cmake_minimum_required(VERSION 3.15)
project(mjava-scanner)

set(CMAKE_CXX_STANDARD 14)

include_directories(
  ../Utils
  ./
)

add_executable(mjava-scanner
  main.cpp
  scanner/scanner.cpp
  scanner/scanner.h
  scanner/dfa_state.h
  ../Utils/utils/error_msg_builder.h
  ../Utils/utils/mjava_utils.cpp
  ../Utils/utils/mjava_utils.h ../Utils/utils/token_type.h)