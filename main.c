#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SetInSet
{
    char name[10];
    int size;
    int *member;
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

void copy_set(Set *set1, Set *set2, Set *copy);
Set difference(Set set1, Set set2);
Set set_union(Set set1, Set set2);
Set intersection(Set set1, Set set2);

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

void copy_set(Set *set1, Set *set2, Set *copy)
{
    copy->set1.size = set1->size;
    strcpy(copy->set1.name, set1->name);

    copy->set1.member = (int *) malloc(sizeof(int) * set1->size);

    for(int i = 0; i < set1->size; i++)
    {
        copy->set1.member[i] = set1->member[i];
    }

    copy->set2.size = set2->size;
    strcpy(copy->set2.name, set2->name);

    copy->set2.member = (int *) malloc(sizeof(int) * set2->size);

    for(int i = 0; i < set2->size; i++)
    {
        copy->set2.member[i] = set2->member[i];
    }
}

Set difference(Set set1, Set set2)
{
    Set diff_set;

    // number of element in set diff
    diff_set.size = 0;

    int ptr_size = 5;
    diff_set.member = (int *) malloc(sizeof(int) * ptr_size);

    // 1st loop for looping member in set1
    for(int i = 0; i < set1.size; i++)
    {
        int num_e = 0;
        // 2nd loop for looping member in set2
        for(int x = 0; x < set2.size; x++)
        {
            // if set1[i] and set2[x] have the same number num_e will go up by one
            if(set1.member[i] == set2.member[x])
            {
                num_e++;
            }
        }

        // num_e = 0 mean there's no member in set2 that is equal to set1[i]
        if(num_e == 0)
        {
            if(ptr_size <= diff_set.size)
            {
                ptr_size += 5;
                diff_set.member = (int *) realloc(diff_set.member, sizeof(int) * ptr_size);
            }
            // assing the value that has in set1 but not in set2 to diff_set
            diff_set.member[diff_set.size++] = set1.member[i];
        }
    }

    copy_set(&set1, &set2, &diff_set);

    return diff_set;
}


Set set_union(Set set1, Set set2)
{
    // set1 = [1,2,3,4,5] | set2 = [2,3,6,7,9]
    // set1 U set2 = set1 U (set2 - set1)
    // union = [1,2,3,4,5] U [6,7,9] = [1,2,3,4,5,6,7,9]
    Set uni_set;

    // declare an array name diff which will contain the difference between set2-set1
    // diff_enum = number of element in diff[]
    Set diff_enum = difference(set2, set1);

    // number of element in uni[]
    uni_set.size = 0;

    int ptr_size = 5;
    uni_set.member = (int *) malloc(sizeof(int) * ptr_size);

    // copy all values in set1 to set uni
    for(int i = 0; i < set1.size; i++)
    {
        if(uni_set.size >= ptr_size)
        {
            ptr_size += 5;
            uni_set.member = (int *) realloc(uni_set.member, sizeof(int) * ptr_size);
        }
        uni_set.member[uni_set.size++] = set1.member[i];
    }

    // copy all values from diff[] to uni[]
    for(int i = 0; i < diff_enum.size; i++)
    {
        if(uni_set.size >= ptr_size)
        {
            ptr_size += 5;
            uni_set.member = (int *) realloc(uni_set.member, sizeof(int) * ptr_size);
        }
        uni_set.member[uni_set.size++] = diff_enum.member[i];
    }

    copy_set(&set1, &set2, &uni_set);

    return uni_set;
}


Set intersection(Set set1, Set set2)
{
    Set set_intsec;
    // number of element in set intersection
    set_intsec.size = 0;

    int ptr_size = 5;
    set_intsec.member = (int *) malloc(sizeof(int) * ptr_size);

    // 1st loop for looping member in set1
    for(int i = 0; i < set1.size; i++)
    {
        int num_e = 0;
        // 2nd loop for looping member in set2
        for(int x = 0; x < set2.size; x++)
        {
            // if set1[i] = set2[x] mean that set1 and set2 are intersect with value set1[i] 
            if(set1.member[i] == set2.member[x])
            {
                num_e++;
            }
        }

        // if num_e > 0 mean number in set1[i] are also in set2
        if(num_e > 0)
        {
            if(set_intsec.size >= ptr_size)
            {
                ptr_size += 5;
                set_intsec.member = (int *) realloc(set_intsec.member, sizeof(int *) * ptr_size);
            }
            // assing value of set1[i] to intsec[] | intsec is an array of intersection
            set_intsec.member[set_intsec.size++] = set1.member[i]; 
        }
    }

    copy_set(&set1, &set2, &set_intsec);

    // return the number of element in intsec
    return set_intsec;
}