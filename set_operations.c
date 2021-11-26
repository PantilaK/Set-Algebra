#include "stdio.h"
int difference(int set1[], int n1, int set2[], int n2, int diff[]);
int set_union(int set1[], int n1, int set2[], int n2, int uni[]);
int intersection(int set1[], int n1, int set2[], int n2, int intsec[]);

int main()
{
    int set1[5] = {1,2,3,4,5};
    int set2[5] = {2,3,6,7,9};
    int set3[20];
    int e = intersection(set1, 5, set2, 5, set3);

    printf("%d\n",e);
    for(int i = 0; i < e; i++)
    {
        printf("%d ",set3[i]);
    }
    return 0;
}
// set1 - set2 = diff_set or diff[]
// this function will return the number of element to diff_set
int difference(int set1[], int n1, int set2[], int n2, int diff[])
{
    // number of element in set diff
    int num_diff = 0;

    // 1st loop for looping member in set1
    for(int i = 0; i < n1; i++)
    {
        int num_e = 0;
        // 2nd loop for looping member in set2
        for(int x = 0; x < n2; x++)
        {
            // if set1[i] and set2[x] have the same number num_e will go up by one
            if(set1[i] == set2[x])
            {
                num_e++;
            }
        }

        // num_e = 0 mean there's no member in set2 that is equal to set1[i]
        if(num_e == 0)
        {
            // assing the value that has in set1 but not in set2 to diff_set
            diff[num_diff++] = set1[i];
        }
    }

    //return number of elements in diff[]
    return num_diff;
}

int set_union(int set1[], int n1, int set2[], int n2, int uni[])
{
    // set1 = [1,2,3,4,5] | set2 = [2,3,6,7,9]
    // set1 U set2 = set1 U (set2 - set1)
    // union = [1,2,3,4,5] U [6,7,9] = [1,2,3,4,5,6,7,9]

    // declare an array name diff which will contain the difference between set2-set1
    // diff_enum = number of element in diff[]
    int diff[20];
    int diff_enum = difference(set2, n2, set1, n1, diff);

    // number of element in uni[]
    int num_union = 0;

    // copy all values in set1 to set uni
    for(int i = 0; i < n1; i++)
    {
        uni[num_union++] = set1[i];
    }

    // copy all values from diff[] to uni[]
    for(int i = 0; i < diff_enum; i++)
    {
        uni[num_union++] = diff[i];
    }

    return num_union;
}

int intersection(int set1[], int n1, int set2[], int n2, int intsec[])
{
    // number of element in set intersection
    int num_intsec = 0;

    // 1st loop for looping member in set1
    for(int i = 0; i < n1; i++)
    {
        int num_e = 0;
        // 2nd loop for looping member in set2
        for(int x = 0; x < n2; x++)
        {
            // if set1[i] = set2[x] mean that set1 and set2 are intersect with value set1[i] 
            if(set1[i] == set2[x])
            {
                num_e++;
            }
        }

        // if num_e > 0 mean number in set1[i] are also in set2
        if(num_e > 0)
        {
            // assing value of set1[i] to intsec[] | intsec is an array of intersection
            intsec[num_intsec++] = set1[i]; 
        }
    }

    // return the number of element in intsec
    return num_intsec;
}