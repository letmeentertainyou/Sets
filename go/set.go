/*
This is a bit of a mesh between the C code and the Rust code. Go structs can have methods but they don't update their internal values the way Rust struct methods do. Because of this methods like insertInt need to return a value in Go, just like they do in C. I find this overlap between the three languages very interesting.
*/

package main

import (
	"fmt"
	"slices"
)

/* The basic struct that forms a Set. */
type Set struct {
	values []int
}

/* Initializes a Set with the given value as a the first member of the Set.*/
func initSetWithInt(value int) Set {
	return Set{[]int{value}}
}

/* This function combines the initSetWithInt and insertInt functions to be able
 * to init a Set with an array of ints. Similar to set([0, 1, 2, 3, 4]) in
 * Python. */
func initSetWithArray(values []int) Set {
	set := initSetWithInt(values[0])
	for i, value := range values {
		if i > 0 {
			set = set.insertInt(value)
		}
	}
	return set
}


/* Takes a Set and an int, and if that int is in the Set, removes it. */
func (self Set) removeInt(value int) Set {
	for i, item := range self.values {
        if item == value {
            self.values = append(self.values[:i], self.values[i+1:]...)
			return self
        }
    }
	return self
}

/* Takes a Set and an int, and if that int isn't in the Set, inserts it. */
func (self Set) insertInt(value int) Set {
	if !(slices.Contains(self.values, value)) {
		self.values = append(self.values, value)
	}
	return self
}

/* Iterates over an array, and calls insertInt on each element. */
func (self Set) insertArray(values []int) Set {
	for _, value := range values {
		self = self.insertInt(value)
	}
	return self
}

/* This allows me to quickly see the contents of a Set..*/
func (self Set) printSet() {
	fmt.Println(self.values)
}

func main() {
	// Example usage:
	set := initSetWithArray([]int{1, 2, 3})
    set = set.insertInt(345)
    set = set.insertArray([]int{4, 4, 4})
	set = set.removeInt(4)
    set.printSet()
	// Expected output:
    // [1 2 3 345]
}
