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
    int i = -1;
    int num, element;
    while(fscanf(read, "%s", str) != EOF)
    {
        char *remove_str = strtok(str, "{");
        num = atoi(remove_str);

        if(strcmp(str,"set") == 0)
        {
            if (++i >= numberOfSet)
            {
                numberOfSet++;
                set = realloc(set, sizeof(Set) * numberOfSet);
            }

            fscanf(read, "%s", str);
            strcpy(set[i].name,str);

            element = 0;
        }
        else if(num != 0)
        {
            set[i].member[element++] = num;
        }
    }

    printf("%s\n", set[1].name);
    printf("%d\n",numberOfSet);
    return 0;
}