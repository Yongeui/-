#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define Tbl_size 37533  

typedef struct ty_record {
    char name[300];
    int monincome;
    int link;
} type_record;

type_record Hashtable[Tbl_size];
int LAST = Tbl_size - 1;
float average_num_probe;
FILE* fp;

int hash(char recname[]) {
    unsigned char u;
    int HA, j, leng, halfleng;
    long sum = 0;
    int A[300] = { 0 };

    leng = strlen(recname);
    for (j = 0; j < leng; j++) {
        u = recname[j];
        A[j] = u;
    }
    halfleng = leng / 2;
    for (j = 0; j < halfleng; j++)
        sum = sum + (A[j] * A[leng - 1 - j] * A[(leng - 1) / 2]);
    if (leng % 2 == 1)
        sum = sum + A[halfleng] * A[halfleng + 1] * A[(leng - 1) / 2];
    HA = sum % Tbl_size;
    return HA;
}

int find_empty_location() {
    int curr;
    curr = LAST;
    while (curr >= 0 && Hashtable[curr].name[0] != '\0')
        curr -= 1;
    return curr;
}

int insert_rec(type_record rec) {
    int HA, curr, nprove = 0, empty_loc;
    HA = hash(rec.name);
    if (Hashtable[HA].name[0] == '\0') {
        Hashtable[HA] = rec;
        return 1;
    }
    else {
        curr = HA;
        do {
            if (strcmp(Hashtable[curr].name, rec.name) == 0)
            {
                printf("insertion failed since same key already exists.\n");
                return -1;
            }
            nprove += 1;
            if (Hashtable[curr].link == -1)
                break;
            else
                curr = Hashtable[curr].link;
        } while (1);

        empty_loc = find_empty_location();

        Hashtable[empty_loc] = rec;
        Hashtable[curr].link = empty_loc;

        return nprove;
    }
}

int retrieve_rec(char* key, int* probe) {
    int curr;
    curr = hash(key);
    if (Hashtable[curr].name[0] == '\0')
        return -1;

    *probe = 0;
    do {
        *probe += 1;
        if (strcmp(Hashtable[curr].name, key) == 0) {
            return curr;
        }
        else
            curr = Hashtable[curr].link;
    } while (curr != -1);
    return -1;
}

unsigned int count_max_probe(const char* file_name) {
    char line[300];
    int nprobe, loc;
    unsigned int max_probe = 0;

    FILE* fp = fopen(file_name, "r");
    if (!fp) {
        printf("Could not open file %s for reading.\n", file_name);
        return 0;
    }

    while (fgets(line, sizeof(line), fp)) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        loc = retrieve_rec(line, &nprobe);
        if (loc != -1 && nprobe > max_probe) {
            max_probe = nprobe;
        }
    }
    fclose(fp);

    return max_probe;
}

int del_start(int s, int* chain_split) {
    int curr, prev, nmove, found = -1, prev_found;

    curr = Hashtable[s].link;
    prev = s;
    while (curr != -1)
    {
        if (hash(Hashtable[curr].name) == s) {
            prev_found = prev;
            found = curr;
        }

        prev = curr;
        curr = Hashtable[curr].link;

    }

    if (found == -1) {
        Hashtable[s].name[0] = '\0';
        return 0;
    }
    else {
        strcpy(Hashtable[s].name, Hashtable[found].name);
        Hashtable[s].monincome = Hashtable[found].monincome;

        nmove = 1 + del_middle(found, prev_found, chain_split);

        return nmove;
    }
}

int del_middle(int s, int p, int* chain_split) {
    int curr, prev, HA_curr, HA_curr_belongs_to_D_s, element_of_D_s, nmove, found, prev_found;

    curr = Hashtable[s].link;
    prev = s;
    found = -1;
    while (curr != -1) {
        if (hash(Hashtable[curr].name) == s) {
            prev_found = prev;
            found = curr;
        }
        prev = curr;
        curr = Hashtable[curr].link;

    }

    if (found == -1) {
        Hashtable[p].link = Hashtable[s].link;
        Hashtable[s].name[0] = '\0';
        return 0;
    }
    else {
        found = -1;
        curr = Hashtable[s].link;
        prev = s;
        while (curr != -1) {
            HA_curr = hash(Hashtable[curr].name);
            HA_curr_belongs_to_D_s = 0;
            element_of_D_s = s;
            do {
                if (element_of_D_s == HA_curr) {
                    HA_curr_belongs_to_D_s = 1;
                    break;
                }
                else
                    element_of_D_s = Hashtable[element_of_D_s].link;
            } while (element_of_D_s != -1);

            if (HA_curr_belongs_to_D_s == 0) {
                found = curr;
                prev_found = prev;
            }

            prev = curr;
            curr = Hashtable[curr].link;
        }
        if (found != -1) {
            strcpy(Hashtable[s].name, Hashtable[found].name);
            Hashtable[s].monincome = Hashtable[found].monincome;
            nmove = 1 + del_middle(found, prev_found, chain_split);
            return nmove;
        }
        else {
            Hashtable[p].link = -1;
            *chain_split += 1;
            int temp_chain_split = 0;
            nmove = del_start(s, &temp_chain_split);
            *chain_split += temp_chain_split;

            return nmove;
        }
    }
}

int delete_rec(char* dkey, int* chain_split) {
    int found = -1, h, curr, prev, nmove = 0;

    h = hash(dkey);
    if (Hashtable[h].name[0] == '\0')
    {
        printf("There are no records with such key.\n");
        return -1;
    }

    if (strcmp(dkey, Hashtable[h].name) == 0)
        nmove = del_start(h, chain_split);
    else {
        curr = Hashtable[h].link;
        prev = h;
        found = -1;
        while (curr != -1) {
            if (strcmp(Hashtable[curr].name, dkey) == 0) {
                found = curr;
                break;
            }
            else {
                prev = curr;
                curr = Hashtable[curr].link;
            }
        }

        if (found == -1)
        {
            printf("A record with such key does not exist.\n");
            return -1;
        }
        else
            nmove = del_middle(found, prev, chain_split);
    }

    return nmove;
}

void delete_multiple(int num_del_req) {
    char line[300], * res;
    int cnt_lines = 0, num_split = 0,
        nmove, leng, num_deletion_success = 0,
        num_relocated_deletions = 0;

    fp = fopen("Companies_Korean.txt", "r");
    while (1)
    {
        res = fgets(line, 300, fp);
        if (!res)
            break;
        cnt_lines += 1;
        leng = strlen(line);
        line[leng - 1] = '\0';
        nmove = delete_rec(line, &num_split);
        if (nmove >= 0)
            num_deletion_success += 1;
        if (nmove > 0)
            num_relocated_deletions += nmove;
        if (cnt_lines == num_del_req)
            break;
    }
    printf("     num_deletion_success=%d, num_relocated_deletions=%d\n", num_deletion_success, num_relocated_deletions-1);
    fclose(fp);
    return;
}

int check_num_links(char key[]) {
    int count = 0, curr, flag = -1;
    int HA = hash(key);
    if (Hashtable[HA].name[0] == '\0') {
        printf("There are no records with such key.\n");
        return -1;
    }

    curr = HA;

    while (curr != -1) {
        if (strcmp(Hashtable[curr].name, key) == 0) {
            flag = 1;
        }
        count += 1;
        curr = Hashtable[curr].link;
    }
    if (flag != 1) {
        printf("There are no records with such key.\n");
        return -1;
    }
    return count;
}

int main(void) {
    type_record a_rec;
    int cnt_lines = 0, cnt_insertion = 0, pos, n_probe, i, k, leng, m_income, n_chain_split, n_move, num_deletions_to_do;
    int count;
    char line[300], name[1300], * res;

    for (i = 0; i < Tbl_size; i++) {
        Hashtable[i].name[0] = '\0';
    }

    fp = fopen("Companies_Korean.txt", "r");
    while (1)
    {
        res = fgets(line, 300, fp);
        if (!res)
            break;
        cnt_lines += 1;
        leng = strlen(line);
        line[leng - 1] = '\0';
        m_income = rand() % 50000;
        strcpy(a_rec.name, line);
        a_rec.monincome = m_income;
        a_rec.link = -1;
        n_probe = insert_rec(a_rec);
        if (n_probe != -1)
            cnt_insertion += 1;
    }
    fclose(fp);

    while (1) {
        printf("명령은 ? ");
        if (!fgets(line, sizeof(line), stdin)) {
            printf("wrong command.\n");
            continue;
        }
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) < 1) continue;

        if (line[0] == 'e')
        {
            printf("    실험을 종료합니다.\n");
            break;
        }

        if (line[0] == 'v') {
            unsigned int max_probe = count_max_probe("Companies_Korean.txt");
            printf("    maximum number of probes per search = %u\n", max_probe);
            continue;
        }

        k = 2;
        i = 0;
        while (line[k] != '\0' && line[k] == ' ') k++;
        while (line[k] != '\0') {
            name[i] = line[k];
            k++;
            i++;
        }
        name[i] = '\0';

        switch (line[0]) {
        case 'i':
            strcpy(a_rec.name, name);
            a_rec.monincome = rand() % 50000;
            a_rec.link = -1;
            n_probe = insert_rec(a_rec);
            if (n_probe == -1)
                printf("    insertion failed by duplicate key.\n");
            else
                printf("    insertion succeeded. num probe = %d\n", n_probe);
            break;
        case 'r':
            n_probe = 0;
            pos = retrieve_rec(name, &n_probe);
            if (pos == -1)
                printf("    No such record exists.\n");
            else
                printf("    Search succeeded. Loc_found = %d, n_probes = %d\n", pos, n_probe);
            break;
        case 'd':
            n_chain_split = 0;
            n_move = delete_rec(name, &n_chain_split);
            if (n_move >= 0)
                printf("    Deletion succeeded. Num_relocations = %d, num_chain_splits = %d\n", n_move, n_chain_split);
            break;
        case 'q':
            for (k = 0; k < i; k++) {
                if (!isdigit(name[k])) {
                    printf("number should be given after q.\n");
                    break;
                }
            }
            num_deletions_to_do = atoi(name);
            delete_multiple(num_deletions_to_do);
            break;

        case 'c':
            count = check_num_links(name);
            if (count != -1) {
                printf("    Number of links : %d\n", count);
            }
            break;

        default:
            printf("wrong command\n");
        }
    }
    return 0;
}
