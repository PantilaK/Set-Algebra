#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structure of set inside another set
typedef struct SetInSet
{
    char name[10];
    int size;
    int *member;
}SetInSet;

// structure set
typedef struct Set
{
    SetInSet set1;
    SetInSet set2;
    char name[10];
    char operator[15];
    int size;
    int *member;
}Set;

void copy_set(Set *set1, Set *set2, Set *copy);
void writeSet_inFile(Set set, FILE *write_file);
Set difference(Set set1, Set set2);
Set set_union(Set set1, Set set2);
Set intersection(Set set1, Set set2);

int main()
{
    // open file for reading set
    FILE *read = fopen("set_file.txt", "r");

    // declare pointer of struct Set and allocate memery for it
    int numberOfSet = 1;
    Set *set = malloc(sizeof(Set) * numberOfSet);

    // reading Set from file
    char str[50];
    int i = -1;
    int num, size, mem_size = 5;
    while(fscanf(read, "%s", str) != EOF)
    {
        // for number which look like "{4,"
        char *remove_str = strtok(str, "{");
        // convert string to int
        num = atoi(remove_str);

        //find if it set or not
        if(strcmp(str,"set") == 0)
        {
            // storing size of each set
            if (i >= 0)
            {
                set[i].size = size;
            }

            // resize of set pointer
            if (++i >= numberOfSet)
            {
                numberOfSet++;
                set = realloc(set, sizeof(Set) * numberOfSet);
            }

            fscanf(read, "%s", str);
            strcpy(set[i].name,str);

            // allocate memory for member inside Set
            set[i].member = (int *) malloc(sizeof(int) * mem_size);
            size = 0;
        }
        else if(num != 0)
        {
            // resize of set member
            if(i >= mem_size)
            {
                mem_size += 5;
                set[i].member = (int *) realloc(set[i].member, sizeof(int) * mem_size);
            }
            // assign member to Set
            set[i].member[size++] = num;
        }
    }
    // resize and assing for the last Set
    if(i >= mem_size)
    {
        mem_size += 5;
        set[i].member = (int *) realloc(set[i].member, sizeof(int) * mem_size);
    }
    set[i].size = size;

    fclose(read);

    // use function intersection, union, and difference then store in Set
    // assing name for each set
    Set set_D = intersection(set[1],set[2]);
    strcpy(set_D.name, "D");
    Set set_E = set_union(set[0],set[2]);
    strcpy(set_E.name, "E");
    Set set_F = difference(set[0], set[1]);
    strcpy(set_F.name, "F");

    // open file for writing the result
    FILE *write = fopen("result.txt", "w");

    // writing the result on file
    for(int k = 0; k < numberOfSet; k ++)
    {
        writeSet_inFile(set[k], write);
    }

    writeSet_inFile(set_D, write);
    writeSet_inFile(set_E, write);
    writeSet_inFile(set_F, write);

    // free memory that we allocated
    for(int k = 0; k < numberOfSet; k ++)
    {
        free(set[k].member);
    }

    free(set);
    free(set_D.member);
    free(set_E.member);
    free(set_F.member); 

    fclose(write);  
    return 0;
}

// function for writing each Set in file
void writeSet_inFile(Set set, FILE *write_file)
{
    // for Set that came from two sets
    if(set.set1.size != 0)
    {
        fprintf(write_file, "set %s %s set %s -> ", set.set1.name, set.operator, set.set2.name);
    }

    // print name of that set
    fprintf(write_file, "set %s = {", set.name);

    // print member of that set
    for(int i = 0; i < set.size; i++)
    {
        if(i != (set.size-1))
        {
            fprintf(write_file, "%d, ", set.member[i]);
        }
        else
        {
            fprintf(write_file, "%d}\n", set.member[i]);
        }
    }
}

// copy set1 and set2 to SetInSet of set3
void copy_set(Set *set1, Set *set2, Set *copy)
{
    // copy size and name of set1
    copy->set1.size = set1->size;
    strcpy(copy->set1.name, set1->name);

    // allocate memory for set3.set1
    copy->set1.member = (int *) malloc(sizeof(int) * set1->size);

    // copy each element of set1 to set3.set1
    for(int i = 0; i < set1->size; i++)
    {
        copy->set1.member[i] = set1->member[i];
    }

    // copy size and name of set2
    copy->set2.size = set2->size;
    strcpy(copy->set2.name, set2->name);

    // allocate memory for set3.set2
    copy->set2.member = (int *) malloc(sizeof(int) * set2->size);

    // copy each element of set2 to set3.set2
    for(int i = 0; i < set2->size; i++)
    {
        copy->set2.member[i] = set2->member[i];
    }
}

Set difference(Set set1, Set set2)
{
    // declare Set 
    Set diff_set;
    
    // assing the operator of this function
    strcpy(diff_set.operator, "-");
    diff_set.size = 0;

    // allocate memory for member in diff_set
    int ptr_size = 5;
    diff_set.member = (int *) malloc(sizeof(int) * ptr_size);

    // 1st loop for looping member in set1
    for(int i = 0; i < set1.size; i++)
    {
        int num_e = 0;
        // 2nd loop for looping member in set2
        for(int x = 0; x < set2.size; x++)
        {
            // if set1.member[i] and set2.member[x] have the same number num_e will go up by one
            if(set1.member[i] == set2.member[x])
            {
                num_e++;
            }
        }

        // num_e = 0 mean there's no member in set2 that is equal to set1[i]
        if(num_e == 0)
        {
            // resize
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

    // declare Set
    Set uni_set;

    // assing operator for this function
    strcpy(uni_set.operator, "U");

    // find the difference of set2 and set 1 and store in diff_enum set
    Set diff_enum = difference(set2, set1);

    // size of uni_set
    uni_set.size = 0;

    // allocate memory for member in uni_set
    int ptr_size = 5;
    uni_set.member = (int *) malloc(sizeof(int) * ptr_size);

    // copy all values in set1 to uni_set
    for(int i = 0; i < set1.size; i++)
    {
        // resize
        if(uni_set.size >= ptr_size)
        {
            ptr_size += 5;
            uni_set.member = (int *) realloc(uni_set.member, sizeof(int) * ptr_size);
        }
        uni_set.member[uni_set.size++] = set1.member[i];
    }

    // copy all values from diff_enum to uni_set
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
    // declare set
    Set set_intsec;

    // size
    set_intsec.size = 0;

    // assing the operator of this function *for intersection use its name
    strcpy(set_intsec.operator, "intersection");

    // allocate memory for member in set_intsec
    int ptr_size = 5;
    set_intsec.member = (int *) malloc(sizeof(int) * ptr_size);

    // 1st loop for looping member in set1
    for(int i = 0; i < set1.size; i++)
    {
        int num_e = 0;
        // 2nd loop for looping member in set2
        for(int x = 0; x < set2.size; x++)
        {
            // if set1.member[i] = set2.member[x] mean that set1 and set2 are intersect with value set1[i] 
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
            // assing value
            set_intsec.member[set_intsec.size++] = set1.member[i]; 
        }
    }

    copy_set(&set1, &set2, &set_intsec);

    return set_intsec;
}