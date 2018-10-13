cmake_minimum_required(VERSION 2.8.4)
project(Trie)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g -Wall -pedantic")
# Generate shared library libTrie.so file.
ADD_LIBRARY(Trie SHARED Trie.cpp)

add_executable(Example1.out Example1.cpp)
target_link_libraries(Example1.out Trie)
