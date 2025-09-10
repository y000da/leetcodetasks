#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "include/CEssentials/hashtable.h"

int main() {
  HT(int, int) int_to_int_map;
  HT(char*, int) char_to_int_map;

  ht_init(int_to_int_map);
  ht_init(char_to_int_map);

  size_t index_of_inserted_element;
  int absent;
  ht_put(char_to_int_map, char*, int, "Burger", index_of_inserted_element, absent, ht_str_hash, ht_str_eq);
  if (absent) {
    ht_value(char_to_int_map, index_of_inserted_element) = 10;
  }

  ht_get(char_to_int_map, "Burger", index_of_inserted_element, ht_str_hash, ht_str_eq);
  if (ht_valid(char_to_int_map, index_of_inserted_element)) {
    printf("%s = %i", ht_key(char_to_int_map, index_of_inserted_element), 
          ht_value(char_to_int_map, index_of_inserted_element));
  }

  ht_capacity(char_to_int_map) = 10;
  int i;
  ht_for_each(char_to_int_map, i) {
    ht_put(char_to_int_map, char*, int, "Burger", index_of_inserted_element, absent, ht_str_hash, ht_str_eq);
    if (absent) {
    ht_value(char_to_int_map, index_of_inserted_element) = i;
    }
  }

  ht_for_each(char_to_int_map, i) {
    ht_get(char_to_int_map, "Burger", index_of_inserted_element, ht_str_hash, ht_str_eq);
    if (ht_valid(char_to_int_map, index_of_inserted_element)) {
      printf("%s = %i", ht_key(char_to_int_map, index_of_inserted_element), 
            ht_value(char_to_int_map, index_of_inserted_element));
    }
  }

  return 0;
}