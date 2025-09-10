void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) 
{

    int index_answer, index_1, index_2;

    //Для корректной индексации (т.к. передаем размеры массивов не от 0)
    index_1 = m - 1; 
    index_2 = n - 1; 
    index_answer = nums1Size - 1;
    
    //Идем по массивам справа
    while (index_1 >= 0 && index_2 >= 0) 
    
    {
        
    //Если число в первом массиве больше числа во втором,
        if (nums1[index_1] > nums2[index_2]) 
        { 
    //то записываем в конец первого массива это число
            nums1[index_answer] = nums1[index_1]; 
    //Уменьшаем индексы 
            index_answer--;
            index_1--;

        }
        else 
        { 
    //Иначе, записываем в конец число из второго массива    
            nums1[index_answer] = nums2[index_2]; 
    //И уменьшаем индексы
            index_answer--;
            index_2--;
        }//end if

    }//end while
    
    //Для случая, если n > m
    while (index_2 >= 0) 
    {
        
        nums1[index_answer] = nums2[index_2];
        index_answer--;
        index_2--;

    }//end while
}