typedef struct stack_object {
    int data;
    struct stack_object* next_object;
} obj;

obj* push(obj* top, int data);
obj* pop(obj* top);
void show_stack(const obj* top);