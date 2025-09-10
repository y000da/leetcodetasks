int validMountainArray(int *arr, int arrSize)
{
    int max = arr[0];
    int index_max = 0;
    int inc_flag = 0;
    int dec_flag = 0;

    for(int i = 0; i < arrSize; i++)
        if(max < arr[i]) max = arr[i];

    for(int i = 0; i < arrSize; i++)
        if(arr[i] == max) index_max = i;

    for(int i = 0; i < index_max; i++)
        if(arr[i] < arr[i+1]) inc_flag = 1;
        else return 0;

    if(inc_flag == 1)
        for(int i = index_max+1; i < arrSize; i++)
            if(arr[i] < arr[i-1]) dec_flag = 1;
            else return 0;

    if(dec_flag && inc_flag == 1) { return 1; }

}