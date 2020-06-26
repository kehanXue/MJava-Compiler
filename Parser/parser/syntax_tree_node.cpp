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

std::string SyntaxTreeNode::ToString() {
  std::string output;
  switch (node_type_) {
    case NodeType::DECLARATION: {
      switch (declaration_) {
        case Declaration::GOAL:break;
        case Declaration::MAIN_CLASS: {
          output += "<MainClass>";
          break;
        }
        case Declaration::CLASS_DECLARATION: {
          output += "<ClassDeclaration>";
          break;
        }
        case Declaration::VAR_DECLARATION: {
          output += "<VarDeclaration>";
          break;
        }
        case Declaration::METHOD_DECLARATION: {
          output += "<MethodDeclaration>";
          break;
        }
        default: {
          output += "<UnknowDeclaration>";
          break;
        }
      }
    }
      break;
    case NodeType::STATEMENT: {
      switch (statement_) {
        case Statement::IF_STATEMENT: {
          output += "<IfStatement>";
          break;
        }
        case Statement::WHILE_STATEMENT: {
          output += "<WhileStatement>";
          break;
        }
        case Statement::PRINT_STATEMENT: {
          output += "<PrintStatement>";
          break;
        }
        case Statement::VAR_ASSIGN_STATEMENT: {
          output += "<VarAssignStatement>";
          break;
        }
        case Statement::ARRAY_ASSIGN_STATEMENT: {
          output += "<ArrayAssignStatement>";
          break;
        }
        case Statement::SERIES_STATEMENT: {
          output += "<SeriesStatement>";
          break;
        }
        default: {
          output += "<KnownStatement>";
          break;
        }
      }
    }
      break;
    case NodeType::EXPRESSION: {
      switch (expression_) {
        case Expression::INT_EXPRESSION: {
          output += "<IntExpression>";
          break;
        }
        case Expression::TRUE_EXPRESSION: {
          output += "<TrueExpression>";
          break;
        }
        case Expression::FALSE_EXPRESSION: {
          output += "<FalseExpression>";
          break;
        }
        case Expression::IDENTIFIER_EXPRESSION: {
          output += "<IdentifierExpression>";
          break;
        }
        case Expression::THIS_EXPRESSION: {
          output += "<ThisExpression>";
          break;
        }
        case Expression::NEW_ARRAY_EXPRESSION: {
          output += "<NewArrayExpression>";
          break;
        }
        case Expression::NEW_EXPRESSION: {
          output += "<NewExpression>";
          break;
        }
        case Expression::NOT_EXPRESSION: {
          output += "<NotExpression>";
          break;
        }
        case Expression::BRACE_EXPRESSION: {
          output += "<BraceExpression>";
          break;
        }
        default: {
          output += "<KnownExpression>";
          break;
        }
      }
    }
      break;
    case NodeType::SUB_EXP_EXP: {
      switch (sub_exp_exp_) {
        case SubExpExp::OP_SUB_EXP: {
          output += "<OpSubExp>";
          break;
        }
        case SubExpExp::EXP_SUB_EXP: {
          output += "<ExpSubExp>";
          break;
        }
        case SubExpExp::LENGTH_SUB_EXP: {
          output += "<LengthSubExp>";
          break;
        }
        case SubExpExp::METHOD_SUB_EXP: {
          output += "<MethodSubExp>";
          break;
        }
        case SubExpExp::NULL_SUB_EXP: {
          output += "<NullSubExp>";
          break;
        }
        default: {
          output += "<KnownSubExp>";
          break;
        }
      }
    }
      break;
    case NodeType::TYPE: {
      if (identifier_type_) output = "<Type " + value_ + ">";
      else output = "<Type " + VarTypetoString(var_type_) + ">";   //TODO
      break;
    }
    case NodeType::CLASS_NAME: {
      output = "<ClassName " + value_ + ">";
      break;
    }
    case NodeType::MAIN_ARGS_NAME: {
      output = "<MainArgsName " + value_ + ">";
      break;
    }
    case NodeType::EXTENDS_CLASS_NAME: {
      output = "<ExtendsClassName " + value_ + ">";
      break;
    }
    case NodeType::VAR_NAME: {
      output = "<VarName " + value_ + ">";
      break;
    }
    case NodeType::ARRAY_NAME: {
      output = "<ArrayName " + value_ + ">";
      break;
    }
    case NodeType::NUM: {
      output = "<Num" + value_ + ">";
      break;
    }
    case NodeType::EXPRESSION_IDENTIFIER: {
      output = "<ExpressionIdentifier" + value_ + ">";
      break;
    }
    case NodeType::METHOD_NAME: {
      output = "<MethodName" + value_ + ">";
      break;
    }
    default:break;
  }

  return output;
}

std::string SyntaxTreeNode::VarTypetoString(VarType var_type) {
  switch (var_type) {
    case VarType::UNDEFINED: {
      return "Undefined";
    }
    case VarType::INT_ARRAY: {
      return "IntArray";
    }
    case VarType::BOOLEAN:{
      return "Boolean";
    }
    case VarType::INT:{
      return "Int";
    }
    case VarType::IDENTIFIER:{
      return "Identifier";
    }
  }
}



