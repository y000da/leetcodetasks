int removeElement(int* nums, int numsSize, int val) 
{

    int val_count = 0;
    int k = 0;
    int left = 0;
    int right = numsSize - 1;

    for(int i = 0; i < numsSize; i++) { if(nums[i] == val) { val_count++; } }

    k = numsSize - val_count;
    
    while(val_count > 0 && k > 0)
    {
        if(nums[right] == val) { right--; val_count--; continue; }

        if(nums[left] == val)
        {
            int tmp = nums[right];
            nums[right] = nums[left];
            nums[left] = tmp;
            left++;
            right--;
            val_count--;
        }
        else left++;

    }
    
    return k;

}