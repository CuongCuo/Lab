#!/usr/bin/env python3
"""giamsat_linux.py - Ghi nhat ky may sinh vien trong gio thi (Ubuntu dual-boot hoac Ubuntu trong VM).

Chay:  python3 giamsat_linux.py      (chi can python3 co san tren Ubuntu)
Cuoi gio: bam Ctrl+C trong cua so nay, nhap ma ket thuc, roi nop file log kem bai.
Log cung dinh dang voi ban Windows, giang vien dung chung phantich.ps1.
"""
import glob, hashlib, hmac, os, re, shutil, signal, socket, sqlite3, subprocess, sys, tempfile, threading, time
from datetime import datetime

KEY = b'UET-CE-SP-GK-2026'

RX_AI_TITLE = re.compile(r'chat\s?gpt|openai|gemini|claude|copilot|deepseek|perplexity|\bgrok\b|\bpoe\b|\bbard\b|meta ai|mistral|le chat|qwen|\bkimi\b|huggingchat|phind|blackbox|you\.com|ollama|lm studio|gpt4all|\bcursor\b|windsurf|codeium|tabnine|\btrae\b|monica|\bgpt-?\d', re.I)
RX_CHAT_TITLE = re.compile(r'zalo|messenger|facebook|discord|telegram|gmail|outlook|microsoft teams|slack|whatsapp|instagram', re.I)
# Xet ca dong lenh: bat ca Claude Code / Gemini CLI / Codex chay duoi ten "node"
RX_AI_PROC = re.compile(r'\b(claude|claude-code|gemini|gemini-cli|codex|aider|ollama|opencode|cursor-agent|cursor|windsurf|copilot|qwen|qwen-code|crush|goose|llama[-\w]*|sgpt|chatgpt|lm-studio|lmstudio|gpt4all)\b', re.I)
# Lien lac + dieu khien tu xa
RX_CHAT_PROC = re.compile(r'(^|/)(telegram-desktop|telegram|discord|slack|zalo|whatsapp[-\w]*|ssh|anydesk|rustdesk|teamviewer|remmina)(\s|$)', re.I)
RX_AI_URL = re.compile(r'https?://[a-z0-9.-]*(chatgpt\.com|openai\.com|gemini\.google\.com|aistudio\.google\.com|claude\.ai|deepseek\.com|perplexity\.ai|grok\.com|copilot\.microsoft\.com|poe\.com|chat\.mistral\.ai|chat\.qwen\.ai|kimi\.com|moonshot\.cn|huggingface\.co/chat|phind\.com|blackbox\.ai|you\.com|chat\.z\.ai|duck\.ai)', re.I)
RX_AI_EXT = re.compile(r'copilot|codeium|continue\.|tabnine|amazon-q|claude|cline|roo-?cline|chatgpt|gemini|codegpt|blackbox|supermaven|qodo|windsurf', re.I)

HOME = os.path.expanduser('~')


def sh(cmd, timeout=3):
    try:
        return subprocess.run(cmd, capture_output=True, text=True, timeout=timeout).stdout.strip()
    except Exception:
        return ''


# --- Log co chuoi bam (giong ban Windows) ---
class Log:
    def __init__(self, path):
        self.path, self.seq, self.prev = path, 0, '0' * 16

    def write(self, typ, data=''):
        data = re.sub(r'[\r\n|]', ' ', str(data)).strip()[:300]
        self.seq += 1
        body = f'{self.seq}|{datetime.now():%Y-%m-%d %H:%M:%S}|{typ}|{data}'
        self.prev = hmac.new(KEY, (self.prev + '|' + body).encode(), hashlib.sha256).hexdigest()[:16]
        with open(self.path, 'a', encoding='utf-8') as f:
            f.write(f'{body}|{self.prev}\r\n')


def mo_de(enc, pw, de_dir):
    """Giai ma cac file .enc khop voi ma (de thu / de chinh thuc), tra ve ten cac de mo duoc.
    Ghi ra file tam truoc, nen nhap sai ma khong lam hong de da mo tu truoc."""
    os.makedirs(de_dir, exist_ok=True)
    opened = []
    for f in enc:
        name = os.path.basename(f)[:-4]
        dst = os.path.join(de_dir, name)
        tmp = dst + '.tmp'
        r = subprocess.run(['openssl', 'enc', '-d', '-aes-256-cbc', '-pbkdf2', '-iter', '100000', '-md', 'sha256',
                            '-in', f, '-out', tmp, '-pass', 'stdin'], input=pw + '\n', capture_output=True, text=True)
        head = open(tmp, 'rb').read(4) if r.returncode == 0 else b''
        bad = (name.endswith('.pdf') and head != b'%PDF') or (name.endswith('.zip') and not head.startswith(b'PK'))
        if r.returncode == 0 and not bad:
            os.replace(tmp, dst)
            opened.append(name)
        elif os.path.exists(tmp):
            os.remove(tmp)
    return opened


def ten_trang(url):
    """Ten trang AI trong URL, de moi trang chi tinh 1 co."""
    m = RX_AI_URL.search(url)
    return m.group(1).lower() if m else url[:60]


def trang_thai(net, n):
    """Mau nen va dong trang thai: hien tat ca vi pham, mang khong che mat AI / lien lac."""
    parts = []
    if net:
        parts.append('ĐANG CÓ MẠNG!')
    elif n['NET']:
        parts.append(f'Đã bật mạng {n["NET"]} lần')
    if n['AI']:
        parts.append(f'AI: {n["AI"]}')
    if n['CHAT']:
        parts.append(f'Liên lạc: {n["CHAT"]}')
    color = '41' if net or n['NET'] or n['AI'] else '43' if n['CHAT'] else '42'
    return color, ' · '.join(parts) or 'Bình thường'


# --- Cua so dang dung: chi lam duoc tren X11 ---
def foreground():
    if os.environ.get('XDG_SESSION_TYPE') != 'x11' or not shutil.which('xprop'):
        return None
    m = re.search(r'(0x[0-9a-f]+)', sh(['xprop', '-root', '_NET_ACTIVE_WINDOW']))
    if not m or m.group(1) == '0x0':
        return ''
    out = sh(['xprop', '-id', m.group(1), '_NET_WM_NAME', 'WM_CLASS'])
    name = re.search(r'_NET_WM_NAME\(\w+\) = "(.*)"', out)
    cls = re.findall(r'"([^"]*)"', out.split('WM_CLASS', 1)[1]) if 'WM_CLASS' in out else []
    return f"{cls[-1] if cls else '?'} :: {name.group(1) if name else ''}"


# Quy dinh: tu luc bat dau den luc ket thuc giam sat, may KHONG duoc co mang.
# Thu ket noi ra Internet that (trong VirtualBox, VM luon co route NAT nen khong dua vao route).
def net_on():
    for host, port in (('1.1.1.1', 443), ('8.8.8.8', 53), ('208.67.222.222', 443)):
        try:
            socket.create_connection((host, port), timeout=2).close()
            return sh(['ip', '-brief', 'route', 'show', 'default']) or f'ket noi duoc {host}'
        except OSError:
            pass
    return ''


class NetWatch(threading.Thread):
    """Kiem tra mang moi 5 s o luong rieng de khong lam dung vong chinh."""
    def __init__(self):
        super().__init__(daemon=True)
        self.state = ''

    def run(self):
        while True:
            self.state = net_on()
            time.sleep(5)


def processes():
    res = {}
    for d in glob.glob('/proc/[0-9]*/cmdline'):
        try:
            with open(d, 'rb') as f:
                cmd = f.read().replace(b'\0', b' ').decode(errors='replace').strip()
            if cmd:
                res[cmd[:200]] = 1
        except Exception:
            pass
    return res


# --- Lich su trinh duyet (doc ban sao SQLite, loc luot truy cap trang AI sau moc thoi gian) ---
def history_files():
    pats = [('ff', '~/.mozilla/firefox/*/places.sqlite'), ('ff', '~/snap/firefox/common/.mozilla/firefox/*/places.sqlite')]
    for base in ['~/.config/google-chrome', '~/.config/chromium', '~/snap/chromium/common/chromium',
                 '~/.config/BraveSoftware/Brave-Browser', '~/.config/microsoft-edge', '~/.config/opera']:
        pats += [('cr', base + '/Default/History'), ('cr', base + '/Profile */History'), ('cr', base + '/History')]
    for kind, p in pats:
        for f in glob.glob(os.path.expanduser(p)):
            yield kind, f


def ai_visits(since_epoch):
    found = []
    for kind, f in history_files():
        tmp = tempfile.mkdtemp()
        try:
            dst = os.path.join(tmp, 'h.db')
            shutil.copy2(f, dst)
            for ext in ('-wal', '-journal'):
                if os.path.exists(f + ext):
                    shutil.copy2(f + ext, dst + ext)
            con = sqlite3.connect(dst)
            if kind == 'ff':
                q = ('SELECT p.url, v.visit_date/1000000 FROM moz_historyvisits v JOIN moz_places p ON p.id=v.place_id '
                     'WHERE v.visit_date/1000000 >= ?')
            else:
                q = ('SELECT u.url, v.visit_time/1000000 - 11644473600 FROM visits v JOIN urls u ON u.id=v.url '
                     'WHERE v.visit_time/1000000 - 11644473600 >= ?')
            for url, t in con.execute(q, (int(since_epoch),)):
                if RX_AI_URL.search(url or ''):
                    found.append((int(t), url[:200]))
            con.close()
        except Exception:
            pass
        finally:
            shutil.rmtree(tmp, ignore_errors=True)
    return found


def main():
    if 'microsoft' in open('/proc/version').read().lower():
        print('Đây là WSL. Hãy chạy CHAY_GIAM_SAT.bat bên Windows thay vì script này.')
        return

    mssv = ''
    while not re.fullmatch(r'\d{8}', mssv):
        mssv = input('Nhập MSSV (8 chữ số): ').strip()
    hoten = input('Nhập họ và tên: ').strip()

    desk = sh(['xdg-user-dir', 'DESKTOP']) or HOME
    if not os.path.isdir(desk):
        desk = HOME
    log = Log(os.path.join(desk, f'GiamSat_{mssv}_{datetime.now():%Y%m%d_%H%M%S}.log'))
    start = time.time()

    virt = sh(['systemd-detect-virt']) or 'unknown'
    session = os.environ.get('XDG_SESSION_TYPE', '?')
    log.write('START', f'MSSV={mssv}; Ten={hoten}; May={os.uname().nodename}; User={os.environ.get("USER")}; '
                       f'OS=Linux {os.uname().release}; Virt={virt}; Session={session}')
    if virt not in ('none', 'unknown'):
        log.write('VM', f'Dang chay trong may ao: {virt}')
    if session != 'x11':
        log.write('INFO_NOFG', f'Phien {session}: khong theo doi duoc cua so dang dung, chi dua vao tien trinh + lich su web')

    exts = []
    for d in ('~/.vscode/extensions', '~/.vscode-oss/extensions'):
        d = os.path.expanduser(d)
        if os.path.isdir(d):
            exts += [e for e in os.listdir(d) if RX_AI_EXT.search(e)]
    if exts:
        log.write('INFO_EXT', 'VS Code co cai: ' + ', '.join(exts))

    if not os.environ.get('GS_NOGATE'):
        while True:
            s = net_on()
            if not s:
                break
            log.write('INFO_WAITNET', s)
            input(f'\nMáy đang có mạng ({s}).\nHãy TẮT mạng (Wi-Fi/cáp; trong VirtualBox tắt cả mạng của máy thật) rồi bấm Enter... ')

    # Mo de: giai ma cac file *.enc canh script bang MA DE giang vien cong bo (can lenh openssl, co san tren Ubuntu)
    enc = sorted(glob.glob(os.path.join(os.path.dirname(os.path.abspath(__file__)), '*.enc')))
    ma_de = None
    if enc:
        de_dir = os.path.join(desk, f'DeThi_{mssv}')
        while True:
            pw = os.environ.get('GS_MADE') or input('Nhập MÃ ĐỀ do giảng viên công bố để mở đề: ').strip()
            if not pw:
                continue
            opened = mo_de(enc, pw, de_dir)
            if opened:
                log.write('EXAM_OPEN', ', '.join(opened))
                ma_de = pw
                print(f'Đã mở đề vào thư mục: {de_dir}')
                subprocess.Popen(['xdg-open', de_dir], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
                break
            log.write('INFO_MADE_SAI')
            print('Sai mã đề, nhập lại.')

    n = {'AI': 0, 'CHAT': 0, 'NET': 0}

    def flag(cat, what):
        n[cat] += 1
        log.write('FLAG_' + cat, what)

    proc_seen = processes()
    for c in proc_seen:
        if RX_AI_PROC.search(c):
            flag('AI', 'Dang chay luc bat dau: ' + c)
        elif RX_CHAT_PROC.search(c):
            log.write('INFO_PROC0', 'Dang chay luc bat dau: ' + c)

    ending = {'v': False}

    def on_int(sig, frm):
        ending['v'] = True

    def on_term(sig, frm):
        log.write('CLOSE_ATTEMPT', f'signal {sig}')
        sys.exit(1)

    signal.signal(signal.SIGINT, on_int)
    signal.signal(signal.SIGTERM, on_term)
    signal.signal(signal.SIGHUP, on_term)

    print(f'\nĐang giám sát. File log: {log.path}')
    print('KHÔNG bật mạng cho đến khi kết thúc. KHÔNG đóng cửa sổ này, để nó hiện ở góc màn hình.')
    print('Cuối giờ: bấm Ctrl+C, nhập MÃ KẾT THÚC (khác mã đề). Script sẽ mở sẵn chỗ chứa file log,')
    print('lúc đó mới bật mạng để nộp bài kèm file log.\n')

    nw = NetWatch()
    nw.start()
    last_fg, site_seen, tick, net_was = None, set(), 0, ''
    while True:
        if ending['v']:
            code = input('\nNhập MÃ KẾT THÚC giảng viên công bố CUỐI GIỜ (không phải mã đề).\n'
                         'Chưa hết giờ thì bấm Enter để làm tiếp: ').strip()
            ending['v'] = False
            if code and code == ma_de:
                log.write('INFO_NHAM_MA', 'nhap ma de vao o ma ket thuc')
                print('Đây là MÃ ĐỀ (đầu giờ), không phải mã kết thúc. Giám sát vẫn tiếp tục.')
            elif code:
                log.write('END', f'code={code}')
                print(f'\nĐã kết thúc. Bây giờ được bật mạng để nộp bài.\nNộp file log này kèm bài làm:\n  {log.path}')
                # Mo san trinh quan ly file, chon dung file log
                cmd = ['nautilus', '--select', log.path] if shutil.which('nautilus') else ['xdg-open', os.path.dirname(log.path)]
                subprocess.Popen(cmd, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
                return
            else:
                log.write('CLOSE_ATTEMPT', 'Ctrl+C khong nhap ma')

        tick += 1
        net = nw.state
        if net and not net_was:
            flag('NET', net)
        elif net_was and not net:
            log.write('NET_OFF')
        net_was = net

        fg = foreground()
        if fg is not None and fg != last_fg:
            last_fg = fg
            log.write('FG', fg)
            if RX_AI_TITLE.search(fg):
                flag('AI', 'Cua so: ' + fg)
            elif RX_CHAT_TITLE.search(fg):
                flag('CHAT', 'Cua so: ' + fg)

        if tick % 20 == 0:  # ~30 s
            for c in processes():
                if c not in proc_seen:
                    proc_seen[c] = 1
                    if RX_AI_PROC.search(c):
                        flag('AI', 'Tien trinh moi: ' + c)
                    elif RX_CHAT_PROC.search(c):
                        flag('CHAT', 'Tien trinh moi: ' + c)
            if tick % 40 == 0:  # ~60 s
                for t, url in sorted(ai_visits(start)):
                    site = ten_trang(url)   # moi trang chi 1 co, ghi lan truy cap dau tien
                    if site not in site_seen:
                        site_seen.add(site)
                        flag('AI', f'Lich su web ({datetime.fromtimestamp(t):%H:%M:%S}): {url}')
            log.write('HB', f'AI={n["AI"]}; CHAT={n["CHAT"]}; NET={n["NET"]}')

        color, st = trang_thai(net, n)
        sys.stdout.write(f'\r\033[1;97;{color}m GIÁM SÁT · {mssv} · {datetime.now():%H:%M:%S} · {st} \033[0m\033[K')
        sys.stdout.flush()
        time.sleep(1.5)


if __name__ == '__main__':
    main()
