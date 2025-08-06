#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* addBack(Node* head, int data) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if (!head) return newNode;
    Node* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
    return head;
}

void displayList(Node* head) {
    if (!head) {
        printf("List is empty\n");
        return;
    }
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

Node* deleteNode(Node* head, int key) {
    Node* temp = head;
    Node* prev = NULL;
    while (temp && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) {
        printf("Element %d not found\n", key);
        return head;
    }
    if (!prev) head = head->next;
    else prev->next = temp->next;
    free(temp);
    return head;
}

void freeList(Node* head) {
    Node* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

/* ------------ Binary Tree ------------ */
typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode* talloc(int data) {
    TreeNode* node = malloc(sizeof(TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

TreeNode* addNode(TreeNode* root, int data) {
    if (!root) return talloc(data);
    if (data < root->data) root->left = addNode(root->left, data);
    else root->right = addNode(root->right, data);
    return root;
}

void preorder(TreeNode* root) {
    if (root) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(TreeNode* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void delTree(TreeNode* root) {
    if (!root) return;
    delTree(root->left);
    delTree(root->right);
    free(root);
}

int main() {
    int choice;
    Node* head = NULL;
    TreeNode* root = NULL;

    do {
        printf("\n--- Problem Set 5 Menu ---\n");
        printf("1. Add element to Linked List\n");
        printf("2. Display Linked List\n");
        printf("3. Delete element from Linked List\n");
        printf("4. Add element to Binary Tree\n");
        printf("5. Preorder Traversal\n");
        printf("6. Inorder Traversal\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        int data;
        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &data);
                head = addBack(head, data);
                break;
            case 2:
                displayList(head);
                break;
            case 3:
                printf("Enter value to delete: ");
                scanf("%d", &data);
                head = deleteNode(head, data);
                break;
            case 4:
                printf("Enter value: ");
                scanf("%d", &data);
                root = addNode(root, data);
                break;
            case 5:
                printf("Preorder: ");
                preorder(root);
                printf("\n");
                break;
            case 6:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;
            case 0:
                freeList(head);
                delTree(root);
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 0);

    return 0;
}
