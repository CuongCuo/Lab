#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int value) {
    Node *p = malloc(sizeof(Node));
    if (p == NULL) {
        return NULL;
    }
    p->data = value;
    p->next = NULL;
    return p;
}

void add_node(Node **head, int value) {
    Node *newNode = create_node(value);
    if (newNode == NULL) return;        // malloc thất bại

    if (*head == NULL) {                // danh sách rỗng
        *head = newNode;
        return;
    }
    Node *cur = *head;
    while (cur->next != NULL)           // đi tới node cuối
        cur = cur->next;
    cur->next = newNode;                // nối vào cuối
}

void print_list(Node *head) {
    for (Node *cur = head; cur != NULL; cur = cur->next)
        printf("%d -> ", cur->data);
    printf("NULL\n");
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *next = head->next;        // lưu trước khi free
        free(head);
        head = next;
    }
}

int main() {
    Node *head = NULL;

    add_node(&head, 10);
    add_node(&head, 20);
    add_node(&head, 30);

    print_list(head);                   // 10 -> 20 -> 30 -> NULL

    free_list(head);
    return 0;
}