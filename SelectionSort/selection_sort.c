#include "selection_sort.h"


int* SelectionSort(int* arr, int arr_size) {
  for (int i = 0; i < arr_size - 1; i++) {
    int lowest_number_index = i;
    for (int j = i+1; j < arr_size; j++) {
      if (arr[j] < arr[lowest_number_index]) { 
        lowest_number_index = j; 
      }
    }  
    if (lowest_number_index != i) {
      int tmp = arr[i];
      arr[i] = arr[lowest_number_index];
      arr[lowest_number_index] = tmp;
    }
  }
  return arr;
}
