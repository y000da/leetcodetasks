int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
  int left = 0;
  int mid = 0;
  int right = sizeof(nums)/sizeof(int) - 1;
  int answer[] = {-1, -1};

  while (left <= right) {
    mid = left + (right - left) / 2;
    if (target == nums[mid]) {
      right = mid;
      while (nums[right] == target) {
        ++right;
      }
      left = mid;
      while (nums[left] == target) {
        --left;
      }
      answer[0] = left;
      answer[1] = right;
    } else if (target < nums[mid]) {
      right = mid - 1;
    } else if (target > nums[mid]) {
      left = mid + 1;
  }
  return answer;
}