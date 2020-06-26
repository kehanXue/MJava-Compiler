//
// Created by 薛轲翰 on 2020/6/26.
//

#ifndef MJAVA_COMPILER_PARSER_PARSER_PARSER_H_
#define MJAVA_COMPILER_PARSER_PARSER_PARSER_H_

#include <fstream>
#include <vector>
#include <memory>

#include "scanner/scanner.h"
#include "syntax_tree_node.h"

class Parser {
 public:
  Parser();
  virtual ~Parser();
  void Run(const std::string& input_file_name);

  void PreOrder(SyntaxTreeNode node);
  bool match(TokenType expected);

  SyntaxTreeNode StartParse();
  SyntaxTreeNode Goal();
  SyntaxTreeNode MainClass();
  SyntaxTreeNode ClassDeclaration();
  SyntaxTreeNode VarDeclaration();
  SyntaxTreeNode MethodDeclaration();
  SyntaxTreeNode Type();
  SyntaxTreeNode Statement();
  SyntaxTreeNode StatementSeries();
  SyntaxTreeNode IfStatement();
  SyntaxTreeNode WhileStatement();
  SyntaxTreeNode PrintStatement();
  SyntaxTreeNode AssignStatement();
  SyntaxTreeNode VarAssignStatement();
  SyntaxTreeNode ArrayAssignStatement();
  SyntaxTreeNode Expression();
  SyntaxTreeNode IntExpression();
  SyntaxTreeNode TrueExpression();
  SyntaxTreeNode FalseExpression();
  SyntaxTreeNode IdentifierExpression();
  SyntaxTreeNode ThisExpression();
  SyntaxTreeNode NewArrayExpression();
  SyntaxTreeNode NewExpression();
  SyntaxTreeNode NotExpression();
  SyntaxTreeNode BraceExpression();
  SyntaxTreeNode SubExpStatament();
  SyntaxTreeNode OpSubExp();
  SyntaxTreeNode ExpSubExp();
  SyntaxTreeNode LengthSubExp();
  SyntaxTreeNode MethodSubExp();
  static SyntaxTreeNode NullSubExp();

  std::string CurrentTokenToString();

 private:
  std::ofstream output_token_file_;
  std::ofstream output_error_file_;

  std::shared_ptr<Scanner> p_scanner_;
  std::vector<TokenType> token_type_list_;
  int current_token_pose_;
};

#endif //MJAVA_COMPILER_PARSER_PARSER_PARSER_H_
