/* 
Array and Append array functions. - PetersonHW1.cpp

Capt Teal "Koala" Peterson
October 2017

Given two arrays of integers, merges them into a new array.  Includes
subroutines to print the arrays and displays input and output.*/

#include <iostream>
using namespace std;

void show(int a[], int len) {
	// Array display function
	cout << "{";
	for (int i = 0; i < len; i++) {
		cout << a[i];
		if ((i + 1) == len) break;
		else cout << ", ";
	}
	cout << "}";
}

int * append(int a[], int length1, int b[], int length2) {
	/* Receives two arrays as input (the pointer to the first array element and the length of array),
	   dynamically allocates memory for the resulting array, and returns a pointer to the first element
	   of resulting array. */
	int * temp = new int[length1+length2]; 
	for (int i = 0; i < length1; i++) {
		temp[i] = a[i];
	}
	for (int i = 0; i < length2; i++) {
		temp[length1 + i] = b[i];
	}
	return temp;
}


void main() {
	// Test array declaration
	const int len1 = 5;
	int a[len1] = { 1,2,3,4,5 };

	const int len2 = 4;
	int b[len2] = { 10,11,12,13 };

	// Display test arrays: pre-merge
	cout << "a[]: ";
	show(a, len1);
	cout << endl;

	cout << "b[]: ";
	show(b, len2);
	cout << endl << endl;

	/* Generate and display results of 9 test cases:
	   len(a,b) -> (0,0), (0,1), (0,B)
                   (1,0), (1,1), (1,B)
				   (A,0), (A,1), (A,B) 
	   where A and B are an arbitrary length >1 in two test length lists below */

	int lenA[] = { 0,1,5 };
	int lenB[] = { 0,1,4 };
	int * result;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << "Test len for (a,b) -> (" << lenA[i] << ", " << lenB[j] << "): ";
			result = append(a, lenA[i], b, lenB[j]);
			show(result, lenA[i] + lenB[j]);
			cout << endl << endl;
		}
	}
}