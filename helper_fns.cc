#include "helper_fns.h"

#include <iostream>
#include <fstream>

using namespace std;


// Print menu of choices to screen

void	printmenu() {

			cout << endl;
			cout << "Please choose from the following menu:" << endl;
			cout << "  1: Read input file" << endl;
			cout << "  2: Sort using Asort" << endl;
			cout << "  3: Sort using Bsort" << endl;
			cout << "  4: Sort using Csort" << endl;
			cout << "  5: Sort using Dsort" << endl;			
			cout << "  6: Sort using Esort" << endl;
			cout << "  7: Sort using Fsort" << endl;			
			cout << "  0: Exit program" << endl;
			cout << endl << "Enter your choice: ";

		return;

}


// Print array to screen .. only for use with small test files

void	printarray(long data[], long size) {

			cout << endl << "Array contents:" << endl;
			for (int i = 0; i < size; ++i)	  cout << data[i] << " ";
			cout << endl;

		return;

}


// Read input file and store numbers in arrays d1 and d2
// Function returns no. of data items, if file is read successfully. Else,
// function returns -1.

int		readfile(string infilename, long d[]) {

			long		i, size;
			ifstream	infile;

			// IMP NOTE: In the C++ std before C++11, the constructor for an
			//           ifstream or ofstream object takes a const char*, not
			//           a string. In compilers that follow the C++11 std or
			//			 later, we may write instead: infile.open(infilename);
	
			infile.open(infilename.c_str());

			if (!infile.is_open()) { size = -1;}
			else {
				for (i = 0; (!infile.eof()) && (i < MAXSIZE); ++i) {
					infile >> d[i];
				} // for
				
				size = i-1; // eof() causes an extra (invalid) number to be read
				infile.close();
			} // else
	
			return size;
}


// Write output file to disk from array data[]
// If file is successfully written to disk, function returns 0. Else,
// function returns -1.

int		writefile(long data[], long size, string outfilename) {

			long		i, errcode;
			ofstream	outfile;

			// IMP NOTE: In the C++ std before C++11, the constructor for an
			//           ifstream or ofstream object takes a const char*, not
			//           a string. In compilers that follow the C++11 std or
			//			 later, we may write instead: outfile.open(outfilename);
			outfile.open(outfilename.c_str());

			if (!outfile.is_open()) { errcode = -1;}
			else {
				for (i = 0; i < size; ++i)	  outfile << data[i] << " ";
				
				errcode = 0;
				outfile.close();
			} // else
	
			return errcode;
}


// Swaps two numbers. Numbers *must* be passed by reference, else we end up
// swapping only copies of data, not the originals.

void	swap(long& x, long& y) {

			long	tmp;

			tmp = x;
			x = y;
			y = tmp;

			return;
}

// ==== Insertion Sort and Merge Sort (Zach) ====

//Starting from position 1, element 1's original value is stored in a temporary variable. 
//If element 1 < element 0, element 0 is copied into element 1 and tmp is copied into element 0.
//Positions are checked incrementally, with elements greater than element i being moved 1 spot over and
//element i taking the empty place below them. The algorithm has O(n^2) complexity in the worst case.

void InsertionSort(long data[], long size){
	for(int i = 1, j; i < size; i++){
		long temp = data[i]; //Stores element i in temporary variable
		for(j = i; j > 0 && temp < data[j-1]; j--) 
			data[j] = data[j-1]; //Data below i is copied 1 space over so long as greater than element i and not acccessing negative indices
		data[j] = temp;
	}
}

// ==== Selection Sort and Radix Sort (Nick) ====

// Selection Sorting:
// We go through array, finds minimum, and orders from low-high.
// The element with the lowest value is selected, and exchanged with the element in the first position
// With this method, we need to know every number in an array to discover a minimum value
// Because scanning every number results in O(n^2) complexity

void SelectionSort(long data[], long size){
	for (long i = 0; i < size - 1; i++){ // start at pos 0, keep going until i reaches last index - 1, i++ to move to next pos.
		long min = i;
		for (long j = i + 1; j < size; j++){
			if (data[j] < data[min]) min = j;
		}
		if (min !=i) swap(data[i], data[min]);
	}
}

// Radix Sort:
// We input numbers into buckets, going from ones to tens (columns). our queue is base 10(0-9)
// We look at the last digit of each number (ones), and insert them into a queue...
// Then, we look at the next digit(s) of each number (tens...cont.) and insert them into a queue
		// We sort with ones, then (if needed) we sort with tens.... We determine order through each bucket place.
void radixSort(long data[], long size){
	if (size < 2) return;

	long minVal = data[0], maxVal = data[0];
	for (long i = 1; i < size; i++){
		if (data[i] < minVal) minVal = data[i]; // finding the minimum value
		if (data[i] > maxVal) maxVal = data[i]; // finding the maximum value
	}
	unsigned long range = (unsigned long)maxVal - (unsigned long)minVal; // we're setting our range

	const int radix = 10; // creating a base of 10
	queue<long> queues[radix]; // holding numbers 0-9

	for (unsigned long factor = 1; range/ factor > 0; factor *= radix){ // factor = factor * radix
		// controlling the column (of a digit between 0-9) that we're looking at. factor begins at 0.
		// range / factor > 0 is a stopping mechanism so it stops running when it doesn't have any more numbers to check.

		for (long j = 0; j < size; j++){ // going through the separated numbers, inserting them into "mailboxes."
			unsigned long key = (unsigned long)data[j] - (unsigned long)minVal; // negative numbers become non-negative.
			queues[(key / factor) % radix].push(data[j]); // isolating the exact digit for that current column
		}

		// inserting the mail back into the array, we're pulling from the queue, and writing back into the array.
		long k = 0;
		for (int j = 0; j < radix; j++){
			while (!queues[j].empty()) { // keep going until the queue is empty
				data[k++] = queues[j].front();
				queues[j].pop();
			}
		}
	}
}
