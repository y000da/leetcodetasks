int findMaxConsecutiveOnes(int* nums, int numsSize) 
{
    
    int max = 0;
    int sum = 0;
    
    for (int i = 0; i < numsSize; i++)
    {
    
        sum = (sum+nums[i])*nums[i];
        
        if(max < sum) { max = sum; }
    
    }
   
    return max;
   
}