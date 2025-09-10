#include "queue.h"

#include <stdlib.h>
#include <stdio.h>

obj* head;

obj* enqueue(obj* queue, int data) {
  if (queue == NULL) {
    queue = malloc(sizeof(obj));
    queue->data = data;
    queue->next_object = NULL;
    head = queue;
    return queue;
  } else {
    obj* ptr = malloc(sizeof(obj));
    ptr->data = data;
    ptr->next_object = NULL;
    queue->next_object = ptr;
    return ptr;
  }
}

obj* dequeue(obj* queue) {
  if (queue == NULL) { return queue; }
  printf("Deleted: %d\n", head->data);
  obj* ptr = head->next_object;
  free(queue);
  return ptr_prev;
}

void show_queue(const obj* queue) {
  const obj* current = queue;
  while (current != NULL) {
    printf("%d\n", current->data);
    current = current->next_object;
  }
}
