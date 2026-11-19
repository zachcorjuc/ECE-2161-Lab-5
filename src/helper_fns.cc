#include "helper_fns.h"

#include <iostream>
#include <fstream>

using namespace std;


// Print menu of choices to screen

void	printmenu() {

			cout << endl;
			cout << "Please choose from the following menu:" << endl;
			cout << "  1: Read input file" << endl;
			cout << "  2: Sort using Selection Sort" << endl;
			cout << "  3: Sort using Radix Sort" << endl;
			cout << "  4: Sort using Insertion Sort" << endl;
			cout << "  5: Sort using Merge Sort" << endl;
			cout << "  6: Sort using Comb Sort" << endl;
			cout << "  7: Sort using Quick Sort" << endl;
			cout << "  8: Sort using Bubble Sort" << endl;
			cout << "  9: Sort using Shell Sort" << endl;
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
				
				//size = i-1; // eof() causes an extra (invalid) number to be read
				size = i;
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

void	checkResults(long results[], long size){
	bool valid_results = true;
	for(int i = 0; i<size-1&&valid_results; ++i){ //Only has to check up to element size-2
		if(results[i]>results[i+1]) valid_results = false;
	}

	if (valid_results) cout << "Results are properly ordered! :)" << endl;
	else cout << "Error: Results are NOT properly ordered :(" << endl;
}

// ==== Insertion Sort and Merge Sort (Zach) ====

//Insert Sort
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

//Mergesort
//Recursive algorithm with worst case O(nlogn) time. Splits an n-sized array into two halves,
//of size n/2, then each sub-array into two halves of n/4..repeats until have n
//single-element arrays. Then, contiguous groups of 2 elements are formed by sorting

//Merge algorithm
void Merge(long data[], long first, long last){
	long mid = (first + last) / 2;
	long i1 = 0, i2 = first, i3 = mid + 1;
	long span = last-first+1;

	long *temp = new long[span];

	while(i2<mid+1&&i3<last+1){ //Ensures that sub-array indices remain in sub-arrays
		if(data[i2] < data[i3]) temp[i1++] = data[i2++];
		else temp[i1++] = data[i3++];
	}

	//Empties rest of the non-empty half into the temporary array
	if(i2>=mid+1){ //Right sub-array isn't emptied
		while(i1<span){
			temp[i1++] = data[i3++];
		}
	}
	else { //Left sub-array isn't emptied
		while(i1<span){
			temp[i1++] = data[i2++];
		}
	}

	for(i1 = 0, i2 = first; i1<span; ++i1, ++i2) data[i2] = temp[i1]; //Loads temporary array into

	delete[] temp;
}

//MergeSort algorithm
void MergeSort(long data[], long first, long last){
	if(first < last){ //Array of 1 is already sorted
		long mid = (first + last) / 2;

		MergeSort(data, first, mid); //Left merge-sort
		MergeSort(data, mid+1, last); //Right merge-srt

		Merge(data, first, last); //Merges sorted halves
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

//Bubble Sort:
//<Inserti Brief Description>

#include "helper_fns.h"

void bubbleSort(long int data[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = n - 1; j > i; j--) {
            if (data[j] < data[j - 1]) {
                long int temp = data[j];
                data[j] = data[j - 1];
                data[j - 1] = temp;
            }
        }
    }
}

//Shell Sort
//Brief description

#include "helper_fns.h"

void shellSort(long int data[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            long int temp = data[i];
            int j = i;

            while (j >= gap && data[j - gap] > temp) {
                data[j] = data[j - gap];
                j -= gap;
            }

            data[j] = temp;
        }
    }
}

// ==== Comb Sort and Quicksort ====

/* Comb Sort:
Comb sort is an improved bubble sort. Bubble sort is slow because small
values near the end of the array can only move one position per pass.
Comb sort first compares elements that are 'step' positions apart, and
shrinks step by a factor of 1.3 each pass, so far-out-of-place values move
a long way in one swap.
  Phase 1: step = n/1.3, n/1.3^2, ... down to 2. Compare data[j] with
           data[j-step] and swap if out of order.
  Phase 2: finish with a bubble sort (step = 1) that stops early as soon
           as a pass makes no swaps.
Average running time should be about O(n*log(n)); the worst case is O(n^2). */

void CombSort(long data[], long n) {
	long step = n, j, k;

	// Phase 1: comb passes with a shrinking gap
	while ((step = long(step / 1.3)) > 1) {
		for (j = n - 1; j >= step; j--) {
			k = j - step;
			if (data[j] < data[k]) swap(data[j], data[k]);
		}
	}

	// Phase 2: bubble sort that quits early when no swaps happen
	bool again = true;
	for (long i = 0; i < n - 1 && again; i++) {
		again = false;
		for (j = n - 1; j > i; --j) {
			if (data[j] < data[j - 1]) {
				swap(data[j], data[j - 1]);
				again = true;
			}
		}
	}
}


/* Quicksort:
Quicksort picks a "bound" (pivot) and partitions the array so everything
left of the bound is <= bound and everything right of it is >= bound. The
bound is then in its final position, and both sides are sorted recursively.
The middle element is used as the bound, which avoids the O(n^2) worst case
on data that is already sorted. Average running time is O(n lg n).

Recursive helper: sorts data[first..last]*/
void QuickSortHelper(long data[], long first, long last) {
	long lower = first + 1, upper = last;

	// Move the middle element to the front and use it as the bound
	swap(data[first], data[(first + last) / 2]);
	long bound = data[first];

	// move lower right and upper left, swapping elements that are
	// on the wrong side of the bound
	while (lower <= upper) {
		while (bound > data[lower]) lower++;
		while (bound < data[upper]) upper--;

		if (lower < upper) swap(data[lower++], data[upper--]);
		else lower++;
	}

	// now the bound is in its final position
	swap(data[upper], data[first]);

	// Recursively sort the left and right subarrays
	if (first < upper - 1) QuickSortHelper(data, first, upper - 1);
	if (upper + 1 < last)  QuickSortHelper(data, upper + 1, last);
}

/* sorts data[0..n-1]
The largest element is moved to the end first. It acts as a "sentinel" so
the scan 'while (bound > data[lower]) lower++;' can never run off the end.*/
void QuickSort(long data[], long n) {
	long i, max;

	if (n < 2) return;

	for (i = 1, max = 0; i < n; i++)          // find the largest element
		if (data[max] < data[i]) max = i;

	swap(data[n - 1], data[max]);             // largest is now in final spot
	QuickSortHelper(data, 0, n - 2);          // sort everything else
}
