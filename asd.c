#include <stdio.h>
#include <stdlib.h>

// Ʈ�� ��� ����ü ����
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// ���� ��� ����ü ����
struct StackNode {
    struct TreeNode* data;
    struct StackNode* next;
};

// ���� ����ü ����
struct Stack {
    struct StackNode* top;
};

// ���� �ʱ�ȭ �Լ�
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}

// ������ ����ִ��� Ȯ���ϴ� �Լ�
int isEmpty(struct Stack* stack) {
    return (stack->top == NULL);
}

// ���ÿ� ��带 Ǫ���ϴ� �Լ�
void push(struct Stack* stack, struct TreeNode* node) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->data = node;
    newNode->next = stack->top;
    stack->top = newNode;
}

// ���ÿ��� ��带 ���ϴ� �Լ�
struct TreeNode* pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        return NULL;
    }
    struct StackNode* temp = stack->top;
    stack->top = stack->top->next;
    struct TreeNode* node = temp->data;
    free(temp);
    return node;
}

// Ʈ�� ��� ���� �Լ�
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ���� ��ȸ �Լ�
void preorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    struct Stack* stack = createStack();
    push(stack, root);

    while (!isEmpty(stack)) {
        struct TreeNode* node = pop(stack);
        printf("%d ", node->data);

        // ������ ����Ʈ���� ���� Ǫ���Ͽ� ���� ����Ʈ���� ���� �湮�ϵ��� �մϴ�.
        if (node->right != NULL) {
            push(stack, node->right);
        }
        if (node->left != NULL) {
            push(stack, node->left);
        }
    }
}

// ���� ��ȸ �Լ�
void inorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    struct Stack* stack = createStack();
    struct TreeNode* current = root;

    while (!isEmpty(stack) || current != NULL) {
        if (current != NULL) {
            push(stack, current);
            current = current->left;
        } else {
            current = pop(stack);
            printf("%d ", current->data);
            current = current->right;
        }
    }
}

// ���� ��ȸ �Լ�
void postorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    struct Stack* stack1 = createStack();
    struct Stack* stack2 = createStack();
    push(stack1, root);

    while (!isEmpty(stack1)) {
        struct TreeNode* node = pop(stack1);
        push(stack2, node);

        if (node->left != NULL) {
            push(stack1, node->left);
        }
        if (node->right != NULL) {
            push(stack1, node->right);
        }
    }

    while (!isEmpty(stack2)) {
        struct TreeNode* node = pop(stack2);
        printf("%d ", node->data);
    }
}

int main() {
    // Ʈ�� ��� ����
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(7);
    root->left->left = createNode(3);
    root->left->right = createNode(6);
    root->right->left = createNode(8);
    root->right->right = createNode(9);
    root->left->left->left = createNode(4);
    root->left->left->right = createNode(5);
    root->right->right->left = createNode(10);
    root->right->right->right = createNode(11);

    printf("���� ��ȸ ���: ");
    preorderTraversal(root);
    printf("\n");

    printf("���� ��ȸ ���: ");
    inorderTraversal(root);
    printf("\n");

    printf("���� ��ȸ ���: ");
    postorderTraversal(root);
    printf("\n");

    return 0;
}
