typedef struct queue_object {
    int data;
    struct queue_object* next_object;
    struct queue_object* prev_object;
} obj;

obj* enqueue(obj* queue, int data);
obj* dequeue(obj* queue);
void show_queue(const obj* queue);
