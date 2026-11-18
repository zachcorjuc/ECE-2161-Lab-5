#include "helper_fns.h"

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
