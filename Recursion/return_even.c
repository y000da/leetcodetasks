#include <stdio.h>
#include <stdlib.h>

// Рекурсивная функция для фильтрации чётных чисел
// arr - исходный массив
// size - размер исходного массива
// result - массив для результата (изначально NULL)
// index - текущий индекс в результирующем массиве
int* filter_even_recursive(int* arr, int size, int* result, int* index) {
    // Базовый случай: если массив пуст, возвращаем результат
    if (size == 0) {
        return result;
    }

    // Если текущий элемент чётный
    if (arr[0] % 2 == 0) {
        // Увеличиваем размер результата
        result = realloc(result, (*index + 1) * sizeof(int));
        // Добавляем элемент в результат
        result[*index] = arr[0];
        (*index)++;
    }

    // Рекурсивный вызов для оставшейся части массива
    return filter_even_recursive(arr + 1, size - 1, result, index);
}

// Обёртка для удобного вызова
int* filter_even(int* arr, int size, int* result_size) {
    int* result = NULL;
    int index = 0;
    result = filter_even_recursive(arr, size, result, &index);
    *result_size = index;
    return result;
}