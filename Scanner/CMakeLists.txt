cmake_minimum_required(VERSION 3.15)
project(mjava-scanner)

set(CMAKE_CXX_STANDARD 14)

include_directories(
  ./
)

add_executable(mjava-scanner
  main.cpp
  scanner/scanner.cpp
  scanner/scanner.h
  scanner/dfa_state.h
  utils/error_msg_builder.h
  utils/mjava_utils.cpp
  utils/mjava_utils.h)