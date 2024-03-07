#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node* nodeptr;
typedef struct node {
    char ch;
    long int bp; 
    nodeptr right; 
    nodeptr below;  
} nodetype;

typedef struct record {
    char word[50];
    int widx;
    int wfreq;
} ty_rec;

typedef struct correct_result {
    char word[100];  
    int ns, nd, ni, nt;
    float penalty;
} ty_correction;

ty_correction cwords[20000];
int nres = 0;

int found_perfect_match = 0;

nodeptr ROOT_TRIE = NULL; 

void find_with_spell_correction(nodeptr root_sub_trie, char key[], char corr_key[], int ki, int ci, int n_s, int n_d, int n_i, int n_t);

int search_trie(char key[], nodeptr* curr, nodeptr* prev) {
    int i = 0;
    *prev = NULL;
    *curr = ROOT_TRIE;

    if (ROOT_TRIE == NULL) {
        return 0;
    }

    do {

        while (key[i] != '\0' && (*curr)->ch == key[i]) {
            (*prev) = (*curr);
            i++;
            (*curr) = (*curr)->below;
        }

        if ((*curr)->ch == '\0' && key[i] == '\0') return -1;
        while ((*curr) != NULL && (*curr)->ch < key[i]) {
            (*prev) = (*curr);
            (*curr) = (*curr)->right;
        }

        if ((*curr) == NULL || (*curr)->ch > key[i]) return i;
    } while (1);
}

nodeptr hang_down(char key[], nodeptr curr, int i) {
    nodeptr new_node;

    while (key[i] != '\0') {
        new_node = (nodeptr)malloc(sizeof(nodetype));
        new_node->ch = key[i];
        new_node->right = NULL;
        i++;
        curr->below = new_node;
        curr = new_node;
    }

    new_node = (nodeptr)malloc(sizeof(nodetype));
    new_node->ch = '\0';
    new_node->right = NULL;
    new_node->below = NULL;
    curr->below = new_node;
    return new_node;
}

float get_penalty(int n_s, int n_d, int n_i, int n_t) {
    return n_s * 1.1 + n_d * 1.3 + n_i * 1.6 + n_t * 1.9;
}

nodeptr insert_trie(char key[50]) {
    int result;
    int i = 0;
    nodeptr new_node;
    nodeptr curr, prev;
    result = search_trie(key, &curr, &prev);
    if (result == -1) {
        printf("E: key already exist\n");
        return NULL;
    }
    new_node = (nodeptr)malloc(sizeof(nodetype));
    if (ROOT_TRIE == NULL) {
        new_node->ch = key[0];
        new_node->right = NULL;
        ROOT_TRIE = new_node;
        return hang_down(key, new_node, 1);
    }
    if (prev == NULL) {
        new_node->ch = key[0];
        new_node->right = ROOT_TRIE;
        ROOT_TRIE = new_node;
        return hang_down(key, new_node, 1);
    }
    if (prev->right == curr) {
        new_node->ch = key[result];
        new_node->right = curr;
        prev->right = new_node;
        return hang_down(key, new_node, result + 1);
    }
    if (prev->below == curr) {
        new_node->ch = key[result];
        new_node->right = curr;
        prev->below = new_node;
        return hang_down(key, new_node, result + 1);
    }

    printf("Critical Error: Logical error!!!!!!!\n");
    return NULL;
}

void substitution(nodeptr root_sub_trie, char key[], char corr_key[], int ki,
    int ci, int n_s, int n_d, int n_i, int n_t) {
    nodeptr np, start_ptr;
    int temp;
    char new_corr_key[100];
    strcpy(new_corr_key, corr_key);
    np = root_sub_trie;
    do {
        start_ptr = np->below;
        new_corr_key[ci] = np->ch;
        new_corr_key[ci + 1] = '\0';
        if (start_ptr) {
            find_with_spell_correction(start_ptr, key, new_corr_key, ki + 1, ci + 1,
                n_s + 1, n_d, n_i, n_t);
        }
        np = np->right;
    } while (np);
    return;
}

void deletion(nodeptr root_sub_trie, char key[], char corr_key[], int ki,
    int ci, int n_s, int n_d, int n_i, int n_t) {
    nodeptr np, start_ptr;
    int temp;
    char new_corr_key[100];
    strcpy(new_corr_key,
        corr_key);
    np = root_sub_trie;
    do {
        start_ptr = np->below;
        new_corr_key[ci] = np->ch;
        new_corr_key[ci + 1] = '\0';
        if (start_ptr) {
            find_with_spell_correction(start_ptr, key, new_corr_key, ki, ci + 1, n_s,
                n_d + 1, n_i, n_t);
        }
        np = np->right;
    } while (np);
    return;
}

void insertion(nodeptr root_sub_trie, char key[], char corr_key[], int ki,
    int ci, int n_s, int n_d, int n_i, int n_t) {
    nodeptr start_ptr;
    int temp;
    char new_corr_key[100];
    strcpy(new_corr_key,
        corr_key);
    start_ptr = root_sub_trie;

    if (start_ptr) {
        find_with_spell_correction(start_ptr, key, new_corr_key, ki + 1, ci, n_s,
            n_d, n_i + 1, n_t);
    }
    return;
}

void transposition(nodeptr root_sub_trie, char key[], char corr_key[], int ki,
    int ci, int n_s, int n_d, int n_i, int n_t) {
    nodeptr p, s;
    int temp;
    char new_corr_key[100];
    strcpy(new_corr_key,
        corr_key);
    p = root_sub_trie;
    do {
        if (p->ch == key[ki + 1]) {
            s = p->below;
            do {
                if (s->ch == key[ki]) {
                    new_corr_key[ci] = key[ki + 1];
                    new_corr_key[ci + 1] = key[ki];
                    ci++;
                    new_corr_key[ci + 1] = '\0';
                    ki++;
                    if (s->below) {
                        find_with_spell_correction(s->below, key, new_corr_key, ki + 1,
                            ci + 1, n_s, n_d, n_i, n_t + 1);
                    }
                    break;
                }
                else {
                    s = s->right;
                }
            } while (s);
            break;
        }
        else
            p = p->right;
    } while (p);
    return;
}

void find_with_spell_correction(nodeptr root_sub_trie, char key[],
    char corr_key[], int ki, int ci, int n_s,
    int n_d, int n_i, int n_t) {
    nodeptr curr = root_sub_trie;
    char new_corr_key[100], c;

    if (!curr) return;

    if (curr->ch == '\0' &&
        key[ki] == '\0') {
        strcpy(cwords[nres].word, corr_key);
        cwords[nres].penalty = get_penalty(n_s, n_d, n_i, n_t);
        cwords[nres].ns = n_s;
        cwords[nres].nd = n_d;
        cwords[nres].ni = n_i;
        cwords[nres].nt = n_t;
        if (get_penalty(n_s, n_d, n_i, n_t) == 0) found_perfect_match = 1;
        nres++;
        if (nres >= 20000) {
            printf("too many possible corrections.\n");
            c = getchar();
        }
        return;
    }

    while (curr && curr->ch < key[ki]) curr = curr->right;
    if (curr && curr->ch == key[ki]) {
        strcpy(new_corr_key, corr_key);
        new_corr_key[ci] = key[ki];
        new_corr_key[ci + 1] = '\0';
        find_with_spell_correction(curr->below, key, new_corr_key, ki + 1, ci + 1,
            n_s, n_d, n_i, n_t);
    }

    if (!found_perfect_match &&
        n_s + n_d + n_i + n_t <=
        2) {
        if (ki <= strlen(key) - 1)
            substitution(root_sub_trie, key, corr_key, ki, ci, n_s, n_d, n_i, n_t);
        if (ki <= strlen(key))
            deletion(root_sub_trie, key, corr_key, ki, ci, n_s, n_d, n_i, n_t);
        if (ki <= strlen(key) - 1)
            insertion(root_sub_trie, key, corr_key, ki, ci, n_s, n_d, n_i, n_t);
        if (ki <= strlen(key) - 2)
            transposition(root_sub_trie, key, corr_key, ki, ci, n_s, n_d, n_i, n_t);
    }
    return;
}

void sort_results(ty_correction cwords[]) {
    int i, j, midx;
    float minval;
    ty_correction temp;
    for (i = 0; i < nres - 1; i++) {
        minval = cwords[i].penalty;
        midx = i;
        for (j = i + 1; j < nres; j++) {
            if (cwords[j].penalty < minval) {
                minval = cwords[j].penalty;
                midx = j;
            }
        }
        temp = cwords[i];
        cwords[i] = cwords[midx];
        cwords[midx] = temp;
    }
}

int printed(char printed_words[][100], char aword[], int total) {
    int i, found = 0;
    for (i = 0; i < total; i++) {
        if (strcmp(printed_words[i], aword) == 0) return 1;
    }
    return 0;
}

void output_top_corrections() {
    char printed_words[500][100];
    int i, n_printed = 0, num_show = 10;
    int n_s, n_d, n_i, n_t;
    float p;
    for (i = 0; i < nres; i++) {
        if (!printed(printed_words, cwords[i].word, n_printed)) {
            n_s = cwords[i].ns;
            n_d = cwords[i].nd;
            n_i = cwords[i].ni;
            n_t = cwords[i].nt;
            p = get_penalty(n_s, n_d, n_i, n_t);
            printf(
                "<%2d>: %-10s penalty: %7.3f,        substitution: %d,  deletion: %d,  insertion: %d,  transposition: %d\n",
                n_printed, cwords[i].word, p, n_s, n_d, n_i, n_t);
            strcpy(printed_words[n_printed],
                cwords[i].word);
            n_printed++;
            if (n_printed >= num_show) break;
        }
    }
}

void main() {
    int i;
    char c, word[50] = { 0 };
    int insertion_cnt, res, widx, wcnt;
    ty_rec record;
    nodeptr last, curr, prev;
    size_t ki = 0, ci = 0; 

    FILE* fpr, * fpw;

    fpr = fopen("Corpus_dictionary_AP_Penn_RARE.txt", "r");
    if (!fpr) {
        printf("File open error of file Corpus_dictionary_AP_Penn_RARE.txt.\n");
        return;
    }

    fpw = fopen("records.bin", "wb");
    if (!fpw) {
        printf("File open error of file records.bin for writing.\n");
        fclose(fpr);
        return;
    }

    for (i = 0; i < 60; i++) {
        cwords[i].penalty = 0;
    }

    insertion_cnt = 0;

    while (1) {
        res = fscanf(fpr, "%s %d %d", word, &widx, &wcnt);
        if (res == EOF) break;

        if (res != 3) {
            printf("File fscanf error.\n");
            break;
        }
        if (strlen(word) > 49) {
            printf("Too long word. Word = %s \n", word);
            continue;
        }

        strcpy(record.word, word);
        record.widx = widx;
        record.wfreq = wcnt;

        last = insert_trie(word);
        if (!last) {
            printf("Word insertion error. Word = %s\n", word);
        }
        else {
            insertion_cnt++;
            last->bp = ftell(fpw);
            fwrite(&record, sizeof(ty_rec), 1, fpw);
        }

        if (insertion_cnt > 94000) {
            printf("Insertion count = %d | Word = %s\n", insertion_cnt, word);
        }
    }

    printf("total records inserted: %d\n", insertion_cnt);

    fclose(fpw);
    fclose(fpr);

    char key[50], corr_key[50];

    do {
        nres = 0;
        printf("\nTYPE A KEY: ");
        gets(key);

        if (key[0] == '$' && key[1] == '\0') {
            printf("Exiting program.\n");
            break;
        }

        corr_key[0] = '\0';
        found_perfect_match = 0;
        ki = 0, ci = 0;
        find_with_spell_correction(ROOT_TRIE, key, corr_key, ki, ci, 0, 0, 0, 0);
        sort_results(cwords);
        printf("total number of corrected results = %d\n\n", nres);
        output_top_corrections();
    } while (1);
}


