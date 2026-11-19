// Copyright (C) 2025 Sarvesh Kulkarni <sarvesh.kulkarni@villanova.edu>
// If you are a student in the ECE 2161 lab, you may use this code.
// Permission is NOT granted to use this code for non-educational purposes.

// WARNING! WARNING! WARNING!
//  This program declares *very* large arrays. If you have not increased your
//  stack space, expect a segmentation fault. In order to increase your
//  stack space, run the following command from your terminal:
//  ulimit -s 819200

#include <iostream>
#include <string>
#include <ctime>

#include "helper_fns.h"

using namespace std;


int main() {
	int		choice, sz;
	//long	data[MAXSIZE], wData[MAXSIZE];
	long data[23], wData[23];
	double  begin_time, end_time, cpu_time_used;
	string  ifilename, ofilename;
	
	while (1) {
		printmenu();
		cin >> choice;
		
		switch (choice) {

			case 1: // Read input file and store data in arrays data1 and data2
                    // The function 'readfile' returns the size of the file that was read
					// If the file could not be read, 'readfile' returns -1
				
					ifilename = "test_input.txt"; //"lab5_input.txt"
					sz = readfile(ifilename, data);
			
					if (sz < 0)	 {
						 cerr << endl << "ERROR: Input File Not Found or File cannot be opened." <<endl;
						 cerr << "       Please check that the file exists, its path, and try again!" << endl << endl;
						 return 0;
					}
					else cout << endl << "File size is: " << sz << endl;
			
					break;

			case 2: // Selection Sort

                    // First, copy the contents of the array 'data' to the working array 'wData'.
					for (int i = 0; i < sz; i++) wData[i] = data[i];
                    
                    
					begin_time = clock();   // start cpu timer
					SelectionSort(wData, sz);
					// Call your Sort function A here to sort the array 'wData''
			        //  Note that 'wData' is of size 'sz' (see case 1).

			
					end_time = clock();		// end cpu timer

					cpu_time_used = (end_time - begin_time) / CLOCKS_PER_SEC;
					cout << endl << "Selection Sort ran for " << cpu_time_used << " secs.";
			
					checkResults(wData, sz);
					ofilename = "lab5_Selection_Sort_out.txt";
					writefile(wData, sz, ofilename);
					
					if (sz < 0)	 {
						 cerr << endl << "ERROR: Output File could not be opened." <<endl;
						 cerr << "       Quitting Now!" << endl << endl;
						 return 0;
					}
					else cout << endl << "Output written to " << ofilename << endl;
			
					break;

			case 3: // Radix Sort
			
			        // First, copy the contents of the array 'data' to the working array 'wData'. Your program should sort 'wData' and not 'data'.
			        for (int i = 0; i < sz; i++) wData[i] = data[i];
			        
					begin_time = clock();   // start cpu timer
					radixSort(wData,sz);
					// Call your Sort function B here to sort the array 'wData'
			        //  Note that 'wDdata' is of size 'sz' (see case 1).


			
					end_time = clock();		// end cpu timer

					cpu_time_used = (end_time - begin_time) / CLOCKS_PER_SEC;
					cout << endl << "Radix Sort ran for " << cpu_time_used << " secs.";
			
					checkResults(wData, sz);
					ofilename = "lab5_Radix_Sort_out.txt";
					writefile(wData, sz, ofilename);
					
					if (sz < 0)	 {
						 cerr << endl << "ERROR: Output File could not be opened." <<endl;
						 cerr << "       Quitting Now!" << endl << endl;
						 return 0;
					}
					else cout << endl << "Output written to " << ofilename << endl;
			
					break;

			case 4: //Insertion Sort
				for (int i = 0; i < sz; i++) wData[i] = data[i];

				begin_time = clock();
				InsertionSort(wData, sz);

				end_time = clock();

				cpu_time_used = (end_time - begin_time) / CLOCKS_PER_SEC;
				cout << endl << "Insertion Sort ran for " << cpu_time_used << " secs.";

				checkResults(wData, sz);
				ofilename = "lab5_Insertion_Sort_Results.txt";
				writefile(wData, sz, ofilename);

				if (sz < 0)	 {
					 cerr << endl << "ERROR: Output File could not be opened." <<endl;
					 cerr << "       Quitting Now!" << endl << endl;
					 return 0;
				}
				else cout << endl << "Output written to " << ofilename << endl;
				break;

			case 5: //Merge Sort
				for (int i = 0; i < sz; i++) wData[i] = data[i];

				begin_time = clock();
				MergeSort(wData, 0, sz-1); //Instead of taking size argument, takes start and end indices

				end_time = clock();

				cpu_time_used = (end_time - begin_time) / CLOCKS_PER_SEC;
				cout << endl << "Merge Sort ran for " << cpu_time_used << " secs.";

				checkResults(wData, sz);
				ofilename = "lab5_Merge_Sort_out.txt";
				writefile(wData, sz, ofilename);

				if (sz < 0)	 {
					 cerr << endl << "ERROR: Output File could not be opened." <<endl;
					 cerr << "       Quitting Now!" << endl << endl;
					 return 0;
				}
				else cout << endl << "Output written to " << ofilename << endl;
				break;
					
			case 6: // Comb Sort
				for (int i = 0; i < sz; i++) wData[i] = data[i];

				begin_time = clock();
				CombSort(wData, sz);

				end_time = clock();

				cpu_time_used = (end_time - begin_time) / CLOCKS_PER_SEC;
				cout << endl << "Comb Sort ran for " << cpu_time_used << " secs.";

				checkResults(wData, sz);
				ofilename = "lab5_Comb_Sort_out.txt";
				if (writefile(wData, sz, ofilename) < 0)	 {
					 cerr << endl << "ERROR: Output File could not be opened." <<endl;
					 cerr << "       Quitting Now!" << endl << endl;
					 return 0;
				}
				else cout << endl << "Output written to " << ofilename << endl;
				break;

			case 7: // Quicksort
				for (int i = 0; i < sz; i++) wData[i] = data[i];

				begin_time = clock();
				QuickSort(wData, sz);

				end_time = clock();

				cpu_time_used = (end_time - begin_time) / CLOCKS_PER_SEC;
				cout << endl << "Quick Sort ran for " << cpu_time_used << " secs.";

				checkResults(wData, sz);
				ofilename = "lab5_Quick_Sort_out.txt";
				if (writefile(wData, sz, ofilename) < 0)	 {
					 cerr << endl << "ERROR: Output File could not be opened." <<endl;
					 cerr << "       Quitting Now!" << endl << endl;
					 return 0;
				}
				else cout << endl << "Output written to " << ofilename << endl;
				break;

				// Write the other cases here
			case 8: // Bubble sort
				// First, copy the contents of the array 'data' to the working array 'wData'. Your program should sort 'wData' and not 'data'.
				for (int i = 0; i < sz; i++) wData[i] = data[i];

				begin_time = clock();   // start cpu timer
				bubbleSort(wData,sz);
				// Call your Sort function B here to sort the array 'wData'
				//  Note that 'wDdata' is of size 'sz' (see case 1).



				end_time = clock();		// end cpu timer

				cpu_time_used = (end_time - begin_time) / CLOCKS_PER_SEC;
				cout << endl << "Bubble Sort ran for " << cpu_time_used << " secs.";

				checkResults(wData, sz);
				ofilename = "lab5_BubbleSort_out.txt";
				writefile(wData, sz, ofilename);

				if (sz < 0)	 {
					 cerr << endl << "ERROR: Output File could not be opened." <<endl;
					 cerr << "       Quitting Now!" << endl << endl;
					 return 0;
				}
				else cout << endl << "Output written to " << ofilename << endl;

				break;
			case 9: // Shell sort
				// First, copy the contents of the array 'data' to the working array 'wData'. Your program should sort 'wData' and not 'data'.
				for (int i = 0; i < sz; i++) wData[i] = data[i];

				begin_time = clock();   // start cpu timer
				shellSort(wData,sz);
				// Call your Sort function B here to sort the array 'wData'
				//  Note that 'wDdata' is of size 'sz' (see case 1).


				end_time = clock();		// end cpu timer

				cpu_time_used = (end_time - begin_time) / CLOCKS_PER_SEC;
				cout << endl << "Shell Sort ran for " << cpu_time_used << " secs.";

				checkResults(wData, sz);
				ofilename = "lab5_Shell_Sort_out.txt";
				writefile(wData, sz, ofilename);

				if (sz < 0)	 {
					 cerr << endl << "ERROR: Output File could not be opened." <<endl;
					 cerr << "       Quitting Now!" << endl << endl;
					 return 0;
				}
				else cout << endl << "Output written to " << ofilename << endl;

				break;

			
			case 0: // Exit Program

					cout << endl << "Received program exit command - I QUIT!" << endl << endl;

					return 0;

			default: // Error in selection

					cout << endl << "Incorrect selection, try again from the menu below." << endl;

		} // switch

	} // while
	
	return 0;
}
