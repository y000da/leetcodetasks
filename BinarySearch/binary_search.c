#include <stdio.h>

int binarySearch(int* arr, int search_value) {
  int left = 0;
  int mid = 0;
  int right = sizeof(arr)/sizeof(int) - 1;

  while (left <= right) {
    mid = left + (right - left) / 2;
    if (search_value == arr[mid]) {
      return mid;
    } else if (search_value < arr[mid]) {
      right = mid - 1;
    } else if (search_value > arr[mid]) {
      left = mid + 1;
    } else return -1;
  }
}