/*
I wanted this file to have the same API as c/set.h which is why the method names
are the same. In general Vectors are already a fully thought out version of an array so I
didn't need to write most of the code that I wrote in C.

I am aware that the goal of Rust is to write memory safe code, but unlike the C code I did
not find myself having to allocate any memory or constantly resize my Sets. It seems like
the Vec type is handling all of that for me. Neato!
*/

#![allow(non_snake_case)]

/* The basic struct that forms a Set. */
struct Set {
    values: Vec<i32>,
}

impl Set {
    /* Initializes a Set with the given value as a the first member of the Set.*/
    fn initSetWithInt(value: i32) -> Set {
        let mut set = Set { values: Vec::new() };
        set.insertInt(value);
        return set;
    }

    /* This function combines the initSetWithInt and insertInt functions to be able
     * to init a Set with an array of ints. Similar to set([0, 1, 2, 3, 4]) in
     * Python. */
    fn initSetWithArray(values: Vec<i32>) -> Set {
        let mut set: Set = Set::initSetWithInt(values[0]);
        for (i, value) in values.iter().enumerate() {
            if i > 0 {
                set.insertInt(*value);
            }
        }
        return set;
    }

    /* Takes a Set and an int, and if that int is in the Set, removes it. */
    fn removeInt(&mut self, value: i32) {
        self.values.retain(|x| *x != value);
    }

    /* Takes a Set and an int, and if that int isn't in the Set, inserts it. */
    fn insertInt(&mut self, value: i32) {
        if !self.values.contains(&value) {
            self.values.push(value);
        }
    }

    /* Iterates over an array, and calls insertInt on each element. */
    fn insertArray(&mut self, values: Vec<i32>) {
        for value in values {
            self.insertInt(value);
        }
    }

    /* This allows me to quickly see the contents of a Set. */
    fn printSet(&mut self) {
        println!("{:?}", self.values);
    }
}

fn main() {
    // Example usage:
    let mut set = Set::initSetWithArray(vec![1, 2, 3]);
    set.insertInt(345);
    set.insertArray(vec![4, 4, 4]);
    set.removeInt(4);
    set.printSet();
    // Expected output:
    // [1, 2, 3, 345]
}
