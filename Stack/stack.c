#include "stack.h"

#include <stdlib.h>
#include <stdio.h>


obj* push(obj* top, int data) {
  obj* ptr = malloc(sizeof(obj));
  ptr->data = data;
  ptr->next_object = top;
  return ptr;
}

obj* pop(obj* top) {
  if (top == NULL) { return top; }
  printf("Deleted: %d\n", top->data);
  obj* ptr_next = top->next_object;
  free(top);
  return ptr_next;
}

void show_stack(const obj* top) {
  const obj* current = top;
  while (current != NULL) {
    printf("%d\n", current->data);
    current = current->next_object;
  }
}
