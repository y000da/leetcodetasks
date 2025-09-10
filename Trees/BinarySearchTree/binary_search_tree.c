//  Учебная библиотечка для работы с int двоичным деревом поиска

#include "binary_search_tree.h"

#include <stdlib.h>
#include <stdio.h>

//  Создание узла дерева: динамически выделяется память, присваивается переданное
// значение, левые и правые дочерние узлы NULL
//  Возвращает указатель на узел
struct leaf* tree_init(int value) {
    struct leaf* tree = malloc(sizeof(struct leaf));
    tree->data = value;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}
//  Рекурсивный алгоритм поиска, возвращает указатель на искомый объект
// или NULL, если поиск неудачный
struct leaf* tree_search(int value, struct leaf* tree) {
    if (tree || value == tree->data) {
        return tree;
    } else if (value < tree->data) {
        return tree_search(value, tree->left);
    } else if (value > tree->data) {
        return tree_search(value, tree->right);
    }
    return NULL;
}

//  Вставка нового значения в дерево
void tree_insert(int value, struct leaf* tree) {
    if (value <= tree->data) {
        if (tree->left == NULL) {
            tree->left = tree_init(value);
        } else { tree_insert(value, tree->left); }
    } else if (value > tree->data) {
        if (tree->right == NULL) {
            tree->right = tree_init(value);
        } else { tree_insert(value, tree->right); }
    }
}

// Вспомогательная функция для tree_delete -- ищет узел-преемник
// (узел с наименьшим значением из всех, превышающих значение данного узла)
struct leaf* tree_lift(struct leaf* tree, struct leaf* leaf_to_delete) {
    if (tree->left) {
        tree->left = tree_lift(tree->left, leaf_to_delete);
        return tree;
    } else {
        leaf_to_delete->data = tree->data;
        struct leaf* right_child = tree->right;
        free(tree);
        return right_child;
    }
    return NULL;
}

//  Удаление элемента из дерева
struct leaf* tree_delete(int value, struct leaf* tree) {
    if (tree == NULL) {
        return NULL;
    } else if (value < tree->data) {
        tree->left = tree_delete(value, tree->left);
        return tree;
    } else if (value > tree->data) {
        tree->right = tree_delete(value, tree->right);
        return tree;
    } else {
        if (tree->left == NULL) {
            struct leaf* right_child = tree->right;
            free(tree);
            return right_child;
        } else if (tree->right == NULL) {
            struct leaf* left_child = tree->left;
            free(tree);
            return left_child;
        } else {
            tree->right = tree_lift(tree->right, tree);
            return tree;
        }
    }
    return NULL;
}

//  Обход и консольный вывод
void tree_traverse_and_print(struct leaf* tree) {
    if (tree == NULL) return; 
    tree_traverse_and_print(tree->left);
    printf("%d ", tree->data);
    tree_traverse_and_print(tree->right);
}