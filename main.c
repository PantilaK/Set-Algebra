#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sets
{
    char name[10];
    int numberOfElement;
    int member[20];
}Set;

typedef struct Combined_sets
{
    Set set1;
    Set set2;
    char name[10];
    char operator[2];
    int numberOfElement;
    int member[20];
}Combined_set;

int main()
{
    FILE *read = fopen("set_file.txt", "r");

    int numberOfSet = 1;
    Set *set = malloc(sizeof(Set) * numberOfSet);

    char str[50];
    int i = 0;
    while(fscanf(read, "%s", str) != EOF)
    {
        if(strcmp(str,"set") == 0)
        {
            if (i >= numberOfSet)
            {
                numberOfSet++;
                set = realloc(set, sizeof(Set) * numberOfSet);
            }

            fscanf(read, "%s", str);
            strcpy(set[i].name,str);
        }
        printf("%s\n", str);
    }

    printf("%s", set[0].name);
    return 0;
}