cmake_minimum_required(VERSION 3.15)
project(mjava-parser)

set(CMAKE_CXX_STANDARD 14)

include_directories(
  ../Scanner
  ../Utils
  ./
)

add_executable(mjava-parser
  main.cpp
  parser/syntax_tree_node.h
  parser/syntax_tree_node.cpp
  parser/parser.h
  parser/parser.cpp
  ../Utils/utils/syntax_type.h
  ../Scanner/scanner/scanner.h
  ../Scanner/scanner/scanner.cpp
  ../Utils/utils/mjava_utils.h
  ../Utils/utils/mjava_utils.cpp)
