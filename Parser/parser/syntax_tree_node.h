//
// Created by 薛轲翰 on 2020/6/26.
//

#ifndef MJAVA_COMPILER_PARSER_PARSER_SYNTAX_TREE_NODE_H_
#define MJAVA_COMPILER_PARSER_PARSER_SYNTAX_TREE_NODE_H_

#include <string>
#include <vector>
#include "utils/syntax_type.h"

class SyntaxTreeNode {
 public:
  SyntaxTreeNode();
  virtual ~SyntaxTreeNode();

  bool IsNull() const;
  void SetIsNull(bool is_null);

  bool IsIdentifierType() const;
  void SetIdentifierType(bool identifier_type);

  const std::string &GetValue() const;
  void SetValue(const std::string &value);

  NodeType GetNodeType() const;
  void SetNodeType(NodeType node_type);

  const std::vector<SyntaxTreeNode> &GetChildrenList() const;
  void AddChildNode(const SyntaxTreeNode& syntax_tree_node);

  Declaration GetDeclaration() const;
  void SetDeclaration(Declaration declaration);

  Statement GetStatement() const;
  void SetStatement(Statement statement);

  Expression GetExpression() const;
  void SetExpression(Expression expression);

  SubExpExp GetSubExpExp() const;
  void SetSubExpExp(SubExpExp sub_exp_exp);

  VarType GetVarType() const;
  void SetVarType(VarType var_type);

 private:
  bool is_null_;
  bool identifier_type_;
  std::string value_;
  NodeType node_type_;
  std::vector<SyntaxTreeNode> children_list_;
  Declaration declaration_;
  Statement statement_;
  Expression expression_;
  SubExpExp sub_exp_exp_;
  VarType var_type_;
};

#endif //MJAVA_COMPILER_PARSER_PARSER_SYNTAX_TREE_NODE_H_
