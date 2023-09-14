#include <stdio.h>
#include <stdlib.h>

// 트리 노드를 나타내는 구조체 정의
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 스택을 위한 구조체 정의
typedef struct StackNode {
    TreeNode* node;
    struct StackNode* next;
} StackNode;

// 스택 관련 함수

StackNode* createStackNode(TreeNode* node) {
    StackNode* stackNode = (StackNode*)malloc(sizeof(StackNode));
    stackNode->node = node;
    stackNode->next = NULL;
    return stackNode;
}

int isEmpty(StackNode* root) {
    return !root;
}

void push(StackNode** root, TreeNode* node) {
    StackNode* stackNode = createStackNode(node);
    stackNode->next = *root;
    *root = stackNode;
}

TreeNode* pop(StackNode** root) {
    if (isEmpty(*root)) {
        return NULL;
    }
    StackNode* temp = *root;
    *root = (*root)->next;
    TreeNode* popped = temp->node;
    free(temp);
    return popped;
}

// 전위 순회 함수 (링크 표현법)
void linkPreorderTraversal(TreeNode* root) {
    if (root == NULL)
        return;

    printf("%d ", root->data);
    linkPreorderTraversal(root->left);
    linkPreorderTraversal(root->right);
}

// 중위 순회 함수 (링크 표현법)
void linkInorderTraversal(TreeNode* root) {
    if (root == NULL)
        return;

    linkInorderTraversal(root->left);
    printf("%d ", root->data);
    linkInorderTraversal(root->right);
}

// 후위 순회 함수 (링크 표현법)
void linkPostorderTraversal(TreeNode* root) {
    if (root == NULL)
        return;

    linkPostorderTraversal(root->left);
    linkPostorderTraversal(root->right);
    printf("%d ", root->data);
}

// 전위 순회 함수 (스택 사용)
void stackPreorderTraversal(TreeNode* root) {
    if (root == NULL)
        return;

    StackNode* stack = NULL;
    TreeNode* current = root;
    push(&stack, current);

    while (!isEmpty(stack)) {
        current = pop(&stack);
        printf("%d ", current->data);

        if (current->right != NULL) {
            push(&stack, current->right);
        }

        if (current->left != NULL) {
            push(&stack, current->left);
        }
    }
}

// 중위 순회 함수 (스택 사용)
void stackInorderTraversal(TreeNode* root) {
    if (root == NULL)
        return;

    StackNode* stack = NULL;
    TreeNode* current = root;

    while (current != NULL || !isEmpty(stack)) {
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }

        current = pop(&stack);
        printf("%d ", current->data);

        current = current->right;
    }
}

// 후위 순회 함수 (스택 사용)
void stackPostorderTraversal(TreeNode* root) {
    if (root == NULL)
        return;

    StackNode* stack1 = NULL;
    StackNode* stack2 = NULL;
    TreeNode* current = root;

    push(&stack1, current);

    while (!isEmpty(stack1)) {
        current = pop(&stack1);
        push(&stack2, current);

        if (current->left != NULL) {
            push(&stack1, current->left);
        }

        if (current->right != NULL) {
            push(&stack1, current->right);
        }
    }

    while (!isEmpty(stack2)) {
        current = pop(&stack2);
        printf("%d ", current->data);
    }
}

int main() {
    TreeNode n1 = { 4, NULL, NULL };
    TreeNode n2 = { 5, NULL, NULL };
    TreeNode n3 = { 3, &n1, &n2 };
    TreeNode n4 = { 6, NULL, NULL };
    TreeNode n5 = { 2, &n3, &n4 };
    TreeNode n6 = { 10, NULL, NULL };
    TreeNode n7 = { 11, NULL, NULL };
    TreeNode n8 = { 8, NULL, NULL };
    TreeNode n9 = { 9, &n6, &n7 };
    TreeNode n10 = { 7, &n8, &n9 };
    TreeNode n11 = { 1, &n5, &n10 };
    TreeNode* root = &n11;

    printf("링크 표현법 전위 순회 결과: ");
    linkPreorderTraversal(root);
    printf("\n");

    printf("링크 표현법 중위 순회 결과: ");
    linkInorderTraversal(root);
    printf("\n");

    printf("링크 표현법 후위 순회 결과: ");
    linkPostorderTraversal(root);
    printf("\n");

    printf("스택 사용 전위 순회 결과: ");
    stackPreorderTraversal(root);
    printf("\n");

    printf("스택 사용 중위 순회 결과: ");
    stackInorderTraversal(root);
    printf("\n");

    printf("스택 사용 후위 순회 결과: ");
    stackPostorderTraversal(root);
    printf("\n");

    return 0;
}
