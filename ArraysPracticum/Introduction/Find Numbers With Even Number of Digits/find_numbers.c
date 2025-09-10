int findNumbers(int* nums, int numsSize) 
{

    int DigitsNum = 0;
    int count;

    for(int i = 0; i < numsSize; i++)
    {

        DigitsNum = (int)log10(nums[i]) + 1;
        if (DigitsNum % 2 == 0) { count ++; }

    }

    return count;

}