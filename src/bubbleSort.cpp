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
