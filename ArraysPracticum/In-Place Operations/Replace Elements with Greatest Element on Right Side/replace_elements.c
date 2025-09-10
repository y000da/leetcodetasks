int* replaceElements(int* arr, int arrSize, int* returnSize) 
{
    int tmp = 0;
    int max = arr[arrSize-1];
    *returnSize=arrSize;
    
    for(int i = arrSize-1; i > 0; i--)
    {
        
        tmp = arr[i-1];
        arr[i-1] = max;

        if(tmp > max) max = tmp;

    }

    arr[arrSize-1] = -1;
    
    return arr;
}