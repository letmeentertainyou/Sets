/*
 * This CLI exists so that I can write a Python test suite that is
 * binary compatable. The end goal is that I can use the same CLI and the
 * same test suite for the Go and Rust versions of Set that I will write.
 */

#include "set.h"

int main(int argc, char *argv[]) {

    if (argc == 4) {
        struct Set *set;
        // * initSetWithInt
        // argv[2] is the int to insert, argv[3] is the size to allocate.
        if (strcmp(argv[1], "-n") == 0) {
            printf("Inserting %s into a Set of size: %s.\n", argv[2], argv[3]);
            set = initSetWithInt(atoi(argv[2]), atoi(argv[3]));
            printSet(set);
        }

        // insertInt
        // argv[2] is target Set, argv[3] is the int to insert.
        if (strcmp(argv[1], "-i") == 0) {
            printf("Inserting %s into the set %s\n", argv[3], argv[2]);
            set = initSetWithString(argv[2]);
            set = insertInt(set, atoi(argv[3]));
            printSet(set);
        }

        // insertArray
        // argv[2] is target Set, argv[3] is the Set to insert.
        if (strcmp(argv[1], "-a") == 0) {
            printf("Inserting %s into the set %s\n", argv[3], argv[2]);
            set = initSetWithString(argv[2]);
            struct Set *set2 = initSetWithString(argv[3]);
            set = insertArray(set, set2->values, set2->length + 1);
            printSet(set);
        }

        // removeInt
        // argv[2] is target Set, argv[3] is the int to remove.
        if (strcmp(argv[1], "-r") == 0) {
            printf("Removing %s from the set %s\n", argv[3], argv[2]);
            set = initSetWithString(argv[2]);
            set = removeInt(set, atoi(argv[3]));
            printSet(set);
        }

    } else {
        printf("Incorrect number of args, read docs/CLI.txt for more info.\n");
    }
}
