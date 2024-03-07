#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Listdata {
    char name[30];
    int id;
    char phone[20];
    char province[30];
} listData;


typedef struct Listnode* type_listNode_pointer;
typedef struct Listnode {
    listData data;
    type_listNode_pointer link;
} listNode;


typedef struct LinkedList {
    type_listNode_pointer head;
    int length;
} linkedList;


void insertLast(linkedList* L, listData item) {
    
    type_listNode_pointer newNode = (type_listNode_pointer)malloc(sizeof(listNode));
    newNode->data = item;
    newNode->link = NULL;

    
    if (L->head == NULL) {
        L->head = newNode;
    }
    else {
        
        type_listNode_pointer temp = L->head;
        while (temp->link != NULL) {
            temp = temp->link;
        }
        
        temp->link = newNode;
    }
    
    L->length++;
}


void printList(linkedList* L) {
   
    type_listNode_pointer temp = L->head;
    printf("모든 학생 정보 출력\n");
    while (temp != NULL) {
        
        printf("이름: %s, 학번: %d, 전화번호: %s, 거주지역: %s\n", temp->data.name, temp->data.id, temp->data.phone, temp->data.province);
       
        temp = temp->link;
    }
}


type_listNode_pointer search(linkedList* L, int x) {
    
    type_listNode_pointer temp = L->head;
    while (temp != NULL) {
        
        if (temp->data.id == x) {
           
            return temp;
        }
        
        temp = temp->link;
    }
   
    return NULL;
}


void insert(linkedList* L, listNode* pre, listData x) {
    
    if (pre == NULL) {
        printf("삽입 실패: 이전 노드를 리스트에서 찾을 수 없음\n");
        return;
    }

    
    type_listNode_pointer temp = L->head;
    while (temp != NULL) {
        if (temp->data.id == x.id) {
            printf("삽입 실패: 학번 %d인 학생이 이미 리스트에 존재함\n", x.id);
            return;
        }
        
        temp = temp->link;
    }

   
    type_listNode_pointer newNode = (type_listNode_pointer)malloc(sizeof(listNode));
    newNode->data = x;
    newNode->link = pre->link;

    
    pre->link = newNode;
   
    L->length++;
    
    printList(L);
}


void delete(linkedList* L, int x) {
    
    if (L->head == NULL) {
        printf("삭제 실패: 리스트가 비어 있음\n");
        return;
    }
   
    if (L->head->data.id == x) {
        
        type_listNode_pointer temp = L->head;
        L->head = L->head->link;
        free(temp);

       
        L->length--;

        
        printList(L);
        return;
    }

    
    type_listNode_pointer prev = NULL, cur = L->head;
    while (cur != NULL) {
       
        if (cur->data.id == x) {
           
            prev->link = cur->link;
            free(cur);

            
            L->length--;

            
            printList(L);
            return;
        }
        
        prev = cur;
        cur = cur->link;
    }

   
    printf("삭제 실패: 학번 %d인 학생을 찾을 수 없음\n", x);
}


void reverse(linkedList* L) {
    
    type_listNode_pointer prev = NULL, cur = L->head, next;
    
    while (cur != NULL) {
       
        next = cur->link;
        
        cur->link = prev;
     
        prev = cur;
        cur = next;
    }

  
    L->head = prev;

 
    printList(L);
}


int getLength(linkedList* L) {
    return L->length;
}

int main() {
   
    linkedList LL = { NULL, 0 };


    listData item;
    type_listNode_pointer np;
    int id;
    int pre_id;
  
    FILE* fp = fopen("student_data.txt", "r");
    if (fp == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

  
    while (fscanf(fp, "%s %d %s %s", item.name, &item.id, item.phone, item.province) != EOF) {
        insertLast(&LL, item);
    }
    fclose(fp);


    while (1) {
        char input[100];
        char* command;

       
        printf("명령어를 입력하세요: ");
        gets(input); 

        command = strtok(input, " ");
        if (!command)
        {
            continue;
        }
       
        if (strcmp(command, "print") == 0) {
           
            printList(&LL);
        }
        else if (strcmp(command, "search") == 0) {
            
            command = strtok(NULL, " ");
            id = atoi(command);
            np = search(&LL, id);
            if (np)
            {
                printf("검색결과\n");
                printf("이름: %s, 학번: %d, 전화번호: %s, 거주지역: %s\n", np->data.name, np->data.id, np->data.phone, np->data.province);
                printf("-----------------------------------------------------------------\n");
            }
            else
            {
                printf("검색 실패: 학번 %d인 학생 없음\n", id);
            }
        }
        else if (strcmp(command, "insert") == 0) {
            command = strtok(NULL, " ");
            pre_id = atoi(command);
            command = strtok(NULL, " ");
            item.id = atoi(command);
            command = strtok(NULL, " ");
            strcpy(item.name, command);
            command = strtok(NULL, " ");
            strcpy(item.phone, command);
            command = strtok(NULL, " ");
            strcpy(item.province, command);
           
            type_listNode_pointer pre_node = search(&LL, pre_id);
            type_listNode_pointer pre_node2 = search(&LL, item.id);
            if (pre_node != NULL && pre_node2 == NULL) {
              
                insert(&LL, pre_node, item);
            }
            else if (pre_node = NULL) {
               
                printf("삽입 실패: 학번 %d인 학생을 찾을 수 없음\n", pre_id);
            }
            else if (pre_node2 != NULL) {
              
                printf("삽입 실패: 학번 %d인 학생이 존재합니다.\n", item.id);
            }
        }
        else if (strcmp(command, "delete") == 0) {
           
            command = strtok(NULL, " ");
            id = atoi(command);
            np = search(&LL, id);
            if (np)
            {
                delete(&LL, id);
            }
            else
            {
                printf("삭제 불가");
            }
        }
        else if (strcmp(command, "reverse") == 0) {
          
            reverse(&LL);
        }
        else if (strcmp(command, "getLength") == 0) {
         
            printf("리스트의 길이: %d\n", getLength(&LL));
        }
        else if (strcmp(command, "exit") == 0) {
         
            break;
        }
        else {
         
            printf("잘못된 명령어입니다.\n");
        }
    }
    return 0;
}
