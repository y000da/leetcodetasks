cmake_minimum_required(VERSION 2.8)

project(test_trees)

set(SOURCE_EXE test.c)

set(SOURCE_LIB Trees/BinarySearchTree/binary_search_tree.c)

add_library(tree STATIC ${SOURCE_LIB})

add_executable(test_tree ${SOURCE_EXE})

target_link_libraries(test_tree tree)
