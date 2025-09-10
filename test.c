#include <stdio.h>
#include <stdlib.h>

#include "Trees/BinarySearchTree/binary_search_tree.h"


int main() {
  struct leaf* tree = tree_init(10);
  tree->left = tree_init(7);
  tree->right = tree_init(12);
  tree->right->right = tree_init(13);
  tree->right->left = tree_init(11);
  tree_delete(12, tree);
  printf("root: %d left: %d right: %d", tree->data, tree->left->data, tree->right->data);
  int value_that_exist = 12;
  struct leaf* search_leaf = tree_search(value_that_exist, tree);
  int value_that_not_exist = 15;
  printf("\nexisting value on addres %p : %d\n", search_leaf, search_leaf->data);
  struct leaf* non_existing_value = tree_search(value_that_not_exist, tree);
  printf("\nnon existing value on addres %p\n", non_existing_value);
  tree_insert(6, tree);
  printf("\nNew value %d on addres %p\n", tree->left->left->data, tree->left->left);
  tree_traverse_and_print(tree);
  tree_delete_whole_tree(tree);
  printf("\n%p\n%p\n%p\n", tree, tree->left, tree->right);
}