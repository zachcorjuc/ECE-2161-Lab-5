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
