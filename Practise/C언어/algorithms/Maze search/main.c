#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define m 12
#define p 12
#define Max_dir 8
#define Timestep 1000
#define MAX_STACKSIZE 100

typedef struct AAoff {
    short int vert;
    short int horiz;
} offsets;

typedef struct St_element {
    short int row;
    short int col;
    short int dir;
} ty_element;
ty_element stack[MAX_STACKSIZE];
ty_element reverse_stack[MAX_STACKSIZE];
typedef struct ListNode* listPointer;
typedef struct ListNode {
    ty_element data;
    listPointer link;
} listNode;

offsets move[Max_dir]{ {-1, 0 }, { -1, 1 }, { 0,1 }, { 1, 1 }, { 1,0 }, { 1, -1 }, { 0, -1 }, { -1, -1 } };

int maze[m + 2][p + 2];
int mark[m + 2][p + 2];

void gotoxy(int x, int y)
{
    COORD Pos = { x ,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void push(listPointer* top, ty_element pos)
{
    listPointer temp = (listPointer)malloc(sizeof(listNode));
    temp->data = pos;
    temp->link = *top;
    *top = temp;
}
ty_element pop(listPointer* top)
{
    listPointer temp = *top;
    ty_element pdata = temp->data;
    *top = temp->link;
    free(temp);
    return pdata;
}
void reverse(listPointer* top)
{
    listPointer temp, curr, next;

    temp = NULL;
    curr = *top;
    do {
        next = curr->link;
        curr->link = temp;
        temp = curr;
        curr = next;
    } while (curr);
    *top = temp;
}
int path(int sy, int sx, int dy, int dx)
{
    listPointer top = NULL;
    listPointer rtop = NULL;
    int i = 0, j = 0, row = 0, col = 0, nextRow = 0, nextCol = 0, dir = 0, basex = 0, basey = 0, ocount = 0;
    int found = 0, num_bktrack = 0, path_length = 0;
    int EXIT_ROW = dy, EXIT_COL = dx;
    ty_element position;

    if (maze[sy][sx] == 1 || maze[dy][dx] == 1)
    {
        printf("입력오류 : 출발점이나 목표점이 막힌 셀입니다.\n");
        return 0;
    }

    CONSOLE_SCREEN_BUFFER_INFO presentCur;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
    basex = presentCur.dwCursorPosition.X;
    basey = presentCur.dwCursorPosition.Y;

    for (i = 0; i < m + 2; i++)
    {
        for (j = 0; j < p + 2; j++)
        {
            gotoxy(j + basex, i + basey);
            printf("%1d", maze[i][j]);
        }
    }

    position.row = sy;
    position.col = sx;
    position.dir = 0;
    push(&top, position);

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < p; j++)
        {
            mark[1 + i][1 + j] = 0;
        }
        printf("\n");
    }

    while (!found && top)
    {
        position = pop(&top);
        row = position.row;
        col = position.col;
        dir = position.dir;

        while (dir < 8 && !found)
        {
            nextRow = row + move[dir].vert;
            nextCol = col + move[dir].horiz;
            gotoxy(col + basex, row + basey);
            
    if (row == sy && col == sx)
            {
                printf(">");
            }
            else
            {
                printf("*");
            }
            if (nextRow == EXIT_ROW && nextCol == EXIT_COL)
            {
                mark[row][col] = 1;
                gotoxy(nextCol + basex, nextRow + basey);
                printf("<");
                position.row = row; position.col = col;
                position.dir = ++dir;
                push(&top, position);
                found = TRUE;
            }
            else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol])
            {

                position.row = row;
                position.col = col;
                position.dir = ++dir;
                push(&top, position);
                mark[nextRow][nextCol] = 1;
                row = nextRow;
                col = nextCol;
                dir = 0;
            }
            else
            {
                dir++;
                if (dir == 8)
                {
                    mark[row][col] = 1;
                    gotoxy(col + basex, row + basey);
                    printf("$");
                    num_bktrack++;
                    Sleep(Timestep / 10);
                }
            }
            Sleep(Timestep / 10);
        }
    }

    gotoxy(basex, basey + m + 2);
    if (found)
    {
        printf("\n찾은 경로(row,col):\n");
        path_length = 0;
        reverse(&top);
        while (top)
        {

            position = pop(&top);
            if (ocount == 6)
            {
                printf("\n");
                ocount = 0;
            }
            ocount++;
            printf("[%2d,%2d]", position.row, position.col);
            path_length++;
        }
        path_length++;
        printf("[%2d,%2d]\n", dy, dx);
        printf("경로길이 = %d, 백트래킹수= %d", path_length, num_bktrack);
    }
    else
    {
        printf("경로없습니다\n");
    }

}

int main()
{
    
    FILE* fp = NULL;
    fp = fopen("maze_14_2.txt", "r");

    int starty; int startx;
    int endy; int endx;
    int res;
    int first, second, third, four;
    while (TRUE) {
        int i = 0;
        while (!feof(fp))
        {
            for (int j = 0; j < p + 2; j++)
            {
                fscanf(fp, "%d", &maze[i][j]);
            }
            i++;
        }

        printf("\n");
        printf("출발점, 목표점은?(4개의 정수; 종료는 Control+DEnter): ");
        res = scanf("%d%d%d%d", &starty, &startx, &endy, &endx);
        if (res != 4) break;
        path(starty, startx, endy, endx);
    }
}
