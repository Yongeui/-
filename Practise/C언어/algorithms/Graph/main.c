#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include <memory.h>
#include<time.h>

#define Max_vertex 100   
#define INFINITE_VAL 10000 
#define NUM_IMPOSSIBLE -99999  
typedef struct stnode* type_node_ptr;
typedef struct stnode {
    int no;
    double length;
    type_node_ptr link;
} type_node;
int Num_vertices;
double Cost_mat[Max_vertex][Max_vertex];
type_node_ptr Adj_list[Max_vertex];

double dist[Max_vertex];
int visited[Max_vertex];
int pred[Max_vertex];
int S[Max_vertex];

void addq(int queue[], int* rear, int item);
void breadth_first(int start);
int choose(int number_of_vertex);
int deleteq(int queue[], int* front, int rear);
void depth_first(int current);
void dijkstra(int v0);
int empty_queue(int front, int rear);
int exist_in_queue(int queue[], int front, int rear, int v);
void main();
void print_paths_dfs_bfs(int start, int desti);
void print_paths_dijkstra(int start, int desti);
void read_and_construct_graph(char* fileName);
int read_number(char buf[], int* pos);
void read_word(char buf[], int* pos, char name[]);
void read_and_construct_graph(FILE* fps);

void addq(int queue[], int* rear, int item) {
    if (*rear == Max_vertex - 1) {
        printf("adding to queue has failed since queue is full.\n");
        return;
    }
    else
        queue[++ * rear] = item;
}

int deleteq(int queue[], int* front, int rear)
{
    if (*front == rear) {
        printf("delete failed since queue is empty.\n");
        return -999;
    }
    else
        return queue[++ * front];
}

int choose(int number_of_vertex) {
    int i, j, min, minpos;
    for (i = 0; i < number_of_vertex; i++) {
        if (S[i] == 0)
            break;
    }
    if (i == number_of_vertex)
        return -1;
    minpos = i;
    min = dist[i];
    for (j = i + 1; j < number_of_vertex; j++)
        if (S[j] == 0 && dist[j] < min) {
            min = dist[j];
            minpos = j;
        }
    return minpos;
}

int empty_queue(int front, int rear) {
    if (front == rear) return 1;
    else return 0;
}

int exist_in_queue(int queue[], int front, int rear, int v) {
    int i, answer = 0;
    for (i = front + 1; i <= rear; i++) {
        if (queue[i] == v)
            answer = 1;
    }
    return answer;
}

int read_number(char buf[], int* pos)
{
    int n = 0, i = 0;
    char numstr[30];
    while (buf[*pos] == ' ' || buf[*pos] == ',')
        (*pos)++;
    while (isdigit(buf[*pos]))
    {
        numstr[i] = buf[*pos]; i++; (*pos)++;
    }
    numstr[i] = '\0';
    if (i == 0)
    {
        printf("수를 읽지 못하였어요. \n");
        return NUM_IMPOSSIBLE;
    }
    else {
        n = atoi(numstr);
        return n;
    }
}

void read_word(char buf[], int* pos, char name[])
{
    int i = 0;
    while (buf[*pos] == ' ' || buf[*pos] == ',') (*pos)++;
    while (buf[*pos] != ' ' && buf[*pos] != ',' && buf[*pos] != '\0')
    {
        name[i] = buf[*pos];
        i++; (*pos)++;
    }
    name[i] = '\0';
    return;
}

void depth_first(int current) {
    visited[current] = 1;
    type_node_ptr ptr = Adj_list[current];
    while (ptr != NULL) {
        int next = ptr->no;
        if (!visited[next]) {
            pred[next] = current;
            depth_first(next);
        }
        ptr = ptr->link;
    }
}


void read_and_construct_graph(FILE* fps) {
    char line[500];
    char str[10];
    char* ret;
    int i, k, m, leng, nr;
    int v, dv;
    double co;
    type_node_ptr nptr, curr;
    ret = fgets(line, 500, fps);
    if (ret == NULL) {
        printf("Read a line error: no line for the number of vertices.\n");
        getchar();
    }

    nr = sscanf(line, "%d", &Num_vertices);
    if (nr != 1) {
        printf("Read error: number of vertices.\n");
        getchar();
    }
    int num_adj_lines = 0;
    do {
        ret = fgets(line, 500, fps);
        if (!ret) {
            break;
        }
        leng = strlen(line);
        if (leng == 0) break;
        i = 0;
        while (i < leng && !isdigit(line[i]))
            i++;
        k = 0;
        while (i < leng && isdigit(line[i])) {
            str[k] = line[i];
            i++; k++;
        }
        str[k] = '\0';
        if (k == 0) break;
        v = atoi(str);
        num_adj_lines++;
        do {
            while (i < leng && !isdigit(line[i]))
                i++;
            if (i >= leng) {
                break;
            }
            k = 0;
            while (i < leng && isdigit(line[i])) {
                str[k] = line[i];
                i++; k++;
            }
            str[k] = '\0';
            dv = atoi(str);
            k = 0;
            while (i < leng && !isdigit(line[i]))
                i++;
            while (i < leng && (isdigit(line[i]) || line[i] == '.')) {
                str[k] = line[i];
                i++; k++;
            }
            str[k] = '\0';
            if (k == 0) {
                printf("오류: 있어야 할 간선의 비용이 안나옴.\n");
                getchar();
            }
            co = atof(str);
            Cost_mat[v][dv] = co;
            nptr = (type_node_ptr)malloc(sizeof(type_node));
            nptr->no = dv; nptr->length = co; nptr->link = NULL;
            curr = Adj_list[v];
            if (curr == NULL)
                Adj_list[v] = nptr;
            else {
                while (curr->link)
                    curr = curr->link;
                curr->link = nptr;
            }
        } while (1);
    } while (1);
    if (Num_vertices != num_adj_lines) {
        printf("인접정보의 줄 수가 총 정점수 와 다르다. (강제종료 하시오.) \n");
        getchar();
    }
    fclose(fps);
}

void breadth_first(int start)
{
    type_node_ptr w;
    int v;
    int queue[Max_vertex];
    int front = -1, rear = -1;
    addq(queue, &rear, start);
    pred[start] = -1;
    while (!empty_queue(front, rear))
    {
        v = deleteq(queue, &front, &rear);
        visited[v] = 1;
        for (w = Adj_list[v]; w; w = w->link)
        {
            if (!visited[w->no] && exist_in_queue(queue, front, rear, w->no) == 0)
            {
                addq(queue, &rear, w->no);
                pred[w->no] = v;

            }
        }
    }
}

void dijkstra(int v0)
{
    int i, u, w, curr;

    for (i = 0; i < Num_vertices; i++)
    {
        if (i == v0)
            continue;
        S[i] = 0;
        dist[i] = Cost_mat[v0][i];
        if (Cost_mat[v0][i] < INFINITE_VAL)
        {
            pred[i] = v0;
        }
        else
        {
            pred[i] = -1;
        }
    }
    S[v0] = 1;
    dist[v0] = 0;
    pred[v0] = -1;

    for (i = 0; i < Num_vertices - 1; i++)
    {
        u = choose(Num_vertices);
        if (u == -1)
        {
            printf("Logic error. 모두 S에 들어있는데 없는것 중 최소를 찾으려고 함.\n");
            getchar();
        }
        if (dist[u] == INFINITE_VAL)
        {
            break;
        }
        S[u] = 1;
        for (w = 0; w < Num_vertices; w++)
        {
            if (S[w] == 0)
            {
                if (dist[u] + Cost_mat[u][w] < dist[w])
                {
                    dist[w] = dist[u] + Cost_mat[u][w];
                    pred[w] = u;
                }
            }

        }
    }


}

void print_paths_dijkstra(int start, int desti)
{
    int d, fr, to, leng, curr;
    int rpath[Max_vertex];

    if (desti == -1)
    {
        fr = 0;
        to = Num_vertices - 1;
    }
    else {
        fr = desti;
        to = desti;
    }
    printf("\n");

    for (d = fr; d <= to; d++)
    {
        if (d == start)
        {
            continue;
        }
        curr = d;
        leng = 0;
        do
        {
            rpath[leng] = curr;
            leng++;
            curr = pred[curr];
        } while (curr != -1);

        printf("%d에서 %d로의 최단 경로 : ", start, d);
        if (leng <= 1)
        {
            printf("경로가 없음.\n");
            continue;
        }

        for (curr = leng - 1; curr >= 0; curr--)
        {
            printf(" %d,", rpath[curr]);
        }

        printf("경로길이 = %6.2f\n", dist[d]);
    }
}

void print_paths_dfs_bfs(int start, int desti)
{
    int d, fr, to, leng, curr;
    int rpath[Max_vertex];
    if (desti == -1)
    {
        fr = 0;
        to = Num_vertices - 1;
    }
    else
    {
        fr = desti;
        to = desti;
    }
    printf("\n");
    for (d = fr; d <= to; d++)
    {
        if (d == start)
        {
            continue;
        }
        curr = d; leng = 0;
        do {
            rpath[leng] = curr;
            leng++;
            curr = pred[curr];
        } while (curr != -1);

        printf("%d 에서 %d로의 경로 : ", start, d);

        if (leng <= 1) {
            printf("경로가 없음.\n");
            continue;
        }

        for (curr = leng - 1; curr >= 0; curr--)
        {
            printf(" %d,", rpath[curr]);
        }
        printf(".\n");
    }
}

void main() {
    int i, j, start_vertex, destination_vertex;
    int ib;
    char buffer[100], command[30], sub[10], filename[100];
    FILE* fps;
    printf("\n그래프 데이터 파일 이름은? ");
    gets(filename);
    fps = fopen(filename, "r");
    if (!fps) {
        printf("파일 열기 실패.\n");
        return;
    }
    for (i = 0; i < Max_vertex; i++) {
        Adj_list[i] = NULL;
        for (j = 0; j < Max_vertex; j++) {
            Cost_mat[i][j] = INFINITE_VAL;
        }
    }
    read_and_construct_graph(fps);
    while (1) {
        for (i = 0; i < Max_vertex; i++) {
            visited[i] = 0; pred[i] = -1; S[i] = 0;
        }
        printf("\n명령문종류: /*dfs a 0 / dfs s 0 7 / bfs a 0 / bfs s 0 7 /*/ dij a 0 / dij s  0 7 / exit.\n");
        printf("명령문을 넣으시오> ");
        gets(buffer);
        ib = 0;
        read_word(buffer, &ib, command);
        if (strlen(command) == 0) {
            printf("명령오류. \n");
            continue;
        }
        if (strcmp(command, "dij") == 0) {
            read_word(buffer, &ib, sub);
            if (strlen(command) == 0)
                continue;
            if (sub[0] == 'a') {
                start_vertex = read_number(buffer, &ib);
                if (start_vertex == NUM_IMPOSSIBLE) {
                    printf("Wrong command.\n"); continue;
                }
                dijkstra(start_vertex);
                print_paths_dijkstra(start_vertex, -1);
            }
            else if (sub[0] == 's') {
                start_vertex = read_number(buffer, &ib);
                if (start_vertex == NUM_IMPOSSIBLE) {
                    printf("Wrong command.\n"); continue;
                }
                destination_vertex = read_number(buffer, &ib);
                if (destination_vertex == NUM_IMPOSSIBLE) {
                    printf("Wrong command.\n"); continue;
                }
                dijkstra(start_vertex);
                print_paths_dijkstra(start_vertex, destination_vertex);
            }
            else {
                printf("명령 오류.\n");
                continue;
            }
        }
        else if (strcmp(command, "dfs") == 0) {
            read_word(buffer, &ib, sub);
            if (strlen(command) == 0)
                continue;
            if (sub[0] == 'a') {
                start_vertex = read_number(buffer, &ib);
                if (start_vertex == NUM_IMPOSSIBLE) {
                    printf("Wrong command.\n"); continue;
                }
                pred[start_vertex] = -1;
                depth_first(start_vertex);
                print_paths_dfs_bfs(start_vertex, -1);
            }
            else if (sub[0] == 's') {
                start_vertex = read_number(buffer, &ib);
                if (start_vertex == NUM_IMPOSSIBLE) {
                    printf("Wrong command.\n"); continue;
                }
                destination_vertex = read_number(buffer, &ib);
                if (destination_vertex == NUM_IMPOSSIBLE) {
                    printf("Wrong command.\n"); continue;
                }
                pred[start_vertex] = -1;
                depth_first(start_vertex);
                print_paths_dfs_bfs(start_vertex, destination_vertex);
            }
            else {
                printf("sub 명령 오류.\n");
                continue;
            }
        } // dfs 
        else if (strcmp(command, "bfs") == 0) {
            read_word(buffer, &ib, sub);
            if (strlen(command) == 0)
                continue;
            if (sub[0] == 'a') {
                start_vertex = read_number(buffer, &ib);
                if (start_vertex == NUM_IMPOSSIBLE) {
                    printf("Wrong command.\n"); continue;
                }
                breadth_first(start_vertex);
                print_paths_dfs_bfs(start_vertex, -1);
            }
            else if (sub[0] == 's') {
                start_vertex = read_number(buffer, &ib);
                if (start_vertex == NUM_IMPOSSIBLE) {
                    printf("Wrong command.\n"); continue;
                }
                destination_vertex = read_number(buffer, &ib);
                if (destination_vertex == NUM_IMPOSSIBLE) {
                    printf("Wrong command.\n"); continue;
                }
                breadth_first(start_vertex);
                print_paths_dfs_bfs(start_vertex, destination_vertex);
            }
            else {
                printf("sub 명령 오류.\n");
                continue;
            }
        }
        else if (strcmp(command, "exit") == 0) {
            break;
        }
        else {
            printf("명령오류. \n"); continue;
        }
    }
    printf("\n프로그램을 종료합니다.\n");
}
