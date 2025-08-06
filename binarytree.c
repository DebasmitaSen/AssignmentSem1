#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ------------ Stack for Expression ------------ */
#define MAX 100
typedef struct {
    int top;
    char items[MAX];
} Stack;

void push(Stack *s, char c) { s->items[++(s->top)] = c; }
char pop(Stack *s) { return s->items[(s->top)--]; }
char peek(Stack *s) { return s->items[s->top]; }
int isEmpty(Stack *s) { return s->top == -1; }

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void infixToPostfix(char* infix, char* postfix) {
    Stack s; s.top = -1;
    int k=0;
    for (int i=0; infix[i]; i++) {
        if (isalnum(infix[i])) postfix[k++] = infix[i];
        else if (infix[i] == '(') push(&s, '(');
        else if (infix[i] == ')') {
            while (!isEmpty(&s) && peek(&s) != '(')
                postfix[k++] = pop(&s);
            pop(&s);
        }
        else {
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(infix[i]))
                postfix[k++] = pop(&s);
            push(&s, infix[i]);
        }
    }
    while (!isEmpty(&s)) postfix[k++] = pop(&s);
    postfix[k] = '\0';
}

/* ------------ Hash Table ------------ */
#define SIZE 10
typedef struct {
    int key;
    int value;
} Entry;

Entry* hashTable[SIZE];

int hash(int key) { return key % SIZE; }

void insert(int key, int value) {
    int index = hash(key);
    while (hashTable[index] != NULL && hashTable[index]->key != -1) {
        index = (index + 1) % SIZE;
    }
    Entry* entry = (Entry*) malloc(sizeof(Entry));
    entry->key = key;
    entry->value = value;
    hashTable[index] = entry;
}

int search(int key) {
    int index = hash(key);
    int count = 0;
    while (hashTable[index] != NULL && count < SIZE) {
        if (hashTable[index]->key == key) return hashTable[index]->value;
        index = (index + 1) % SIZE;
        count++;
    }
    return -1;
}

int main() {
    int choice;
    char infix[100], postfix[100];
    int key, value, result;

    do {
        printf("\n--- Problem Set 6 Menu ---\n");
        printf("1. Convert Infix to Postfix\n");
        printf("2. Insert into Hash Table\n");
        printf("3. Search in Hash Table\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter infix expression (use single-letter operands): ");
                scanf("%s", infix);
                infixToPostfix(infix, postfix);
                printf("Postfix Expression: %s\n", postfix);
                break;
            case 2:
                printf("Enter key: ");
                scanf("%d", &key);
                printf("Enter value: ");
                scanf("%d", &value);
                insert(key, value);
                printf("Inserted (%d, %d)\n", key, value);
                break;
            case 3:
                printf("Enter key to search: ");
                scanf("%d", &key);
                result = search(key);
                if (result == -1) printf("Key not found\n");
                else printf("Value for key %d: %d\n", key, result);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 0);

    return 0;
}
