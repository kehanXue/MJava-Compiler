//
// Created by 薛轲翰 on 2020/6/25.
//

#ifndef MJAVA_COMPILER_SCANNER_UTILS_TOKEN_TYPE_H_
#define MJAVA_COMPILER_SCANNER_UTILS_TOKEN_TYPE_H_

enum class TokenType {
  CLASS = 0,
  PUBLIC,
  STATIC,
  VOID,
  MAIN,
  STRING,
  EXTENDS,
  RETURN,
  INT,
  BOOLEAN,
  IF,
  ELSE,
  WHILE,
  SYSTEM_OUT_PRINTLN,
  LENGTH,
  TRUE,
  FALSE,
  THIS,
  NEW,

  IDENTIFIER,
  DIGIT,

  L_PARENTHESIS,
  R_PARENTHESIS,
  L_PARENTHESES,
  R_PARENTHESES,
  L_BRACE,
  R_BRACE,
  COMMA,
  SEMICOLON,
  ASSIGNMENT,
  LESS_THAN,
  ADD,
  SUB,
  MULTI,
  POINT,
  UN,
  AND,

  EOF_TOKEN,
  NULL_TOKEN,
  ERROR,
  SPACE,
  TAB,
  ENTER
};

#endif //MJAVA_COMPILER_SCANNER_UTILS_TOKEN_TYPE_H_
