//  Универсальная хэш-таблица, не зависящая от типа данных
//
//  ОБЪЕКТЫ:
//  ht(key_type, value_type) - структура
//  ht_begin(h) - начало таблицы
//  ht_end(h) - конец таблицы
//  Поля структуры:
//  capacity - текущий размер хэш-таблицы
//  size - количество занятых элементов
//  max_size - макисмальный размер до увеличения
//  flags - массив из capacity флагов, каждый из которых задаёт состояние
// соответствующей ему ячейки: 0 - свободна, 1 - занята, 2 - удалена
//  keys - массив ключей
//  values - массив значений
//
//  МЕТОДЫ:
//  ht_init(h) - конструктор
//  ht_destroy(h) - деструктор
//  ht_size(h) - получение размера
//  ht_max_size(h) - получение максимального размера
//  ht_capacity(h) - получение вместимости
//  ht_key(h, index) - получение ключа по адресу
//  ht_value(h, index) - получение значения по адресу
//  ht_clear(h) - очистка таблицы
//  ht_get(h, key, result, hash_func, eq_func) - получение элемента
//  ht_put(h, key_type, value_type, key, index, absent,
//          hasn_func, eq_func) - добавление элемента
//  ht_valid(h, index) - проверка существования элемента
//  ht_delete(h, index) - удаление элемента
//  ht_reserve(h, key_type, value_type, new_capacity,
//              success, hash_func) - проверка требуемого размера таблицы


#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


//-----------Макрос таблицы-----------
//
//  Принимает тип ключа и значения,
// объявляет структуру, содержащую поля:

#define ht(key_type, value_type) struct { \
  size_t size, max_size, capacity; \
  char *flags; \
  key_type *keys; \
  value_type *values; \
}

#define ht_begin(h) (0)
#define ht_end(h) ((h).capacity)

//-----------Конструктор структуры-----------
//
//  Трюк с do {...} while (0) нужен, чтобы записать в макросе несколько команд,
// которые гарантировано выполняться один раз
//  Инициализация хэш-таблицы не приводит к выделению памяти
#define ht_init(h) do { \
  (h).size = (h).max_size = (h).capacity = 0; \
  (h).flags = NULL; \
  (h).keys = NULL; \
  (h).values = NULL; \
} while (0)

//-----------Деструктор структуры-----------
//
#define ht_destroy(h) do { \
  free((h).values); \
  free((h).keys); \
  free((h).flags); \
} while (0)

//-----------Запросы к структуре-----------
//
//  Для получения различных параметров контейнера,
// а также получение к ключам и значениям, если известен их адрес
#define ht_size(h) ((h).size)
#define ht_max_size(h) ((h).max_size)
#define ht_capacity(h) ((h).capacity)
#define ht_key(h, index) ((h). keys[(index)])
#define ht_value(h, index) ((h).values[(index)])

//-----------Очистка контейнера-----------
//
#define ht_clear(h) do { \
  (h).size = 0; \
  if ((h).flags) { memset((h).flags, 0, (h).capacity); } \
} while (0)

//-----------Поиск value по key-----------
//
//  В качестве одного из параметров принимаем имя переменной (result), в которую
// следует поместить результат, т.к. мы не можем вернуть значение из макроса как
// из обычной функции.
//  Помимо самой таблицы, ключа и имени переменной результата,
// мы принимаем хэш-функцию и функцию сравнения, т.к. их неоткуда
// больше узнать.
//  Пользовательские переменные в скобках, чтобы корректно обработать передачу
// сложного выражения
//  На выходе в result будет лежать либо индекс элемента с запрошенным ключом,
// либо индекс свободного элемента
#define ht_get(h, key, result, hash_func, eq_func) do { \
  if (!(h).size) { \
      (result) = 0; \
/*  Оператор break работает как преждевременный возврат из функции, т.к. 
она обрамлена как цикл */ \
      break; \
  } \
/*  Вычисляем маску для быстрого нахождения остатка от деления 
на размер таблицы*/ \
  size_t ht_mask = (h).capacity - 1; \
  (result) = hash_func(key) & ht_mask; \
/*  Вычисление значения хэш-функции и обрезка её до размера
массива с помощью маски*/ \
  size_t ht_step = 0; \
/*  Цикл поиска элемента. Если элемент удален (флаг = 2), пропускаем.
Если элемент занят, вызываем функцию сравнения. При пропуске увеличиваем
индекс на величину шага и затем увеличиваем сам шаг*/ \
  while ((h).flags[(result)] == 2 || ((h).flags[(result)] == 1 &&  \
          !eq_func((h).keys[(result)], (key)))) { \
    (result) = ((result) + ++ht_step) & ht_mask; \
  } \
} while (0)

//-----------Проверка существования элемента-------
//
#define ht_valid(h, index) ((h).flags && (h).flags[(index)] == 1)

//-----------Проверка требуемого размера таблицы-----------
//
#define ht_reserve(h, key_type, value_type, new_capacity, success, hash_func) do { \
  /*  Нужно ли вообще расширять место?*/ \
    if (new_capacity <= (h).max_size) { \
      (success) = true; \
      break; \
    } \
  /*  Вычисление новой емкости*/ \
    size_t ht_new_capacity = (new_capacity); \
  /*  Вспомогательная функция огруления вверх до степени двойки*/ \
    roundupsize(ht_new_capacity); \
  /*  Если полученный результат меньше текущей емкости, умножаем его на 2*/ \
    if (ht_new_capacity <= (h).capacity) { \
      ht_new_capacity <<= 1; \
    } \
  /*  Выделяем память под все структуры и обрабатываем ошибки выделения памяти*/ \
    char *ht_new_flags = malloc(ht_new_capacity); \
    if (!ht_new_flags) { \
      (success) = false; \
      break; \
    } \
    key_type *ht_new_keys = malloc(ht_new_capacity * sizeof(key_type)); \
    if (!ht_new_keys) { \
      free(ht_new_flags); \
      (success) = false; \
      break; \
    } \
    value_type *ht_new_values = malloc(ht_new_capacity * sizeof(value_type)); \
    if (!ht_new_values) { \
      free(ht_new_keys); \
      free(ht_new_flags); \
      (success) = false; \
      break; \
    } \
  /*  Очистка новых флагов и перехэширование*/ \
    memset(ht_new_flags, 0, ht_new_capacity); \
    size_t ht_mask = ht_new_capacity - 1; \
  /* Итерируем по всем элементам, пропуская свободные и удаленные*/ \
    for (size_t ht_i = 0; ht_i < (h).capacity; ht_i++) { \
      if ((h).flags[ht_i] != 1) continue; \
  /*  Для каждого элемента вычисляем хэш и ищем место в новой таблице*/ \
      size_t ht_j = hash_func((h).keys[ht_i]) & ht_mask; \
      size_t ht_step = 0; \
      while (ht_new_flags[ht_j]) { \
        ht_j = (ht_j + ++ht_step) & ht_mask; \
      } \
  /*  Копирование элемента из старой таблицы в новую с пометкой
  о занятости места*/ \
      ht_new_flags[ht_j] = 1; \
      ht_new_keys[ht_j] = (h).keys[ht_i]; \
      ht_new_values[ht_j] = (h).values[ht_i]; \
    } \
  /* Старая таблица больше не нужна, освобождаем память и
  обновляем указатели в структуре на новые области памяти, 
  а также обновить емкость и максимальный размер, поставить
  статус успешного выполнения*/ \
    free((h).values); \
    free((h).keys); \
    free((h).flags); \
    (h).flags = ht_new_flags; \
    (h).keys = ht_new_keys; \
    (h).values = ht_new_values; \
    (h).capacity = ht_new_capacity; \
  /*  Новый максимальный размер ~=75% от новой емкости*/ \
    (h).max_size = (ht_new_capacity >> 1) + (ht_new_capacity >> 2); \
    (success) = true; \
  } while (0)
  

//-----------Добавление элемента в хэш-таблицу-----------
//  
//  Принимает таблицу, типы ключа и значения (нужны для переаллокации памяти, если
// в таблице кончится место), ключ, который мы хотим добавить, хэш-функцию и 
// функцию сравнения.
//  Возвращает два числа - индекс вставленного элемента и результат операции - 
// переменная absent (1 = вставлен, 0 = уже существовал и есть возможность
// обновить значение, -1 = ошибка выделения памяти)
#define ht_put(h, key_type, value_type, key, index, absent, \
                      hasn_func, eq_func) do { \
/* Убеждаемся, что в таблице хватает места, а если нет - расширяем её*/ \
  bool ht_success; \
  size_t ht_new_size = (h).size ? (h).size + 1 : 2; \
/*  Эта функция проверяет, что в таблице можно сохранить не менее
HashTable_new_size элементов, в противном случае она переаллоцирует
таблицу с увеличением размера*/ \
  ht_reserve((h), key_type, value_type, ht_new_size, ht_success, hash_func); \
  if (!ht_success) { \
    (absent) = -1; \
    break; \
  } \
  /*  Аналогичный поиску алгоритм поиска элемента, только удаленные
  элементы не пропускаются и не останавливаемся на обнаружении элемента
  (или его отсутствия), а идем дальше.*/ \
  size_t ht_mask = (h).capacity - 1; \
  (index) = hash_func(key) & ht_mask; \
  size_t ht_step = 0; \
  while ((h).flags[(index)] == 2 || ((h).flags[(index)] == 1 && \
          !eq_func((h).keys[(index)], (key)))) { \
      (index) = ((index) + ++ht_step) & ht_mask; \
  } \
/*  Если место не пустое, то просто возвращаем absent = 0*/ \
  if ((h).flags[(index)] == 1) { \
		(absent) = 0; \
	} else { \
/*Если место пустое, то помечаем его занятым и копируем ключ
в соотвествующую ячейку таблицы ключей, увеличиваем счетчик элементов.
В absent вернем 1*/ \
		(h).flags[(index)] = 1; \
		(h).keys[(index)] = (key); \
		(h).size++; \
		(absent) = 1; \
	} \
} while (0)

//-----------Удаление элемента-----------
//
//  Переводим элемент в состояние "удалено" и уменьшаем
// счетчик количества элементов
#define ht_delete(h, index) do { \
  (h).flags[(index)] = 2; \
  (h).size--; \
} while (0)

//-----------Итерирование по таблице-----------
//
static inline size_t ht_next_valid_index(const char *flags, size_t capacity,
                                          size_t index) {
  while (index < capacity && flags[index] != 1) {
    index++;
  }
  return index;
}

#define ht_for_each(h, index) for ( \
  size_t index = ht_next_valid_index((h).flags, (h).capacity, ht_begin((h))); \
  index != ht_end((h)) && ht_valid((h), index); \
  index++, index = ht_next_valid_index((h).flags, (h).capacity, index) \
)

//-----------Округления вверх до степени двойки-----------
//
//  Округление 8-битного int
#define roundup8(x) (--(x), (x)|=(x)>>1, (x)|=(x)>>2, (x)|=(x)>>4, ++(x))
//  Округление 16-битного int
#define roundup16(x) (--(x), (x)|=(x)>>1, (x)|=(x)>>2, (x)|=(x)>>4, \
                      (x)|=(x)>>8, ++(x))
//  Округление 32-битного int
#define roundup32(x) (--(x), (x)|=(x)>>1, (x)|=(x)>>2, (x)|=(x)>>4, \
                      (x)|=(x)>>8, (x)|=(x)>>16, ++(x))
//  Округление 64-битного int
#define roundup64(x) (--(x), (x)|=(x)>>1, (x)|=(x)>>2, (x)|=(x)>>4, \
                      (x)|=(x)>>8, (x)|=(x)>>16, (x)|=(x)>>32, ++(x))                     
//  Округление size_t переменной до ближайшей степени двойки
#if SIZE_MAX == UINT64_MAX
#define roundupsize(x) roundup64(x)
#elif SIZE_MAX == UINT32_MAX
#define roundupsize(x) roundup32(x)
#elif SIZE_MAX == UINT16_MAX
#define roundupsize(x) roundup16(x)
#elif SIZE_MAX == UINT8_MAX
#define roundupsize(x) roundup8(x)
#endif