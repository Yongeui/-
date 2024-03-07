#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

typedef struct anod Ty_Node, * TreePointer;

struct anod {
    int sno; 
    char name[50]; 
    TreePointer leftChild, rightChild; 
};

TreePointer new_node(int sno, char* name);
TreePointer insert(TreePointer root, int sno, char* name);
TreePointer search(TreePointer root, char* name);
void inorder(TreePointer root);
TreePointer minValueNode(TreePointer node);
TreePointer deleteNode(TreePointer root, char* name);
int get_max(int a, int b);
int height(TreePointer node);
void printChildren(TreePointer root, char* name);
int countLeaves(TreePointer node);

TreePointer new_node(int sno, char* name) {
    TreePointer temp = (TreePointer)malloc(sizeof(Ty_Node));
    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    temp->sno = sno;
    if (name != NULL) {
        strncpy(temp->name, name, MAX_NAME_LENGTH);
    }
    else {
        temp->name[0] = '\0';
    }
    temp->leftChild = temp->rightChild = NULL;
    return temp;
}

TreePointer insert(TreePointer root, int sno, char* name) {
    if (root == NULL)
        return new_node(sno, name);
    if (strcmp(name, root->name) < 0)
        root->leftChild = insert(root->leftChild, sno, name);
    else if (strcmp(name, root->name) > 0)
        root->rightChild = insert(root->rightChild, sno, name);
    return root;
}

TreePointer search(TreePointer root, char* name) {
    if (root == NULL || strcmp(name, root->name) == 0)
        return root;
    if (strcmp(name, root->name) < 0)
        return search(root->leftChild, name);
    return search(root->rightChild, name);
}

void inorder(TreePointer root) {
    if (root != NULL) {
        inorder(root->leftChild);
        printf("%s, %d\n", root->name, root->sno);
        inorder(root->rightChild);
    }
}

TreePointer minValueNode(TreePointer node) {
    TreePointer current = node;
    while (current && current->leftChild != NULL)
        current = current->leftChild;
    return current;
}

TreePointer deleteNode(TreePointer root, char* name) {
    if (root == NULL) return root;

    if (strcmp(name, root->name) < 0)
        root->leftChild = deleteNode(root->leftChild, name);

    else if (strcmp(name, root->name) > 0)
        root->rightChild = deleteNode(root->rightChild, name);

    else {
        if (root->leftChild == NULL) {
            TreePointer temp = root->rightChild;
            free(root);
            return temp;
        }
        else if (root->rightChild == NULL) {
            TreePointer temp = root->leftChild;
            free(root);
            return temp;
        }

        TreePointer temp = minValueNode(root->rightChild);
        root->sno = temp->sno;
        strncpy(root->name, temp->name, MAX_NAME_LENGTH);
        root->rightChild = deleteNode(root->rightChild, temp->name);
    }
    return root;
}

int height(TreePointer node) {
    if (node == NULL)
        return 0;
    return 1 + get_max(height(node->leftChild), height(node->rightChild));
}

int getLevelUtil(TreePointer node, char* name, int level) {
    if (node == NULL)
        return 0;

    if (strcmp(name, node->name) == 0)
        return level;

    int downlevel = getLevelUtil(node->leftChild, name, level + 1);
    if (downlevel != 0)
        return downlevel;

    downlevel = getLevelUtil(node->rightChild, name, level + 1);
    return downlevel;
}

int getLevel(TreePointer node, char* name) {
    return getLevelUtil(node, name, 1);
}

void printChildren(TreePointer root, char* name) {
    TreePointer node = search(root, name);
    if (node == NULL) {
        printf("그런 학생은 없습니다.\n");
        return;
    }
    printf("Left child: %s, ", node->leftChild ? node->leftChild->name : "None");
    printf("Right child: %s\n", node->rightChild ? node->rightChild->name : "None");
}

int countLeaves(TreePointer node) {
    if (node == NULL)
        return 0;
    if (node->leftChild == NULL && node->rightChild == NULL)
        return 1;
    else
        return countLeaves(node->leftChild) + countLeaves(node->rightChild);
}

int get_max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    char name[MAX_NAME_LENGTH];  
    TreePointer root = NULL;    
    int sno;                     

    FILE* file = fopen("sdata.txt", "r");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }
    while (fscanf(file, "%d %49s", &sno, name) == 2) {
        root = insert(root, sno, name);
    }
    fclose(file);

    char command[3];
    while (1) {
        printf("수행할 작업은 (in, sp, de, se, ht, ch, le, ex) ? ");
        if (scanf("%2s", command) != 1) { 
            printf("Failed to read command.\n");
            continue;
        }
        command[2] = '\0';

        if (strcmp(command, "in") == 0) {
            if (scanf("%d %49s", &sno, name) != 2) { 
                printf("Failed to read sno and name.\n");
                continue;
            }
            root = insert(root, sno, name);
            printf("입력 성공!   level = %d\n", getLevel(root, name));
        }
        else if (strcmp(command, "sp") == 0) {
            printf("파일의 내용은 다음과 같습니다:\n");
            inorder(root);
        }
        else if (strcmp(command, "de") == 0) {
            if (scanf("%49s", name) != 1) {
                printf("Failed to read name.\n");
                continue;
            }
            TreePointer node = search(root, name);
            if (node != NULL) {
                root = deleteNode(root, name);
                printf("성공적으로 삭제되었습니다.\n");
            }
            else
                printf("그런 학생은 없습니다.\n");
        }
        else if (strcmp(command, "se") == 0) {
            if (scanf("%49s", name) != 1) {
                printf("Failed to read name.\n");
                continue;
            }
            TreePointer node = search(root, name);
            if (node != NULL) {
                int level = getLevel(root, name);
                printf("이름: %s, 학번: %d, 레벨위치= %d\n", node->name, node->sno, level);
            }
            else
                printf("No such student.\n");
        }
        else if (strcmp(command, "ht") == 0) {
            printf("Height: %d\n", height(root));
        }
        else if (strcmp(command, "ch") == 0) {
            if (scanf("%49s", name) != 1) {
                printf("Failed to read name.\n");
                continue;
            }
            printChildren(root, name);
        }
        else if (strcmp(command, "le") == 0) {
            printf("number of leaf nodes = %d\n", countLeaves(root));
        }
        else if (strcmp(command, "ex") == 0) {
            printf("프로그램을 종료합니다 !\n");
            printf("계속하려면 아무 키나 누르십시오...\n");
            int ignored = getchar();
            break;
        }
        else {
            printf("Invalid command.\n");
        }
    }
    return 0;
}
