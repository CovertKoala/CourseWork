// Capt Teal "Koala" Peterson
// 29 Nov 17
// Peterson_HA2.cpp
//
// Binary Tree test/demo file
//
// Designed on Windows 10

#include <iostream>
#include <cstdlib>		//for rand() use
using namespace std;

#include "Peterson_binary_tree.h"

void selection_sort(int a[], int len) { 
	// borrowed from previous lab work
	// sorts array of integers in ascending order

	if (len < 2) return; // already sorted

	int min, temp;
	for (int i = 0; i < len - 1; i++) {
		min = i;
		for (int j = i + 1; j < len; j++) {
			if (a[j] < a[min]) {
				min = j;
			}
		}
		// swap a[i] and a[min]
		temp = a[i];
		a[i] = a[min];
		a[min] = temp;
	}
}

int main(){

	//Bug #1 in original program - because total was not initialized on creation prior to use,
	//it would produce a random number when used prior to initialization.  I fixed this by
	//initilizing all new variables to 0 (except for the tree object).

	// *** Test Case A - Empty Tree *** //
		cout << "*************************************" << endl;
		cout << "* Begining Test Case A - Empty Tree *" << endl;
		cout << "*************************************" << endl;

		btree a;

		// Insert nodes/data
		// N/A - empty test

		// Print current tree with print()/print_vis()
		a.print();
		a.print_vis();

		// Print output of target test methods

		cout << "Output of Test Case A - Empty Tree" << endl;
		cout << "largest_key(): " << a.largest_key() << endl;
		cout << "smallest_key(): " << a.smallest_key() << endl;
		cout << "easy_average(): " << a.easy_average() << endl;
		cout << "average_data(): " << a.average_data() << endl;
		cout << "min_depth(): " << a.min_depth() << endl;
		cout << "max_depth(): " << a.max_depth() << endl << endl;


	// *** Test Case B - Tree with one node *** //
		cout << "*******************************************" << endl;
		cout << "* Begining Test Case B - Tree w/ one node *" << endl;
		cout << "*******************************************" << endl;

		btree b;

		// Insert nodes/data
		b.insert(rand()%99, rand()%99);

		// Print current tree with print()/print_vis()
		b.print();
		b.print_vis();

		// Print output of target test methods

		cout << "Output of Test Case B - Tree w/ one node" << endl;
		cout << "largest_key(): " << b.largest_key() << endl;
		cout << "smallest_key(): " << b.smallest_key() << endl;
		cout << "easy_average(): " << b.easy_average() << endl;
		cout << "average_data(): " << b.average_data() << endl;
		cout << "min_depth(): " << b.min_depth() << endl;
		cout << "max_depth(): " << b.max_depth() << endl << endl;


	// *** Test Case C - Tree with 8 random nodes entered randomly *** //
		cout << "********************************************************************" << endl;
		cout << "* Begining Test Case C - Tree with 8 random nodes entered randomly *" << endl;
		cout << "********************************************************************" << endl;

		btree c;

		// Insert nodes/data
		int randomKeys[8], randomData[8]; // not truly random since rand() is not seeded -> for reproduceability
		cout << "Random key/data pairs:" << endl;
		for (int i = 0; i < 8; i++) {
			randomKeys[i] = rand() % 99;
			randomData[i] = rand() % 99;
			cout << '(' << randomKeys[i] << ',' << randomData[i] << ") ";
		}
		cout << endl << "Note duplicate keys" << endl << endl;
		for (int i=0; i < 8; i++) {
			c.insert(randomKeys[i], randomData[i]);
		}

		// Print current tree with print()/print_vis()
		c.print();
		c.print_vis();

		// Print output of target test methods

		cout << endl << "Output of Test Case C - Tree with 8 random nodes entered randomly" << endl;
		cout << "largest_key(): " << c.largest_key() << endl;
		cout << "smallest_key(): " << c.smallest_key() << endl;
		cout << "easy_average(): " << c.easy_average() << endl;
		cout << "average_data(): " << c.average_data() << endl;
		cout << "min_depth(): " << c.min_depth() << endl;
		cout << "max_depth(): " << c.max_depth() << endl << endl;


	// *** Test Case D - Tree with 8 random nodes entered in ascending order *** //
		cout << "******************************************************************************" << endl;
		cout << "* Begining Test Case D - Tree with 8 random nodes entered in ascending order *" << endl;
		cout << "******************************************************************************" << endl;

		btree d;

		// Insert nodes/data
			//Generate Random Key/Data pairs for remaining cases
			selection_sort(randomKeys,8);
			selection_sort(randomData,8);

			//Insert key/data pairs in ascending order
			for (int i=0; i < 8; i++) {
				d.insert(randomKeys[i], randomData[i]);
			}

		// Print current tree with print()/print_vis()
		d.print();
		d.print_vis();

		// Print output of target test methods

		cout << "Output of Test Case D - Tree with 8 random nodes entered in ascending order" << endl;
		cout << "largest_key(): " << d.largest_key() << endl;
		cout << "smallest_key(): " << d.smallest_key() << endl;
		cout << "easy_average(): " << d.easy_average() << endl;
		cout << "average_data(): " << d.average_data() << endl;
		cout << "min_depth(): " << d.min_depth() << endl;
		cout << "max_depth(): " << d.max_depth() << endl << endl;


	// *** Test Case E - Tree with 8 random nodes entered in desceding order *** //
		cout << "******************************************************************************" << endl;
		cout << "* Begining Test Case E - Tree with 8 random nodes entered in desceding order *" << endl;
		cout << "******************************************************************************" << endl;

		btree e;

		// Insert nodes/data
		for (int i=7; i >= 0; i--) {
			e.insert(randomKeys[i], randomData[i]);
		}

		// Print current tree with print()/print_vis()
		e.print();
		e.print_vis();

		// Print output of target test methods

		cout << "Output of Test Case E - Tree with 8 random nodes entered in desceding order" << endl;
		cout << "largest_key(): " << e.largest_key() << endl;
		cout << "smallest_key(): " << e.smallest_key() << endl;
		cout << "easy_average(): " << e.easy_average() << endl;
		cout << "average_data(): " << e.average_data() << endl;
		cout << "min_depth(): " << e.min_depth() << endl;
		cout << "max_depth(): " << e.max_depth() << endl << endl;

		cout << "Tests A-E Complete";

	return 0;
}
