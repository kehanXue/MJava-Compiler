//
// Created by 薛轲翰 on 2020/6/26.
//

#ifndef MJAVA_COMPILER_UTILS_UTILS_SYNTAX_TYPE_H_
#define MJAVA_COMPILER_UTILS_UTILS_SYNTAX_TYPE_H_

enum class NodeType {
  DECLARATION = 0,
  STATEMENT,
  EXPRESSION,
  SUB_EXP_EXP,
  TYPE,
  CLASS_NAME,
  MAIN_ARGS_NAME,
  EXTENDS_CLASS_NAME,
  VAR_NAME,
  ARRAY_NAME,
  NUM,
  EXPRESSION_IDENTIFIER,
  METHOD_NAME
};

enum class Declaration {
  GOAL = 0,
  MAIN_CLASS,
  CLASS_DECLARATION,
  VAR_DECLARATION,
  METHOD_DECLARATION
};

enum class VarType {
  INT_ARRAY = 0,
  BOOLEAN,
  INT,
  IDENTIFIER
};

enum class Statement {
  IF_STATEMENT = 0,
  WHILE_STATEMENT,
  PRINT_STATEMENT,
  VAR_ASSIGN_STATEMENT,
  ARRAY_ASSIGN_STATEMENT,
  SERIES_STATEMENT
};

enum class Expression {
  INT_EXPRESSION = 0,
  TRUE_EXPRESSION,
  FALSE_EXPRESSION,
  IDENTIFIER_EXPRESSION,
  THIS_EXPRESSION,
  NEW_ARRAY_EXPRESSION,
  NEW_EXPRESSION,
  NOT_EXPRESSION,
  BRACE_EXPRESSION
};

enum class SubExpExp {
  OP_SUB_EXP = 0,
  EXP_SUB_EXP,
  LENGTH_SUB_EXP,
  METHOD_SUB_EXP,
  NULL_SUB_EXP
};

#endif //MJAVA_COMPILER_UTILS_UTILS_SYNTAX_TYPE_H_
