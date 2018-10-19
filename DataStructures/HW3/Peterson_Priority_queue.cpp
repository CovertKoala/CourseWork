//  Created by Mikhail Auguston on 9/18/16.
//  Updated by Capt Teal "Koala" Peterson on 12/03/17
//
//  Peterson_Priority_queue.cpp
//  
//	Description:
//  Platform: Developed on Windows 10

#include <iostream>
#include <cstdlib>		// for rand() use
#include <string>		//**ADDED**
using namespace std;

class Priority_queue {
    int size; // current size
    int max_size;
    int * elements;
    
    void max_heapify(int i){
        int largest = 1;
        int l = 2 * i;      // LEFT(i)
        int r = 2 * i + 1;  // RIGHT(i)
        if(l <= size && elements[l] > elements[i]) 
                largest = l;
        else    largest = i;
        
        if(r <= size && elements[r] > elements[largest])
            largest = r;
        
        if(largest != i){
            // swap elements[i] with elements[largest]
            int temp = elements[i];
            elements[i] = elements[largest];
            elements[largest] = temp;
            max_heapify(largest); // recursion
        }
    }

	//***** Koala's Private Update *****
	void print_visual(int heap[], int h_size) {
		// Prints queue in tree form:
		//       ------- 16-------			7 spaces to left (2^3 -1), 7 '-' (same), btwn = 0 -> 2^4 (but doesn't matter)
		//	 --- 15---       --- 14---		3 spaces to left (2^2 -1), 3 '-' (same), btwn = 7 -> 2^3+1
		// - 10-   - 9 -   - 11-   - 13-	1 spaces to left (2^1 -1), 1 '-' (same), btwn = 3 -> 2^2+1
		// 7   4   3   8   2   6   5   12	0 spaces to left (2^0 -1), 0 '-' (same), btwn = 1 -> 2^1+1
		//    								*extra space for single digits
		if (h_size == 1) cout << heap[1] << '\n';

		int max_rows = (int) ceil(log2(h_size));
		//Initialize variables
		int row_size = 0;
		int item = 0;
		int index = 1;
		unsigned int dash_cnt = 0;
		unsigned int space_cnt = 0;

		//Print Queue in Tree form
		for (int i = 1; i <= max_rows; i++) {
			row_size = (int) pow(2, i - 1);					//row_size also happens to be index of first item in the row
			dash_cnt = (int) pow(2, max_rows - i) - 1;		//'-' size (and row leading space size)
			space_cnt = (int) pow(2, max_rows - i) * 2 - 1;//Element Buffer size
			cout << string(dash_cnt, ' ');			//Row leading spaces

			for (int j = 0; j < row_size; j++) {
				index = row_size + j;
				if (index > h_size) break;			//Check for last element
				item = heap[index];
				cout << string(dash_cnt, '-');		//Leading '-'
				if (item <= 99) cout << ' ';		//Centering space
				cout << item;						//Element
				if (item <= 9) cout << ' ';			//Centering space
				cout << string(dash_cnt, '-');		//Trailing '-'
				if (i == 1) break;
				cout << string(space_cnt, ' ');		//Element buffer space
			}
			cout << endl;							//End of row
			if (index > h_size) break;
		}
	}

	void print_wide_visual() {
		//Due to the stylized output, there is not enough room on the screen for queues > 63.
		//This splits the queue in two for printing.

		if (size <= 63) print_visual(elements,size); //ensures correct print is called.
		else if (size >= 128) {
			cout << "Max print size is 127\n";
			return;
		}
		else {

			//Splits Queue
			int max_rows = (int)ceil(log2(size))-1;
			int left_size = (int) pow(2,max_rows)-1;
			int right_size = (int) pow(2, max_rows)-1;
			int *left_side = new int[left_size];
			int *right_side = new int[right_size];

			left_side[0] = -1;
			right_side[0] = -1;
			//Left base: 2 ^ n   Right base: 3 * 2 ^ (n - 1)  Width : 2 ^ (n - 1)
			int left_base = 2;
			int right_base = 3;
			int row_width = 1;
			int index = 1;
			//re-use these two variables
			right_size = 0;
			left_size = 0;

			for (int i = 1; i <= max_rows; i++) {
				left_base = (int)pow(2, i);
				right_base = 3 * (int)pow(2, (i - 1));
				row_width = (int)pow(2, (i - 1));
				for (int j = 0; j < row_width; j++) {
					if ((left_base + j) <= size) {
						left_size++;
						left_side[index] = elements[left_base + j];
					}

					if ((right_base + j) <= size) {
						right_size++;
						right_side[index] = elements[right_base + j];
					}

					index++;
					if (left_size + right_size >= size) break;
				}
			}

			//Prints Queue
			cout << "*** Top of heap: " << elements[1] << " ***\n";
			cout << "Left side of tree:\n";
			print_visual(left_side, left_size);
			cout << "\nRight side of tree:\n";
			print_visual(right_side, right_size);
		}
	}
	//***** End Koala's Private Update (more below) *****
    
public:
    // constructor
    Priority_queue(int n){
        if(n <= 0) max_size = 1; // default max_size == 1
        else max_size = n;
        size = 0; // creates empty queue
        elements = new int [max_size + 1];
        // indicies of stored elements start with 1
        elements[0] = -1; 
    }

    
    void enqueue(int key){
        if(size + 1 > max_size){ 
            cout<< " queue overflow\n";
            return;
        }
        size++;
        elements[size] = key;
        // Walk backwards through the array from size/2 to 1, 
        // calling max_heapify() on each key => this is the same as constructing 
        // a heap from sub-heaps (bottom-up).
        // Order of processing guarantees that the children of key i 
        // are heaps when i is processed
        for(int i = size/2; i > 0; i--)
            max_heapify(i);
    }

    int maximum(){
        if(size == 0){
            cout<< " queue underflow\n";
            return -1;
        }
        return elements[1];
    }
    
    int dequeue(){
        if(size == 0){
            cout<< " queue underflow\n";
            return -1;
        }
        int root = elements[1];
        elements[1] = elements[size];
        size--;
        max_heapify(1);
        return root;
    }
    
    int increase_key(int position, int new_key){
		//**Added components to this if/esle if block**
		if (size == 0) {
			cout << " Error: Empty Queue";
			return -1;
		}
		else if (position > size || position <= 0) { // also test for 0 or less
			cout << " Error: position " << position << " is out of range 1 to " << size << endl;
			return -1;
		}
		else if (new_key < elements[position]) {
			cout << " Error: new key " << new_key << " is smaller than current key "
				<< elements[position] << endl;
			return -1;
		}
        elements[position] = new_key;
		while (position > 1 && elements[position / 2] < elements[position]) {
			// swap element with its parent
			int temp = elements[position / 2];
			elements[position / 2] = elements[position];
			elements[position] = temp;
			position = position / 2; // move upward
		}
		return position;
    }
    
    void show(){
        // print the heap contents
        cout<< "The heap contains: "; //**UPDATED** gramatically correct no matter the size
        for(int i = 1; i <= size; i++)
            cout<< elements[i]<< ' ';
		if (size == 0) cout << "nothing"; //**ADDED**
        cout<<endl;
    }

	double height() {
		// Return height of queue
		return log2(size+1);
	}


	//***** Koala's Updates *****

	void clear() {
		//Per home assignment writeup, changes 'size' to zero
		//Makes data in queue 'inaccessable' ("Clears" it)
		size = 0;
	}

	void decrease_key(int position, int new_key) {
		//Changes value of key at 'position' to 'new_key'
		if (size == 0) {
			cout << " Error: Empty Queue";
			return;
		}
		else if (position > size || position <= 0) {
			cout << " Error: position " << position << " is out of range 1 to " << size << endl;
			return;
		}
		else if (new_key > elements[position]) {
			cout << " Error: new key " << new_key << " is larger than current key ";
			if (position <= size) cout << elements[position];
			cout << '\n';
			return;
		}
		elements[position] = new_key;
		max_heapify(position);
	}

	void print_visual() {
		//Public queue -> tree print function
		if (size == 0) cout << "Queue is empty.\n";
		else if (size > 63) print_wide_visual();
		else print_visual(elements,size);
	}

};

int main(){

	cout << "print_visual() is tested/used to demo clear() and decrease_key()\n\n";

	// *** Test Case A - Empty Queue *** //
	cout << "**************************************\n";
	cout << "* Begining Test Case A - Empty Queue *\n";
	cout << "**************************************\n";

	Priority_queue a(0);

	// Insert keys
	// N/A - empty test

	// Print current Queue with show()/print_visual()
	a.show();
	a.print_visual();

	// Print output of target test methods

	cout << "\nOutput of Test Case A - Empty Queue\n";
	cout << "decrease(1,0): ";
	a.decrease_key(1, 0);  //Test on non-existant first key
	cout << "\ndecrease(0,1): ";
	a.decrease_key(0, 1);  // Test on 0 index
	cout << "\nclear(): ";
	a.clear();  // test clear
	a.print_visual();


	// *** Test Case B - Queue with one key *** //
	cout << "\n\n";
	cout << "*******************************************\n";
	cout << "* Begining Test Case B - Queue w/ one key *\n";
	cout << "*******************************************\n";

	Priority_queue b(1);

	// Insert keys
	b.enqueue(99);

	// Print current Queue with show()/print_visual()
	b.show();
	b.print_visual();  // Test print_visual()

	// Print output of target test methods

	cout << "\nOutput of Test Case B - Queue w/ one key\n";
	cout << "decrease(2,1): ";
	b.decrease_key(2, 1);  //Test key beyond range
	cout << "decrease(0,1): ";
	b.decrease_key(0, 1);  //Test key at 'notional' 0 position
	cout << "decrease(1,0):\n";
	b.decrease_key(1, 0);  //Test key at correct position 1 with small key
	b.print_visual();
	cout << "decrease(1,999): ";
	b.decrease_key(1, 999); //Test on new 'bigger' key
	cout << "decrease(1,1): ";
	b.decrease_key(1, 1);  //Test on key smaller than current key
	cout << "\nclear(): ";
	b.clear(); // test clear
	b.print_visual();


	// *** Test Case C - Queue with 5 random keys entered randomly *** //
	cout << "\n\n";
	cout << "********************************************************************\n";
	cout << "* Begining Test Case C - Queue with 5 random keys entered randomly *\n";
	cout << "********************************************************************\n";

	Priority_queue c(5);

	// Insert keys
	int testKeys[5] = { 1, 22, 333, 7, 55 };
	for (int i = 0; i < 5; i++) {
		c.enqueue(testKeys[i]);
	}
	
	// Print current Queue with show()/print_visual()
	c.show();
	c.print_visual();

	// Print output of target test methods

	cout << "\nOutput of Test Case C - Queue with 5 random keys entered randomly" << endl;
	cout << "decrease(1,0):\n";
	c.decrease_key(1, 0);  // test on first position with smaller key
	c.print_visual();
	cout << "decrease(0,999): ";
	c.decrease_key(0, 999); // test on '0' position
	cout << "decrease(1,999): ";
	c.decrease_key(1, 999); // test on 'bigger' key
	cout << "decrease(6,1): ";
	c.decrease_key(6, 1); // test on outside of range
	cout << "\nclear(): ";
	c.clear();  // test clear
	c.print_visual();


	// *** Test Case D - Queue with 70 random keys entered in ascending order *** //
	cout << "\n\n";
	cout << "*******************************************************************************\n";
	cout << "* Begining Test Case D - Queue with 70 random keys entered in ascending order *\n";
	cout << "*******************************************************************************\n";

	Priority_queue d(70);

	// Insert keys
		//Generate Random Key/Data pairs for remaining cases
	int random_key = 0;
	for (int i = 0; i < 70; i++) {
		random_key = rand() % 999;
		d.enqueue(random_key);
		//cout << random_key << ' ';
	}

	// Print current Queue with show()/print_visual()
	d.show();
	cout << '\n';
	d.print_visual();

	// Print output of target test methods

	cout << "\nOutput of Test Case D - Queue with 70 random keys entered in ascending order" << endl;
	cout << "decrease(0,1): ";
	d.decrease_key(0, 1);  // test on '0' position
	cout << "decrease(1,999): ";
	d.decrease_key(1, 999); // test on 'bigger' key
	cout << "decrease(71,1): ";
	d.decrease_key(71, 1); // test on high side of range
	cout << "decrease(1,0):\n";
	d.decrease_key(1, 0); // test on low side of range, w/ smaller key
	d.print_visual();
	cout << "\nclear(): ";
	d.clear(); // test clear
	d.print_visual();

	cout << "\nTests A-D Complete" << endl;
    return 0;
}