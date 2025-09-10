int removeDuplicates(int* nums, int numsSize) 
{
    
    int validIndex = 0;

    for(int i = 1; i < numsSize; i++)
    {
        
        if(nums[i] != nums[i-1])
        {
           
            nums[validIndex]=nums[i];
            validIndex++;

        }

    }

    return validIndex;
    
}