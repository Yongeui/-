 #define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

typedef struct ano* nodeptr;
typedef struct ano {
    char name[30];
    float gpa;
    char place[100];
    nodeptr links[MAX];
} nodetype;

nodeptr ROOT = NULL;
nodeptr stack[100];
int top = -1;

nodeptr search_node(nodeptr cur, char sname[]) {
    int i;
    nodeptr rptr;
    if (!cur) return NULL;

    if (strcmp(cur->name, sname) == 0) {
        return cur;
    }
    else {
        for (i = 0; cur->links[i] != NULL; i++) {
            rptr = search_node(cur->links[i], sname);
            if (rptr) return rptr;
        }
        return NULL;
    }
}

int read_upper(FILE* fp, char buf[20][50]) {
    int i, j, k;
    char line[400];
    char* cp;
    cp = fgets(line, 400, fp);
    if (!cp) {
        printf("Impossible for the control to reach here. \n");
        return 0;
    }
    else {
        if (line[0] == '-')
            return 0;

        i = 0;
        j = 0;
        while (1) {
            k = 0;
            while (line[j] != ' ' && line[j] != '\n') {
                buf[i][k] = line[j];
                j++;
                k++;
            }

            buf[i][k] = '\0';
            i++;
            if (line[j] == '\n')
                break;
            else {
                do
                    j++;
                while (line[j] == ' ');
            }
        }
        return i;
    }
}

void read_store_lower_data(FILE* fp) {
    char rname[30], address[100];
    float rgpa;
    nodeptr np;
    int read_num;

    while (1) {
        read_num = fscanf(fp, "%29s%f%99[^\n]", rname, &rgpa, address);
        fgetc(fp);  

        rname[29] = '\0';
        address[strlen(address)] = '\0';

        if (read_num != 3) break;

        np = search_node(ROOT, rname);
        if (!np) {
            printf("이런 이름을 가진 노드가 없습니다. \n");
            continue;
        }
        strcpy(np->name, rname);
        np->gpa = rgpa;
        strcpy(np->place, address);
    }
}


void print_general_tree(nodeptr curr) {
    int i;
    if (!curr)
        return;

    printf("이름: %s   학점: %5.2f   주소: %s \n", curr->name, curr->gpa, curr->place);
    for (i = 0; curr->links[i]; i++)
        print_general_tree(curr->links[i]);
}

void make_node_and_attach_to_parent(nodeptr parent, char* tname, int loc) {
    nodeptr np1;
    int i;

    np1 = (nodeptr)malloc(sizeof(nodetype));
    if (!np1) {
        printf("Memory allocation failed!\n");
        return;
    }
    strcpy(np1->name, tname);
    for (i = 0; i < MAX; i++)
        np1->links[i] = NULL; 

    if (parent) {  
        parent->links[loc] = np1;
    }
}

void push_stack(nodeptr nptr) {
    top++;
    stack[top] = nptr;
}

void pop_stack() {
    top--;
}

int dfs_ancestors(nodeptr cur, char* sname) {
    int i, res;
    if (strcmp(cur->name, sname) == 0) {
        printf("해당 노드의 조상들은 다음과 같다 :");
        for (i = 0; i <= top; i++)
            printf(" %s", stack[i]->name);
        printf("\n");
        return 1;
    }

    push_stack(cur);
    for (i = 0; cur->links[i]; i++) {
        res = dfs_ancestors(cur->links[i], sname);
        if (res) return 1;
    }
    pop_stack();
    return 0;
}

void dfs_height(nodeptr cur, int par_height, int* tree_height) {
    int my_height = par_height + 1;
    int i;
    if (*tree_height < my_height)
        *tree_height = my_height;
    for (i = 0; cur->links[i]; i++)
        dfs_height(cur->links[i], my_height, tree_height);
    return;
}

int dfs_depth(nodeptr cur, int par_height, char* sname) {
    int my_height = par_height + 1;
    int i, res;
    if (strcmp(cur->name, sname) == 0) {
        printf("해당 노드의 깊이는 다음과 같다 : %s : %d\n", sname, my_height);
        return 1;
    }
    for (i = 0; cur->links[i]; i++) {
        res = dfs_depth(cur->links[i], my_height, sname);
        if (res)
            return 1;
    }
    return 0;
}

void nm(nodeptr current, char* name) {
    if (!current) return;
        
    if (strcmp(current->name, name) == 0) {
        int count = 0;
        for (int i = 0; current->links[i]; i++) {
            printf("%s ", current->links[i]->name);
            count++;
        }
        printf(" : %d명 \n", count);
        return;
    }

    for (int i = 0; current->links[i]; i++) {
        nm(current->links[i], name);
    }
}

int br_found = 0;

void br(nodeptr current, char* name) {
    if (!current || br_found) return;

    int siblings_count = 0;


    for (int i = 0; current->links[i]; i++) {
        if (strcmp(current->links[i]->name, name) == 0) {

            for (int j = 0; current->links[j]; j++) {
                if (j != i) { 
                    printf("%s ", current->links[j]->name);
                    siblings_count++;  
                }
            }

            if (siblings_count == 0) {
                printf("%s의 형제는 없습니다.\n", name);
            } else {
                printf("\n");
            }

            br_found = 1;
            return;
        }
    }


    for (int i = 0; current->links[i]; i++) {
        br(current->links[i], name);
    }
}

int main() {
    char buf[20][50];
    char line[400], command[50], name[30];
    int num_persons, k, i, res;
    nodeptr np;

    FILE* fp = fopen("data_general_tree.txt", "r");
    if (!fp) {
        printf("file open error. \n");
        return 1;
    }

    do {
        num_persons = read_upper(fp, buf);
        if (num_persons == 0)
            break;

        if (!ROOT) {
            np = (nodeptr)malloc(sizeof(nodetype));
            if (!np) {
                printf("Memory allocation failed!\n");
                return 1;
            }
            strcpy(np->name, buf[0]);
            for (int j = 0; j < MAX; j++) np->links[j] = NULL; 
            ROOT = np;
            np->links[0] = NULL;
            for (k = 1; k < num_persons; k++)
                make_node_and_attach_to_parent(np, buf[k], k - 1);

            np->links[k - 1] = NULL;
        }
        else {
            np = search_node(ROOT, buf[0]);
            if (!np) {
                printf("Error: 두번째 줄 이하의 첫 이름의 노드가 없음. \n");
                continue;
                while (getchar() != '\n');
            }
            for (k = 1; k < num_persons; k++)
                make_node_and_attach_to_parent(np, buf[k], k - 1);
            np->links[k - 1] = NULL;
        }
    } while (1);

    read_store_lower_data(fp);
    printf("Data_general_tree.txt의 데이터 \n");
    printf("----------------------------------------\n");
    print_general_tree(ROOT);
    printf("----------------------------------------\n");
    printf("\n");


    do {
        printf("명령어를 입력하세요(se, ht, dp, ac, nm, br, ex) : ");
        fgets(line, sizeof(line), stdin);

        i = 0;
        while (line[i] == ' ' || line[i] == '\t') i++;
        k = 0;
        while (!(line[i] == ' ' || line[i] == '\t' || line[i] == '\n')) { 
            command[k] = line[i];
            i++;
            k++;
        }
        command[k] = '\0';

        if (strcmp(command, "ex") == 0) {
            printf("----------------------------------------\n");
                printf("루프를 종료하였습니다. \n");
            break;
        }

        k = 0;
        while (line[i] == ' ' || line[i] == '\t') i++;
        while (!(line[i] == ' ' || line[i] == '\t' || line[i] == '\n')) { 
            name[k] = line[i];
            i++;
            k++;
        }
        name[k] = '\0';

        if (strcmp(command, "se") == 0) {
            np = search_node(ROOT, name);
            if (np)
                printf("해당 노드의 데이터는 다음과 같다 : %s %6.2f %s\n", np->name, np->gpa, np->place);
            else printf("Such a person does not exist. \n");
        }
        else if (strcmp(command, "nm") == 0) {
            nm(ROOT, name);
        }
        else if (strcmp(command, "br") == 0) {
            br_found = 0;  
            br(ROOT, name);
        }
        else if (strcmp(command, "ht") == 0) {
            int tree_height = 0;
            dfs_height(ROOT, 0, &tree_height);
            printf("트리의 높이는 다음과 같다 : %d \n", tree_height);
        }
        else if (strcmp(command, "dp") == 0) {
            res = dfs_depth(ROOT, 0, name);
            if (!res)
                printf("Such a name does not exist in the tree. \n");
        }
        else if (strcmp(command, "ac") == 0) {
            top = -1;
            res = dfs_ancestors(ROOT, name);
            if (!res)
                printf("Such a name does not exist in the tree. \n");
        }
        else {
            printf("Wrong command. \n");
        }
    } while (1);


    fclose(fp);
    return 0;
}
