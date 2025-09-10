void moveZeroes(int* nums, int numsSize) {
    
    int ind_1 = 0;
 int ind_2 = 0;
 int tmp = 0;

 while(ind_1 < numsSize)
 {
     
     if(nums[ind_1] != 0 && numsSize > 1)
     {
         tmp = nums[ind_2];
         nums[ind_2] = nums[ind_1];
         nums[ind_1] = tmp;
         ind_1++;
         ind_2++;

     }
     else ind_1++;

 }

 
}