//
// Created by 薛轲翰 on 2020/6/25.
//

#include "parser/parser.h"

int main(int argc, char** argv) {
  Parser parser;

  if (argc > 1) {
    for (int i = 1; i < argc; ++i) {
      parser.Run(std::string(argv[i]));
    }
  }

  return 0;
}