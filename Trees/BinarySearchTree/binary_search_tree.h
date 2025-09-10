struct leaf {
    int data;
    struct leaf* left;
    struct leaf* right;
};

//  Инициализация дерева (с его помощью можно также создавать новые узлы)
struct leaf* tree_init();

//  Поиск в дереве
struct leaf* tree_search(int value, struct leaf* tree);

//  Вставка 
void tree_insert(int value, struct leaf* tree);

//  Вспомогательная функция
struct leaf* tree_lift(struct leaf* tree, struct leaf* leaf_to_delete);

//  Удаление элемента
struct leaf* tree_delete(int value, struct leaf* tree);

//  Обход и консольный вывод
void tree_traverse_and_print(struct leaf* tree);

//  Удаление всего дерева
void tree_delete_whole_tree(struct leaf* tree);