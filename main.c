#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int difference(const int const set1[], int n1,  const int const set2[], int n2, int diff[]);
int set_union(const int const set1[], int n1, const int const set2[], int n2, int uni[]);
int intersection(const int const set1[], int n1, const int const set2[], int n2, int intsec[]);

typedef struct SetInSet
{
    char name[10];
    int size;
    int member[20];
}SetInSet;

typedef struct Set
{
    SetInSet set1;
    SetInSet set2;
    char name[10];
    char operator[2];
    int size;
    int *member;
}Set;

int main()
{
    FILE *read = fopen("set_file.txt", "r");

    int numberOfSet = 1;
    Set *set = malloc(sizeof(Set) * numberOfSet);

    char str[50];
    int i = -1;
    int num, size, mem_size = 5;
    while(fscanf(read, "%s", str) != EOF)
    {
        char *remove_str = strtok(str, "{");
        num = atoi(remove_str);

        if(strcmp(str,"set") == 0)
        {
            if (i >= 0)
            {
                set[i].size = size;
            }

            if (++i >= numberOfSet)
            {
                numberOfSet++;
                set = realloc(set, sizeof(Set) * numberOfSet);
            }

            fscanf(read, "%s", str);
            strcpy(set[i].name,str);

            set[i].member = (int *) malloc(sizeof(int) * mem_size);
            size = 0;
        }
        else if(num != 0)
        {
            if(i >= mem_size)
            {
                mem_size += 5;
                set[i].member = (int *) realloc(set[i].member, sizeof(int) * mem_size);
            }
            set[i].member[size++] = num;
        }
        printf("%s\n",str);
    }
    if(i >= mem_size)
    {
        set[i].member = (int *) realloc(set[i].member, sizeof(int) * mem_size);
    }
    set[i].size = size;

    // Combined_set set3_union;
    // strcpy(set3_union.operator, "U");
    // set3_union.numberOfElement = set_union(set[2].member);

    printf("%s\n", set[1].name);
    printf("%d\n",set[2].member[6]);
    return 0;
}