//
// Created by 薛轲翰 on 2020/6/26.
//

#include "syntax_tree_node.h"

SyntaxTreeNode::SyntaxTreeNode()
    : is_null_(false),
      identifier_type_(false),
      value_(""),
      node_type_(NodeType::UNDEFINED),
      declaration_(Declaration::UNDEFINED),
      statement_(Statement::UNDEFINED),
      expression_(Expression::UNDEFINED),
      sub_exp_exp_(SubExpExp::UNDEFINED),
      var_type_(VarType::UNDEFINED) {

}

SyntaxTreeNode::~SyntaxTreeNode() = default;

bool SyntaxTreeNode::IsNull() const {
  return is_null_;
}

void SyntaxTreeNode::SetIsNull(bool is_null) {
  is_null_ = is_null;
}

bool SyntaxTreeNode::IsIdentifierType() const {
  return identifier_type_;
}

void SyntaxTreeNode::SetIdentifierType(bool identifier_type) {
  identifier_type_ = identifier_type;
}

const std::string &SyntaxTreeNode::GetValue() const {
  return value_;
}

void SyntaxTreeNode::SetValue(const std::string &value) {
  value_ = value;
}

NodeType SyntaxTreeNode::GetNodeType() const {
  return node_type_;
}

void SyntaxTreeNode::SetNodeType(NodeType node_type) {
  node_type_ = node_type;
}

const std::vector<SyntaxTreeNode> &SyntaxTreeNode::GetChildrenList() const {
  return children_list_;
}

void SyntaxTreeNode::AddChildNode(const SyntaxTreeNode &syntax_tree_node) {
  children_list_.emplace_back(syntax_tree_node);
}

Declaration SyntaxTreeNode::GetDeclaration() const {
  return declaration_;
}

void SyntaxTreeNode::SetDeclaration(Declaration declaration) {
  declaration_ = declaration;
}

Statement SyntaxTreeNode::GetStatement() const {
  return statement_;
}

void SyntaxTreeNode::SetStatement(Statement statement) {
  statement_ = statement;
}

Expression SyntaxTreeNode::GetExpression() const {
  return expression_;
}

void SyntaxTreeNode::SetExpression(Expression expression) {
  expression_ = expression;
}

SubExpExp SyntaxTreeNode::GetSubExpExp() const {
  return sub_exp_exp_;
}

void SyntaxTreeNode::SetSubExpExp(SubExpExp sub_exp_exp) {
  sub_exp_exp_ = sub_exp_exp;
}

VarType SyntaxTreeNode::GetVarType() const {
  return var_type_;
}

void SyntaxTreeNode::SetVarType(VarType var_type) {
  var_type_ = var_type;
}



