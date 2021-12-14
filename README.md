# Description
This project is about operations on set
- Set union
- Set intersection
- Set difference

It will read set from set_file.txt file and then find union, intersection, and difference between two sets that in set_file.txt and store result back in result.txt file
```
set A = {1, 2, 6, 8, 20}
set B = {20, 9, 7, 1, 5, 10, 29, 3}
set C = {9, 7, 8, 30, 2, 4, 14}
```

# Library
- stdio.h
- stdlib.h
- string.h

# Set Structure
- SetInSet\
\
this struct will be substruct of struct Set
```
typedef struct SetInSet
{
    char name[10];
    int size;
    int *member;
}SetInSet;
```

- Set\
\
structer which have 2 SetInSet struct, name, size, operatoe, and member\
for operator it will have only when it is Set that come from when using set_union, intersection, or difference function only
```
typedef struct Set
{
    SetInSet set1;
    SetInSet set2;
    char name[10];
    char operator[15];
    int size;
    int *member;
}Set;
```

# Set Function
- Set union\
\
**Set** set_union(Set set1, Set set2);\
this function will find union of set1 and set2 and return struct *Set*

- Set intersection\
\
**Set** intersection(Set set1, Set set2);\
this function will return struct *Set* which is the interscetion between set1 and set2

- Set difference\
\
**Set** difference(Set set1, Set set2);\
this function will return struct *Set* which iis the difference of set1 and set2

```
Set set_D = intersection(set_B, set_C);
Set set_E = set_union(set_A, set_C);
Set set_F = difference(set_A, set_B);
```

# Output
The output will appear on result.txt file which will have set that we read from set_file.txt file and set that is the output of function set_union, intersection, and difference
```
set A = {1, 2, 6, 8, 20}
set B = {20, 9, 7, 1, 5, 10, 29, 3}
set C = {9, 7, 8, 30, 2, 4, 14}
set B intersection set C -> set D = {9, 7}
set A U set C -> set E = {1, 2, 6, 8, 20, 9, 7, 30, 4, 14}
set A - set B -> set F = {2, 6, 8}
```
