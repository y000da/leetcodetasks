int checkIfExist(int* arr, int arrSize)
{

    for(int i = 0; i < arrSize; i++)
    {

        for(int j = 1; j < arrSize; j++)
        {

            if((arr[i] == 2 * arr[j]) && (i != j)) { return 1; }

        }

    }

    return 0;

}