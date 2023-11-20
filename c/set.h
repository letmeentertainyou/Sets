/*
I had originally intended to create a type agnostic Set like in Python but it
turns out to be really hard to have arrays of different types because of
allocation. Which is why I am only using the data type int in this file.

Technically these sets would support other data types if you changed most of the
occurrences of int to the other data type. Set->length and Set->size still need
to be numbers though so a find and replace is not a perfect answer.

I realize that the C language convention is to use underscores in names but
after using camelCase in JS I can't make myself switch back. I don't like typing
all those underscores.
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Generic membership test for the C language. */
bool isMember(int list[], int value, int length) {
    for (int i = 0; i < length + 1; i++) {
        if (list[i] == value) {
            return true;
        }
    }
    return false;
}

/* getIndex and isMember are almost identical functions and it might be simpler
 * to only have getIndex. The problem is that -1 isn't falsey so I'd have to
 * rewrite the code that relies on isMember. I wrote that function first. If I
 * do that rewrite then <stdbool.h> won't be needed anymore. */
int getIndex(int list[], int value, int length) {
    for (int i = 0; i < length + 1; i++) {
        if (list[i] == value) {
            return i;
        }
    }
    return -1;
}

/* The basic struct that forms a Set. Length represents the index of the last
 * item in the Set and so it's not really length. The length of the Set is
 * length +1. I guess that's confusing.*/
struct Set {
    int size;
    int length;
    int values[];
};

/* This allows me to quickly see the contents of a set since C has no way to
 * print arrays. */
void printSet(struct Set *set) {
    printf("Printing set.\n");
    for (int i = 0; i < (set->length) + 1; i++) {
        printf("%d, ", set->values[i]);
    }
    printf("\n");
}

/* Initializes a Set with the given value as a the first member of the set.*/
struct Set *initSetWithInt(int value, int size) {
    // This cast was needed for set.h but not set.c
    struct Set *newSetPtr =
        (struct Set *)malloc(sizeof(struct Set) + size * sizeof(int));
    // This sets the size and length attributes of the set.
    *newSetPtr = (struct Set){size, 0};
    // This is required because values is dynamic so it can't be cast above.
    newSetPtr->values[0] = value;
    return newSetPtr;
}

/* Allows me to easily double or halve the size of a Set as it grows/shrinks.
 * After creating a new struct Set * to return, the old one is freed. */
struct Set *resizeSet(struct Set *set, int newSize, int copySize) {
    struct Set *newSet = initSetWithInt(0, newSize);
    newSet->length = set->length;
    memcpy(newSet->values, set->values, copySize * sizeof(int));
    free(set);
    return newSet;
}

/* Takes a Set and an int, and if that int is in the Set, removes it. When
 * Set->length is less than half of Set->size, the Set is automatically resized.
 */
struct Set *removeInt(struct Set *set, int value) {
    int index = getIndex(set->values, value, set->length);
    if (index > -1) {
        // printf("The value %d will be popped at index %d.\n", value, index);
        for (int i = index; i < set->length; i++) {
            set->values[i] = set->values[i + 1];
        }
        set->values[set->length] = 0;
        set->length--;
        if (set->length < set->size / 2 && set->length > 10) {
            // Length is zero indexed but memcpy is not so we need length +1
            return resizeSet(set, set->length, set->length + 1);
        }
        return set;
    }
}

/* Takes an integer and attempts to add it to the set. If Set->length equals
 * Set->size then the Set is automatically resized to be twice as big. */
struct Set *insertInt(struct Set *set, int value) {
    // You must send NULL if you want to create a Set from nothing
    // But it does work now.
    if (set == NULL) {
        return initSetWithInt(value, 8);
    }
    if (set->length < set->size - 1) {
        if (!isMember(set->values, value, set->length)) {
            set->length++;
            set->values[set->length] = value;
        }
        return set;
    } else {
        return insertInt(resizeSet(set, set->size * 2, set->size), value);
    }
}

/* Iterates over an array, and calls insertInt on each element. */
struct Set *insertArray(struct Set *set, int list[], int length) {
    for (int i = 0; i < length; i++) {
        set = insertInt(set, list[i]);
    }
    return set;
}

/* This function combines the initSetWithInt and insertInt functions to be able
 * to init a set with an array of ints. Similar to set([0, 1, 2, 3, 4]) in
 * Python. */
struct Set *initSetWithArray(int list[], int length) {
    struct Set *newSet;
    for (int i = 0; i < length; i++) {
        if (i == 0) {
            newSet = initSetWithInt(list[i], length);
        } else {
            newSet = insertInt(newSet, list[i]);
        }
    }
    return newSet;
}

/* This function expects a trailing comma. Valid input could look like
 * '1,2,2,3,4,55,6,12313,' You can also have duplicates in the input string and
 * they will be removed from the output. */
struct Set *initSetWithString(char str[]) {
    // 2147483647 is ten chars long so that's our size.
    char tmp[10];
    int tmpLength = 0;
    struct Set *set;
    int firstIter = 0;

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ',') {
            int tmpInt = atoi(tmp);
            if (firstIter == 0) {
                set = initSetWithInt(tmpInt, 10);
                firstIter += 1;
            } else {
                set = insertInt(set, tmpInt);
            }
            memset(tmp, 0, sizeof(tmp));
            tmpLength = 0;
        } else {
            tmp[tmpLength] = str[i];
            tmpLength += 1;
        }
    }
    return set;
}
