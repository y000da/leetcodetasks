#include <stdlib.h>
#include <math.h>

#include "sorted_squares.h"


int* sortedSquares(int* nums, int numsSize, int* returnSize) 
{

    int* squares_array = malloc(sizeof(int)*numsSize);

    *returnSize = numsSize;

    int right = numsSize-1, left = 0, ptr = numsSize-1;

    while ((left <= right) && (ptr>=0))
    {
        if (pow(nums[right],2) >= pow(nums[left],2)) { squares_array[ptr] = pow(nums[right--],2); }
        else { squares_array[ptr] = pow(nums[left++],2); }

        ptr--;
    }

    return squares_array;
}