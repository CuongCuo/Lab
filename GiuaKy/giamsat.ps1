# giamsat.ps1 - Ghi nhat ky may sinh vien trong gio thi (Windows).
# Sinh vien chay qua CHAY_GIAM_SAT.bat. Log nop kem bai.
# Hien huy hieu nho goc phai man hinh: xanh = binh thuong, cam = mo app lien lac, do = mo AI.

$ErrorActionPreference = 'SilentlyContinue'
Add-Type -AssemblyName System.Windows.Forms, System.Drawing, Microsoft.VisualBasic
Add-Type @"
using System; using System.Runtime.InteropServices; using System.Text;
public static class FgWin {
  [DllImport("user32.dll")] static extern IntPtr GetForegroundWindow();
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
  [DllImport("user32.dll")] static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
  [DllImport("user32.dll")] static extern bool SetWindowPos(IntPtr h, IntPtr after, int x, int y, int cx, int cy, uint flags);
  // Giu cua so noi tren cung ma khong kich hoat no (SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE)
  public static void KeepOnTop(IntPtr h) { SetWindowPos(h, new IntPtr(-1), 0, 0, 0, 0, 0x13); }
  public static string Title(out uint pid) {
    IntPtr h = GetForegroundWindow(); StringBuilder sb = new StringBuilder(512);
    GetWindowText(h, sb, 512); GetWindowThreadProcessId(h, out pid); return sb.ToString();
  }
}
"@

$KEY = 'UET-CE-SP-GK-2026'

# --- Mau nhan dien ---
$RX_AI_TITLE = '(?i)chat\s?gpt|openai|gemini|claude|copilot|deepseek|perplexity|\bgrok\b|\bpoe\b|\bbard\b|meta ai|mistral|le chat|qwen|\bkimi\b|huggingchat|phind|blackbox|you\.com|ollama|lm studio|gpt4all|\bcursor\b|windsurf|codeium|tabnine|\btrae\b|monica|\bgpt-?\d'
$RX_CHAT_TITLE = '(?i)zalo|messenger|facebook|discord|telegram|gmail|outlook|microsoft teams|slack|whatsapp|instagram'
$RX_AI_PROC = '(?i)^(chatgpt|claude|ollama|ollama app|lm studio|lmstudio|gpt4all|jan|cursor|windsurf|copilot|m365copilot|deepseek|perplexity|codex|gemini|trae|kiro)$'
# Lien lac + dieu khien tu xa (nho nguoi khac lam, hoac chay AI tren may o nha)
$RX_CHAT_PROC = '(?i)^(zalo|telegram|discord|messenger|whatsapp|slack|ultraviewer.*|teamviewer|anydesk|rustdesk|mstsc|parsec|remoting_host|ssh)$'
$RX_AI_DNS = '(?i)openai\.com|chatgpt\.com|oaistatic|oaiusercontent|gemini\.google|bard\.google|aistudio\.google|claude\.ai|anthropic\.com|deepseek|perplexity|grok\.com|copilot\.microsoft|githubcopilot|poe\.com|mistral\.ai|qwen|kimi\.|moonshot|huggingface\.co|phind|blackbox\.ai|you\.com|codeium|tabnine|cursor\.(sh|com)|windsurf'
# Ten mien API ma Claude Code / Codex / Gemini CLI... bat buoc phai goi toi -> xuat hien la co dung
$RX_AI_API = '(?i)anthropic\.com|claude\.ai|openai\.com|chatgpt\.com|generativelanguage\.googleapis|cloudcode-pa\.googleapis|deepseek|api\.x\.ai|openrouter\.ai|mistral\.ai|moonshot|dashscope|api\.z\.ai'
# Dong lenh cua tien trinh: bat ca cong cu AI chay duoi ten node.exe / bun.exe
$RX_AI_CMD = '(?i)@anthropic-ai[\\/]claude-code|anthropic\.claude-code|[\\/]claude(\.exe)?\b|@google[\\/]gemini-cli|gemini-cli|@openai[\\/]codex|[\\/]codex(\.exe)?\b|opencode|\baider\b|qwen-code|@github[\\/]copilot|cursor-agent|[\\/]ollama|@charmland[\\/]crush|[\\/]goose(\.exe)?\b'
$RX_AI_WSL ='(?i)\b(claude|gemini|codex|aider|ollama|opencode|cursor-agent|copilot|qwen|crush|goose|llama|sgpt|chatgpt)\b'
$RX_AI_EXT = '(?i)copilot|codeium|continue\.|tabnine|amazon-q|claude|cline|roo-?cline|chatgpt|gemini|codegpt|blackbox|supermaven|qodo|windsurf'
$RX_VM_PROC = '(?i)^(virtualboxvm|virtualbox|vmware|vmware-vmx|vmplayer|vmconnect|qemu-system-x86_64|vboxheadless)$'
$RX_AI_URL = '(?i)https?://[a-z0-9.-]*(chatgpt\.com|openai\.com|gemini\.google\.com|aistudio\.google\.com|claude\.ai|deepseek\.com|perplexity\.ai|grok\.com|copilot\.microsoft\.com|poe\.com|chat\.mistral\.ai|chat\.qwen\.ai|kimi\.com|moonshot\.cn|huggingface\.co/chat|phind\.com|blackbox\.ai|you\.com|chat\.z\.ai|duck\.ai)[^\x00-\x20"''<>]{0,120}'

# --- Thong tin sinh vien ---
$mssv = $env:GS_MSSV
while ($mssv -notmatch '^\d{8}$') {
  $mssv = [Microsoft.VisualBasic.Interaction]::InputBox('Nhập MSSV (8 chữ số):', 'Giám sát thi', '').Trim()
  if ($mssv -eq '') { exit }
}
$hoten = $env:GS_TEN
if (-not $hoten) { $hoten = [Microsoft.VisualBasic.Interaction]::InputBox('Nhập họ và tên:', 'Giám sát thi', '').Trim() }

$desk = [Environment]::GetFolderPath('Desktop')
$logPath = Join-Path $desk ("GiamSat_{0}_{1}.log" -f $mssv, (Get-Date -Format 'yyyyMMdd_HHmmss'))

# --- Ghi log co chuoi bam: moi dong phu thuoc dong truoc, sua/xoa dong giua se lo ---
$script:seq = 0
$script:prev = '0' * 16
$hmac = New-Object System.Security.Cryptography.HMACSHA256 (,[Text.Encoding]::UTF8.GetBytes($KEY))
function Write-Log([string]$type, [string]$data) {
  $data = ($data -replace '[\r\n|]', ' ').Trim()
  if ($data.Length -gt 300) { $data = $data.Substring(0, 300) }
  $script:seq++
  $body = '{0}|{1}|{2}|{3}' -f $script:seq, (Get-Date -Format 'yyyy-MM-dd HH:mm:ss'), $type, $data
  $h = $hmac.ComputeHash([Text.Encoding]::UTF8.GetBytes($script:prev + '|' + $body))
  $script:prev = (($h[0..7] | ForEach-Object { $_.ToString('x2') }) -join '')
  [IO.File]::AppendAllText($logPath, "$body|$($script:prev)`r`n", [Text.Encoding]::UTF8)
}

# --- Ghi nhan trang thai ban dau ---
Write-Log 'START' ("MSSV={0}; Ten={1}; May={2}; User={3}; OS={4}" -f $mssv, $hoten, $env:COMPUTERNAME, $env:USERNAME, [Environment]::OSVersion.VersionString)

$ext = Get-ChildItem (Join-Path $env:USERPROFILE '.vscode\extensions') -Directory |
  Where-Object { $_.Name -match $RX_AI_EXT } | ForEach-Object { $_.Name }
if ($ext) { Write-Log 'INFO_EXT' ('VS Code co cai: ' + ($ext -join ', ')) }

ipconfig /flushdns | Out-Null   # xoa cache DNS: moi ten mien AI xuat hien sau day deu la trong gio thi
$script:dnsSeen = @{}
Get-DnsClientCache | Where-Object { $_.Entry -match $RX_AI_DNS } | ForEach-Object { $script:dnsSeen[$_.Entry] = 1 }
if ($script:dnsSeen.Count) { Write-Log 'INFO_DNS0' ('Co san truoc gio thi: ' + ($script:dnsSeen.Keys -join ', ')) }

$script:nAI = 0
$script:nChat = 0
$script:nNet = 0
function Flag([string]$cat, [string]$what) {
  if ($cat -eq 'AI') { $script:nAI++ } elseif ($cat -eq 'NET') { $script:nNet++ } else { $script:nChat++ }
  Write-Log "FLAG_$cat" $what
}

# Quy dinh: tu luc bat dau den luc ket thuc giam sat, may KHONG duoc co mang (Wi-Fi, cap, 4G, chia se tu dien thoai, VPN).
function Get-NetOn {
  $p = Get-NetConnectionProfile | Where-Object { $_.InterfaceAlias -notmatch '(?i)vEthernet|VirtualBox|VMware|Loopback' }
  ($p | ForEach-Object { "$($_.InterfaceAlias) [$($_.Name)] $($_.IPv4Connectivity)" }) -join '; '
}
if (-not $env:GS_NOGATE) {
  while ($n = Get-NetOn) {
    Write-Log 'INFO_WAITNET' $n
    [Windows.Forms.MessageBox]::Show("Máy đang có mạng: $n`n`nHãy TẮT Wi-Fi, rút cáp mạng (hoặc bật Chế độ máy bay) rồi bấm OK.`nTừ giờ đến khi kết thúc giám sát không được bật mạng.", 'Giám sát thi') | Out-Null
  }
}
$script:netOn = $false

# Mo de: giai ma cac file *.enc canh script (do mahoa_de.ps1 tao) bang MA DE giang vien cong bo
function Unprotect-Bytes([byte[]]$data, [string]$pass) {
  $salt = $data[8..15]
  $kdf = New-Object Security.Cryptography.Rfc2898DeriveBytes ($pass, [byte[]]$salt, 100000, [Security.Cryptography.HashAlgorithmName]::SHA256)
  $kiv = $kdf.GetBytes(48)
  $aes = [Security.Cryptography.Aes]::Create()
  $aes.Key = $kiv[0..31]; $aes.IV = $kiv[32..47]
  $aes.CreateDecryptor().TransformFinalBlock($data, 16, $data.Length - 16)   # sai ma -> loi padding
}
$encFiles = @(Get-ChildItem $PSScriptRoot -Filter '*.enc')
if ($encFiles.Count) {
  $deDir = Join-Path $desk "DeThi_$mssv"
  while ($true) {
    $pass = if ($env:GS_MADE) { $env:GS_MADE } else { [Microsoft.VisualBasic.Interaction]::InputBox('Nhập MÃ ĐỀ do giảng viên công bố để mở đề:', 'Giám sát thi', '').Trim() }
    if ($pass -eq '') { continue }
    # Moi ma chi mo duoc de cua no (de thu / de chinh thuc): file nao giai ma khong duoc thi bo qua
    $outs = @(foreach ($f in $encFiles) {
      try {
        $plain = Unprotect-Bytes ([IO.File]::ReadAllBytes($f.FullName)) $pass
        $head = [Text.Encoding]::ASCII.GetString($plain, 0, [Math]::Min(4, $plain.Length))
        if (($f.Name -match '\.pdf\.enc$' -and $head -ne '%PDF') -or ($f.Name -match '\.zip\.enc$' -and $head -notlike 'PK*')) { throw 'sai ma' }
        @{ Name = $f.Name -replace '\.enc$', ''; Data = $plain }
      } catch {}
    })
    if (-not $outs.Count) { Write-Log 'INFO_MADE_SAI' ''; [Windows.Forms.MessageBox]::Show('Sai mã đề, nhập lại.', 'Giám sát thi') | Out-Null; continue }
    New-Item -ItemType Directory $deDir -Force | Out-Null
    foreach ($o in $outs) { [IO.File]::WriteAllBytes((Join-Path $deDir $o.Name), $o.Data) }
    Write-Log 'EXAM_OPEN' (($outs | ForEach-Object { $_.Name }) -join ', ')
    $script:maDe = $pass
    Invoke-Item $deDir
    break
  }
}

$script:procSeen = @{}
Get-Process | ForEach-Object {
  $n = $_.ProcessName
  if ($script:procSeen.ContainsKey($n)) { return }
  if ($n -match $RX_AI_PROC) { $script:procSeen[$n] = 1; Flag 'AI' "Dang chay luc bat dau: $n" }
  elseif ($n -match $RX_CHAT_PROC) { $script:procSeen[$n] = 1; Write-Log 'INFO_PROC0' "Dang chay luc bat dau: $n" }
}
Get-Process | Where-Object { $_.ProcessName -match $RX_VM_PROC } |
  ForEach-Object { $script:procSeen[$_.ProcessName] = 1; Write-Log 'VM' $_.ProcessName }

# Lich su trinh duyet: doc tho file SQLite, lay URL trang AI. URL moi xuat hien trong gio thi = da truy cap.
function Get-HistoryFiles {
  $roots = @("$env:LOCALAPPDATA\Google\Chrome\User Data", "$env:LOCALAPPDATA\Microsoft\Edge\User Data",
             "$env:LOCALAPPDATA\BraveSoftware\Brave-Browser\User Data", "$env:LOCALAPPDATA\CocCoc\Browser\User Data")
  foreach ($r in $roots) { Get-ChildItem $r -Directory | Where-Object { $_.Name -match '^(Default|Profile \d+)$' } |
    ForEach-Object { Join-Path $_.FullName 'History' } | Where-Object { Test-Path $_ } }
  $op = "$env:APPDATA\Opera Software\Opera Stable\History"; if (Test-Path $op) { $op }
  Get-ChildItem "$env:APPDATA\Mozilla\Firefox\Profiles\*\places.sqlite*" | ForEach-Object { $_.FullName }
}
function Get-AiUrls {
  $set = @{}
  foreach ($f in Get-HistoryFiles) {
    try {
      $fs = [IO.File]::Open($f, 'Open', 'Read', 'ReadWrite, Delete')
      $buf = New-Object byte[] $fs.Length; [void]$fs.Read($buf, 0, $buf.Length); $fs.Close()
      $txt = [Text.Encoding]::GetEncoding(28591).GetString($buf)
      foreach ($m in [regex]::Matches($txt, $RX_AI_URL)) { $set[$m.Value] = 1 }
    } catch {}
  }
  $set
}
$script:urlSeen = Get-AiUrls
$script:siteSeen = @{}
Write-Log 'INFO_HIST0' ("So URL AI trong lich su truoc gio thi: {0}" -f $script:urlSeen.Count)

function Get-Ssid {
  $l = netsh wlan show interfaces | Select-String '^\s*SSID\s*:' | Select-Object -First 1
  if ($l) { ($l.ToString() -split ':', 2)[1].Trim() } else { '-' }
}
$script:ssid = Get-Ssid
Write-Log 'INFO_NET' "SSID=$($script:ssid)"

$script:cmdSeen = @{}
function Scan-Cmd {
  Get-CimInstance Win32_Process -Property ProcessId, CommandLine, ExecutablePath | Where-Object { $_.CommandLine -match $RX_AI_CMD } |
    ForEach-Object {
      $k = if ($_.ExecutablePath) { $_.ExecutablePath } else { $_.CommandLine }   # moi chuong trinh chi ghi 1 lan
      if (-not $script:cmdSeen.ContainsKey($k)) { $script:cmdSeen[$k] = 1; Flag 'AI' "Lenh: $($_.CommandLine)" }
    }
}

$script:wslSeen = @{}
function Scan-Wsl {
  if (-not (Get-Process vmmemWSL, vmmem, wslhost -ErrorAction SilentlyContinue)) { return }
  $psi = New-Object Diagnostics.ProcessStartInfo 'wsl.exe', '-e sh -c "ps -eo args="'
  $psi.RedirectStandardOutput = $true; $psi.UseShellExecute = $false; $psi.CreateNoWindow = $true
  $p = [Diagnostics.Process]::Start($psi)
  $out = $p.StandardOutput.ReadToEndAsync()
  if (-not $p.WaitForExit(5000)) { $p.Kill(); return }
  foreach ($line in ($out.Result -split "`n")) {
    $line = $line.Trim()
    if ($line -match $RX_AI_WSL -and -not $script:wslSeen.ContainsKey($line)) {
      $script:wslSeen[$line] = 1
      Flag 'AI' "WSL: $line"
    }
  }
}

Scan-Cmd

# --- Huy hieu luon noi tren cung ---
$form = New-Object Windows.Forms.Form
$form.FormBorderStyle = 'None'; $form.TopMost = $true; $form.ShowInTaskbar = $false
$form.Size = New-Object Drawing.Size 360, 54
$wa = [Windows.Forms.Screen]::PrimaryScreen.WorkingArea
$form.StartPosition = 'Manual'
$form.Location = New-Object Drawing.Point ($wa.Right - 370), ($wa.Bottom - 64)
$lbl = New-Object Windows.Forms.Label
$lbl.Dock = 'Fill'; $lbl.TextAlign = 'MiddleCenter'; $lbl.ForeColor = 'White'
$lbl.Font = New-Object Drawing.Font 'Segoe UI', 10, ([Drawing.FontStyle]::Bold)
$form.Controls.Add($lbl)
$tip = New-Object Windows.Forms.ToolTip
$tip.SetToolTip($lbl, 'Cuối giờ: nhấp đúp để kết thúc (cần MÃ KẾT THÚC, không phải mã đề)')

function Update-Badge {
  # Hien tat ca vi pham cung luc: mang khong duoc che mat AI / lien lac
  $parts = @()
  if ($script:netOn) { $parts += 'ĐANG CÓ MẠNG!' } elseif ($script:nNet -gt 0) { $parts += "Đã bật mạng $($script:nNet) lần" }
  if ($script:nAI -gt 0) { $parts += "AI: $($script:nAI)" }
  if ($script:nChat -gt 0) { $parts += "Liên lạc: $($script:nChat)" }
  if ($script:netOn -or $script:nNet -gt 0 -or $script:nAI -gt 0) { $form.BackColor = [Drawing.Color]::FromArgb(200, 30, 30) }
  elseif ($script:nChat -gt 0) { $form.BackColor = [Drawing.Color]::FromArgb(220, 120, 0) }
  else { $form.BackColor = [Drawing.Color]::FromArgb(20, 130, 60) }
  $st = if ($parts) { $parts -join ' · ' } else { 'Bình thường' }
  $lbl.Text = "GIÁM SÁT THI · $mssv · $(Get-Date -Format 'HH:mm:ss')`n$st"
  # Khong dung $form.TopMost = $true o day: lenh do keo con tro khoi hop nhap ma ket thuc moi 1,5 s
  if ($form.IsHandleCreated) { [FgWin]::KeepOnTop($form.Handle) }
}

$script:lastFg = ''
$script:tick = 0
$timer = New-Object Windows.Forms.Timer
$timer.Interval = 1500
$timer.Add_Tick({
  $script:tick++
  # Cua so dang dung (moi 1.5 s, chi ghi khi doi)
  $fpid = [uint32]0
  $title = [FgWin]::Title([ref]$fpid)
  $pname = (Get-Process -Id $fpid).ProcessName
  $fg = "$pname :: $title"
  if ($fg -ne $script:lastFg) {
    $script:lastFg = $fg
    Write-Log 'FG' $fg
    if ($title -match $RX_AI_TITLE -or $pname -match $RX_AI_PROC) { Flag 'AI' "Cua so: $fg" }
    elseif ($title -match $RX_CHAT_TITLE -or $pname -match $RX_CHAT_PROC) { Flag 'CHAT' "Cua so: $fg" }
  }
  # Mang (moi 6 s): ghi lai luc bat / tat
  if ($script:tick % 4 -eq 0) {
    $n = Get-NetOn
    if ($n -and -not $script:netOn) { $script:netOn = $true; Flag 'NET' $n }
    elseif (-not $n -and $script:netOn) { $script:netOn = $false; Write-Log 'NET_OFF' '' }
  }
  # Quet cham (moi 30 s)
  if ($script:tick % 20 -eq 0) {
    Get-Process | ForEach-Object {
      $n = $_.ProcessName
      if (-not $script:procSeen.ContainsKey($n)) {
        if ($n -match $RX_AI_PROC) { $script:procSeen[$n] = 1; Flag 'AI' "Tien trinh moi: $n" }
        elseif ($n -match $RX_CHAT_PROC) { $script:procSeen[$n] = 1; Flag 'CHAT' "Tien trinh moi: $n" }
        elseif ($n -match $RX_VM_PROC) { $script:procSeen[$n] = 1; Write-Log 'VM' $n }
      }
    }
    if ($script:tick % 40 -eq 0) {
      foreach ($u in (Get-AiUrls).Keys) {
        if (-not $script:urlSeen.ContainsKey($u)) {
          $script:urlSeen[$u] = 1
          # Moi trang chi 1 co: mot lan truy cap de lai nhieu URL trong file lich su, co URL dinh ky tu rac
          $site = [regex]::Match($u, $RX_AI_URL).Groups[1].Value.ToLower()
          if (-not $script:siteSeen.ContainsKey($site)) { $script:siteSeen[$site] = 1; Flag 'AI' "Lich su web: $site" }
        }
      }
    }
    Get-DnsClientCache | Where-Object { ($_.Entry -match $RX_AI_DNS -or $_.Entry -match $RX_AI_API) -and -not $script:dnsSeen.ContainsKey($_.Entry) } |
      ForEach-Object {
        $script:dnsSeen[$_.Entry] = 1
        if ($_.Entry -match $RX_AI_API) { Flag 'AI' "Ten mien AI: $($_.Entry)" } else { Write-Log 'DNS' $_.Entry }
      }
    Scan-Cmd
    $s = Get-Ssid
    if ($s -ne $script:ssid) { $script:ssid = $s; Write-Log 'INFO_NET' "SSID=$s" }
    Scan-Wsl
    Write-Log 'HB' ("AI={0}; CHAT={1}; NET={2}" -f $script:nAI, $script:nChat, $script:nNet)
  }
  Update-Badge
})

$script:allowClose = $false
$lbl.Add_DoubleClick({
  $code = [Microsoft.VisualBasic.Interaction]::InputBox("Nhập MÃ KẾT THÚC giảng viên công bố CUỐI GIỜ.`n(Không phải mã đề lúc đầu giờ.)`n`nChưa hết giờ thì bấm Cancel để làm tiếp.", 'Kết thúc giám sát', '').Trim()
  if ($code -eq '') { return }
  if ($script:maDe -and $code -eq $script:maDe) {
    Write-Log 'INFO_NHAM_MA' 'nhap ma de vao o ma ket thuc'
    [Windows.Forms.MessageBox]::Show('Đây là MÃ ĐỀ (đầu giờ), không phải mã kết thúc. Giám sát vẫn tiếp tục.', 'Giám sát thi') | Out-Null
    return
  }
  Write-Log 'END' "code=$code"
  $timer.Stop()
  $form.Hide()
  # Mo san File Explorer, chon dung file log de sinh vien keo vao cho nop bai
  Start-Process explorer.exe "/select,`"$logPath`""
  # Hien thong bao TRUOC khi dong form: dong form chinh se huy luon hop thoai dang mo
  [Windows.Forms.MessageBox]::Show("Đã kết thúc giám sát. Bây giờ được bật mạng để nộp bài.`n`nFile log đã được chọn sẵn trong cửa sổ File Explorer vừa mở:`n$logPath`n`nNộp file này kèm bài làm.", 'Giám sát thi') | Out-Null
  $script:allowClose = $true
  $form.Close()
})
$form.Add_FormClosing({
  param($s, $e)
  if ($script:allowClose) { return }
  if ($e.CloseReason -eq 'WindowsShutDown') { Write-Log 'SHUTDOWN' ''; return }
  Write-Log 'CLOSE_ATTEMPT' "$($e.CloseReason)"
  $e.Cancel = $true
})

Update-Badge
$timer.Start()
[Windows.Forms.MessageBox]::Show("Đang giám sát. File log:`n$logPath`n`n- KHÔNG bật mạng cho đến khi kết thúc.`n- Không tắt huy hiệu xanh ở góc phải dưới màn hình.`n- Cuối giờ: nhấp đúp vào huy hiệu, nhập MÃ KẾT THÚC (khác mã đề). Script sẽ mở sẵn chỗ chứa file log, lúc đó mới bật mạng để nộp bài kèm file log.", 'Giám sát thi') | Out-Null
[Windows.Forms.Application]::Run($form)
$timer.Stop()
