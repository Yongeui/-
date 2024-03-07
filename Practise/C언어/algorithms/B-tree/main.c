#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define D2	2
#define D	D2/2
#define MAX 100
#define false 0
#define true 1

typedef struct element {
	char name[100];
	int nleng;
}ele;

typedef struct node* nodeptr;
typedef struct node {
	ele rec[D2];
	nodeptr ptr[D2 + 1];
	int fill_cnt;
}node;

typedef struct big_node {
	ele rec[D2 + 1];
	nodeptr ptr[D2 + 2];
}big_node;

typedef struct two_Bn {
	ele rec[2 * D2];
	nodeptr ptr[2 * D2 + 1];
} two_Bnode;

nodeptr ROOT = NULL;
nodeptr stack[MAX];
int top = -1;

void push(nodeptr node);
nodeptr pop();
void insert_btree();
int insert_arec(ele in_rec);
void insert_pair_into_curr_node(nodeptr curr, ele in_rec, nodeptr child);
big_node prepare_big_node(nodeptr curr, ele in_rec, nodeptr child);
void split(nodeptr curr, nodeptr new_ptr, big_node bnode);
nodeptr retrieve(char*, int*);
void seq_scan_btree(nodeptr curr);
int B_tree_deletion(char*);
void redistribution(nodeptr father, nodeptr l_sibling, nodeptr r_sibling, char wcase, int j);
int merge(nodeptr father, nodeptr curr, nodeptr r_sibling, nodeptr l_sibling);
int total_height = 0;

int main(void) {
	char line[200] = { 0 }, * res_gets;
	ele one_rec;
	char name_s[100] = { 0 };
	int lleng;
	int i, k, r;
	nodeptr tp;

	insert_btree();

	while (1) {
		fflush(stdin);
		printf("\n명령을 넣으시오\n");
		printf("insert: i 이름  / delete : d 이름  /  retrieve : r 이름  /  전체출력: p   /  종료: e  >> ");
		res_gets = gets(line);
		if (!res_gets)
			break;

		lleng = strlen(line);
		if (lleng <= 0)
			continue;

		i = 1;
		if (line[0] == 'E' || line[0] == 'e') {
			printf("종료명령이 들어왔음!\n\n");   return 0;
		}
		else if (line[0] == 'I' || line[0] == 'i') {
			k = 0;
			while (line[i] == ' ')	i++;
			while (i < lleng) {
				name_s[k] = line[i]; k++; i++;
			}
			name_s[k] = '\0';

			if (strlen(name_s) == 0)
				continue;

			strcpy(one_rec.name, name_s);
			one_rec.nleng = strlen(name_s);

			top = -1;
			r = insert_arec(one_rec);
			if (r == 0)
				printf("삽입 실패.\n");
			else
				printf("삽입 성공.\n");
		}
		else if (line[0] == 'D' || line[0] == 'd') {
			k = 0;
			while (line[i] == ' ')	i++;
			while (i < lleng) {
				name_s[k] = line[i]; k++; i++;
			}
			name_s[k] = '\0';

			if (strlen(name_s) == 0)
				continue;

			r = B_tree_deletion(name_s);
			if (r == 0)
				printf("삭제요청 받은 키의 레코드가 존재하지 않음.\n");
			else
				printf("삭제 성공.\n");
		}
		else if (line[0] == 'R' || line[0] == 'r') {
			k = 0;
			while (line[i] == ' ')	i++;
			while (i < lleng) {
				name_s[k] = line[i]; k++; i++;
			}
			name_s[k] = '\0';

			if (strlen(name_s) == 0)
				continue;

			tp = retrieve(name_s, &i);
			if (tp)
				printf("탐색성공.  Name: %s,  길이: %d\n", tp->rec[i].name, tp->rec[i].nleng);
			else
				printf("탐색요청 받은 키를 가진 레코드가 존재하지 않음.\n");
		}
		else if (line[0] == 'P' || line[0] == 'p') {
			if (ROOT)
				seq_scan_btree(ROOT);
		}
		else
			printf("input error \n");
	}
	return 0;
}

void push(nodeptr node) {
	if (top >= MAX - 1) {
		printf("stack is full\n");
		return;
	}
	stack[++top] = node;
}

nodeptr pop() {
	if (top < 0) {
		printf("stack is empty\n");
		return NULL;
	}
	return stack[top--];
}

void insert_pair_into_curr_node(nodeptr curr, ele in_rec, nodeptr child) {
	int i, j;

	for (i = 0; i < curr->fill_cnt; i++) {
		int cmp = strcmp(in_rec.name, curr->rec[i].name);
		if (cmp == 0) {
			return;
		}
		else if (cmp < 0) {
			for (j = curr->fill_cnt; j > i; j--) {
				curr->rec[j] = curr->rec[j - 1];
				curr->ptr[j + 1] = curr->ptr[j];
			}
			curr->rec[i] = in_rec;
			curr->ptr[i + 1] = child;
			curr->fill_cnt++;
			return;
		}
	}

	curr->rec[curr->fill_cnt] = in_rec;
	curr->ptr[curr->fill_cnt + 1] = child;
	curr->fill_cnt++;
	return;
}

big_node prepare_big_node(nodeptr curr, ele in_rec, nodeptr child) {
	big_node bnode;
	int i, j;

	for (i = 0; i < D2; i++) {
		bnode.rec[i] = curr->rec[i];
		bnode.ptr[i] = curr->ptr[i];
	}
	bnode.ptr[D2] = curr->ptr[D2];

	for (i = 0; i < D2; i++) {
		int cmp = strcmp(in_rec.name, bnode.rec[i].name);
		if (cmp < 0) {
			for (j = D2 - 1; j >= i; j--) {
				bnode.rec[j + 1] = bnode.rec[j];
				bnode.ptr[j + 2] = bnode.ptr[j + 1];
			}
			bnode.rec[i] = in_rec;
			bnode.ptr[i + 1] = child;
			return bnode;
		}
	}

	bnode.rec[D2] = in_rec;
	bnode.ptr[D2 + 1] = child;
	return bnode;
}

void split(nodeptr curr, nodeptr new_ptr, big_node bnode) {
	int i;
	for (i = 0; i < D; i++) {
		curr->rec[i] = bnode.rec[i];
		curr->ptr[i] = bnode.ptr[i];
	}
	curr->ptr[D] = bnode.ptr[D];

	for (i = 0; i < D2 - D; i++) {
		new_ptr->rec[i] = bnode.rec[i + D + 1];
		new_ptr->ptr[i] = bnode.ptr[i + D + 1];
	}
	new_ptr->ptr[i] = bnode.ptr[D2 + 1];
	curr->fill_cnt = D;
	new_ptr->fill_cnt = D2 - D;

	return;
}

int insert_arec(ele in_rec) {
	int i, j;
	nodeptr curr, child, new_ptr, tptr = NULL;
	big_node bnode;

	if (!ROOT) {
		ROOT = (nodeptr)malloc(sizeof(node));
		ROOT->rec[0] = in_rec;
		ROOT->ptr[0] = ROOT->ptr[1] = NULL;
		ROOT->fill_cnt = 1;
		return 1;
	}

	curr = ROOT;

	do {
		for (i = 0; i < curr->fill_cnt; i++) {
			if (strcmp(in_rec.name, curr->rec[i].name) < 0)
				break;
			else if (strcmp(in_rec.name, curr->rec[i].name) == 0)
			{
				printf("동일키 이미 존재로 안 넣음: %s\n", in_rec.name);
				return 0;
			}
		}
		child = curr->ptr[i];
		if (child) {
			push(curr);
			curr = child;
		}
		else
			break;
	} while (1);

	do {
		if (curr->fill_cnt < D2) {
			insert_pair_into_curr_node(curr, in_rec, child);
			return 1;
		}
		else {
			bnode = prepare_big_node(curr, in_rec, child);
			new_ptr = (nodeptr)malloc(sizeof(node));
			split(curr, new_ptr, bnode);

			in_rec = bnode.rec[D];
			child = new_ptr;

			if (top >= 0) {
				curr = pop();
			}
			else {
				tptr = (nodeptr)malloc(sizeof(node));
				tptr->rec[0] = in_rec;
				tptr->ptr[0] = ROOT;
				tptr->ptr[1] = child;
				tptr->fill_cnt = 1;
				ROOT = tptr;
				total_height++;
				return 2;
			}
		}
	} while (1);

	return 0;
}

void insert_btree() {
	FILE* fp;
	ele data;
	char line[200] = { 0 }; // 수정 1
	char* ret_fgets;
	int r;
	int n = 0, lineleng;
	int check, count = 0;

	fp = fopen("Com_names1.txt", "r");
	if (!fp) {
		printf("Cannot open this file :  Com_names1.txt\n");
		scanf("%d", &check);
	}

	ROOT = NULL;
	while (1) {
		ret_fgets = fgets(line, 200, fp);
		if (!ret_fgets)
			break;

		lineleng = strlen(line);
		if (lineleng - 1 >= 100)
			continue;
		line[lineleng - 1] = '\0';

		strcpy(data.name, line);
		data.nleng = strlen(line);

		top = -1;
		r = insert_arec(data);
		if (r != 0)
			count++;
	}

	fp = fopen("Com_names2.txt", "r");
	if (!fp) {
		printf("Cannot open this file :  Com_names2.txt\n");
		scanf("%d", &check);
	}

	while (1) {
		ret_fgets = fgets(line, 200, fp);
		if (!ret_fgets)
			break;

		lineleng = strlen(line);
		if (lineleng - 1 >= 100)
			continue;
		line[lineleng - 1] = '\0';

		strcpy(data.name, line);
		data.nleng = strlen(line);

		top = -1;
		r = insert_arec(data);
		if (r != 0)
			count++;
	}

	printf("삽입 성공한 레코드 수 = %d \n\n", count);
	fclose(fp);
}

nodeptr retrieve(char* skey, int* idx_found) {
	nodeptr curr = ROOT;
	nodeptr P;
	int i;
	do {
		for (i = 0; i < curr->fill_cnt; i++) {
			if (strcmp(skey, curr->rec[i].name) < 0)
				break;
			else if (strcmp(skey, curr->rec[i].name) == 0) {
				*idx_found = i;
				return curr;
			}
		}
		P = curr->ptr[i];
		if (P) {
			curr = P;
		}
	} while (P);

	return NULL;
}

void seq_scan_btree(nodeptr curr) {
	int i;
	int n;
	if (curr) {
		n = curr->fill_cnt;
		for (i = 0; i < n; i++) {
			seq_scan_btree(curr->ptr[i]);
			printf("Name : %s\n", curr->rec[i].name);
		}
		seq_scan_btree(curr->ptr[i]);
		return;
	}
	else
		return;
}

void redistribution(nodeptr father, nodeptr l_sibling, nodeptr r_sibling, char wcase, int j) {
	int i, k, m, n, h;
	two_Bnode twoB;

	if (wcase == 'L')
		j = j - 1;
	else if (wcase == 'R')
		j = j;

	i = 0;
	if (i < D2) {
		twoB.rec[i] = father->rec[j];
		i++;
	}

	for (k = 0; k < l_sibling->fill_cnt && i < 2 * D2; k++, i++) {
		twoB.ptr[i] = l_sibling->ptr[k]; twoB.rec[i] = l_sibling->rec[k];
	}
	if (i < 2 * D2 + 1)
		twoB.ptr[i] = l_sibling->ptr[k];

	for (k = j + 1; k < father->fill_cnt && i < 2 * D2; k++, i++) {
		twoB.ptr[i] = father->ptr[k];
		twoB.rec[i] = father->rec[k - 1];
	}
	if (i < 2 * D2 + 1)
		twoB.ptr[i] = father->ptr[k];

	for (k = 0; k < r_sibling->fill_cnt && i < 2 * D2; k++, i++) {
		twoB.ptr[i] = r_sibling->ptr[k];
		twoB.rec[i] = r_sibling->rec[k];
	}

	h = i / 2;

	for (m = 0; m < h; m++) {
		l_sibling->ptr[m] = twoB.ptr[m];
		l_sibling->rec[m] = twoB.rec[m];
	}

	l_sibling->ptr[m] = twoB.ptr[m];
	l_sibling->fill_cnt = h;

	n = 0;
	n++;
	for (m = 0; m < (i - h - 1); m++, n++) {
		r_sibling->ptr[m] = twoB.ptr[n]; r_sibling->rec[m] = twoB.rec[n];
	}
	r_sibling->ptr[m] = twoB.ptr[n]; r_sibling->fill_cnt = i - h - 1;

	r_sibling->ptr[n] = twoB.ptr[m];
	r_sibling->fill_cnt = i - h - 1;

	if (j < D2)
		father->rec[j] = twoB.rec[h];
	father->ptr[j + 1] = r_sibling;
	return;
}

int merge(nodeptr father, nodeptr curr, nodeptr r_sibling, nodeptr l_sibling) {
	int i, j, k;
	nodeptr leftptr, rightptr;

	if (r_sibling) {
		leftptr = curr;
		rightptr = r_sibling;
	}
	else {
		leftptr = l_sibling;
		rightptr = curr;
	}

	for (i = leftptr->fill_cnt, k = 0; k < rightptr->fill_cnt; i++, k++) {
		leftptr->rec[i] = rightptr->rec[k];
		leftptr->ptr[i + 1] = rightptr->ptr[k + 1];
	}

	leftptr->fill_cnt += rightptr->fill_cnt;

	for (j = 0; j <= father->fill_cnt; j++) {
		if (father->ptr[j] == rightptr) {
			free(rightptr);
			break;
		}
	}
	if (father->fill_cnt == 0) {
		free(rightptr);
	}

	return j;
}

int B_tree_deletion(char* out_key) {
	nodeptr curr, r_sibling, l_sibling, father, Pt, leftptr, rightptr;
	int i, j, k, r_OK, l_OK, found;
	curr = ROOT;

	found = 0;
	do {
		for (i = 0; i < curr->fill_cnt; i++)
			if (strcmp(out_key, curr->rec[i].name) < 0)
				break;
			else if (strcmp(out_key, curr->rec[i].name) == 0) {
				found = 1;
				break;
			}
		if (found)
			break;
		else {
			Pt = curr->ptr[i];
			if (Pt) {
				push(curr);
				curr = Pt;
			}
			else
				return 0;
		}
	} while (1);

	if (curr->ptr[0]) {
		Pt = curr->ptr[i + 1];
		push(curr);
		while (Pt->ptr[0]) {
			push(Pt);
			Pt = Pt->ptr[0];
		}
		curr->rec[i] = Pt->rec[0];

		curr = Pt;
		i = 0;
	}

	do {
		for (j = i + 1; j < curr->fill_cnt; j++) {
			curr->rec[j - 1] = curr->rec[j];
			curr->ptr[j] = curr->ptr[j + 1];
		}
		curr->fill_cnt--;

		if (curr == ROOT) {
			if (curr->fill_cnt == 0) {
				ROOT = ROOT->ptr[0];
				free(curr);
			}
			return 1;
		}

		if (curr->fill_cnt >= D)
			return 2;

		father = pop();

		for (j = 0; j <= father->fill_cnt; j++)
			if (father->ptr[j] == curr)
				break;

		if (j >= 1)
			l_sibling = father->ptr[j - 1];
		else
			l_sibling = NULL;

		if (j < father->fill_cnt)
			r_sibling = father->ptr[j + 1];
		else
			r_sibling = NULL;

		r_OK = 0;  l_OK = 0;
		if (r_sibling && r_sibling->fill_cnt > D)
			r_OK = 1;
		else if (l_sibling && l_sibling->fill_cnt > D)
			l_OK = 1;

		if (r_OK || l_OK) {
			if (r_OK) {
				redistribution(father, curr, r_sibling, 'R', j);
			}
			else if (l_OK) {
				redistribution(father, l_sibling, curr, 'L', j);
			}
			printf("Redistribution has been done.\n");
			return 3;
		}
		else {
			i = merge(father, curr, r_sibling, l_sibling);
			printf("Merging has been done.\n");

			curr = father;
		}
	} while (1);
}
