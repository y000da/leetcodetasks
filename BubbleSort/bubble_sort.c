#include "bubble_sort.h"


int* bubbleSort(int* arr, int arr_size) {
  int unsorted_index = arr_size - 1;
  char sorted = 0;

  while (!sorted) {
    sorted = 1;
    
    for (int i = 0; i < unsorted_index; i++) {
      if (arr[i] > arr[i+1]) {
        int tmp = arr[i];
        arr[i] = arr[i+1];
        arr[i+1] = tmp;
        sorted = 0;
        }

      unsorted_index -= 1;
    }
  }
    
  return arr;
}