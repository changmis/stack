#include <stdio.h>
#include <stdlib.h>

// 트리 노드 구조체 정의
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// 스택 노드 구조체 정의
struct StackNode {
    struct TreeNode* data;
    struct StackNode* next;
};

// 스택 구조체 정의
struct Stack {
    struct StackNode* top;
};

// 스택 초기화 함수
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}

// 스택이 비어있는지 확인하는 함수
int isEmpty(struct Stack* stack) {
    return (stack->top == NULL);
}

// 스택에 노드를 푸시하는 함수
void push(struct Stack* stack, struct TreeNode* node) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->data = node;
    newNode->next = stack->top;
    stack->top = newNode;
}

// 스택에서 노드를 팝하는 함수
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

// 트리 노드 생성 함수
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 전위 순회 함수
void preorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    struct Stack* stack = createStack();
    push(stack, root);

    while (!isEmpty(stack)) {
        struct TreeNode* node = pop(stack);
        printf("%d ", node->data);

        // 오른쪽 서브트리를 먼저 푸시하여 왼쪽 서브트리를 먼저 방문하도록 합니다.
        if (node->right != NULL) {
            push(stack, node->right);
        }
        if (node->left != NULL) {
            push(stack, node->left);
        }
    }
}

// 중위 순회 함수
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

// 후위 순회 함수
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
    // 트리 노드 생성
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

    printf("전위 순회 결과: ");
    preorderTraversal(root);
    printf("\n");

    printf("중위 순회 결과: ");
    inorderTraversal(root);
    printf("\n");

    printf("후위 순회 결과: ");
    postorderTraversal(root);
    printf("\n");

    return 0;
}
