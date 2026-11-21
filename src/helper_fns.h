#ifndef HELPER_FNS_H_
#define HELPER_FNS_H_

// DO NOT forget to add the prototypes for your ASort, BSort, and other functions below!

#include <queue> // Radix sort header
#include <string>
#include <unistd.h>
#define MAXSIZE	 2100000

using namespace std;

void	printmenu();
void	printarray(long data[], long size);
int	readfile(string infilename, long data[]);
int	writefile(long data[], long size, string outfilename);
void	swap(long& x, long& y);
void	checkResults(long[], long);


// Selection sort and Radix Sort
void SelectionSort(long data[], long size);
void radixSort(long data[], long size);

// Insertion sort and Merge Sort
void InsertionSort(long[], long);
void Merge(long[], long, long);
void MergeSort(long[], long, long);


// Comb Sort and Quicksort
void CombSort(long data[], long n);
void QuickSort(long data[], long n);
void QuickSortHelper(long data[], long first, long last);

// bubble sort
void bubbleSort(long int data[], int n);
void shellSort(long int data[], int n);

#endif
