cmake_minimum_required(VERSION 3.15)
project(mjava-parser)

set(CMAKE_CXX_STANDARD 14)

include_directories(
  ../Scanner
  ../Utils
  ./
)

add_executable(mjava-parser
  main.cpp parser/syntax_tree_node.cpp parser/syntax_tree_node.h ../Utils/utils/syntax_type.h parser/parser.cpp parser/parser.h)
