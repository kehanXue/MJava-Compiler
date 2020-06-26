//
// Created by 薛轲翰 on 2020/6/26.
//

#include "parser.h"

Parser::Parser()
    : current_token_pose_(0) {
}

Parser::~Parser() = default;

void Parser::Run(const std::string &input_file_name) {
  current_token_pose_ = 0;

  if (output_syntax_tree_file.is_open()) {
    output_syntax_tree_file.close();
  }
  if (output_error_file_.is_open()) {
    output_error_file_.close();
  }

  p_scanner_ = std::make_shared<Scanner>();
  token_type_list_ = p_scanner_->Run(input_file_name, input_file_name + "_tokens");

  try {
    output_syntax_tree_file.open(input_file_name+"_syntax_tree.txt");
    output_error_file_.open(input_file_name+"_parser_error.txt");

  } catch (...) {
    std::cout << "Open file failed!" << std::endl;
    return;
  }

  SyntaxTreeNode syntax_tree_root_node = StartParse();
  PreOrder(syntax_tree_root_node);

  output_syntax_tree_file.close();
  output_error_file_.close();
}

void Parser::PreOrder(SyntaxTreeNode node) {
  if (!node.IsNull()) {
    output_syntax_tree_file << node.ToString() + "\r\n\t";
    for (const auto& child : node.GetChildrenList()) {
      PreOrder(child);
    }
  }
}

bool Parser::match(TokenType expected) {
  current_token_pose_++;
  if (token_type_list_.at(current_token_pose_) == expected) {
    return true;
  } else {
    output_error_file_ << ErrorMsgBuilder::BuildErrorMsg("unexpected token: " +
        CurrentTokenToString());
    return false;
  }
}

SyntaxTreeNode Parser::StartParse() {
  return Goal();
}

/*
 * Goal-> MainClass { ClassDeclaration } EOF
 */
SyntaxTreeNode Parser::Goal() {
  SyntaxTreeNode goal_node;
  goal_node.SetNodeType(NodeType::DECLARATION);
  goal_node.SetDeclaration(Declaration::GOAL);

  SyntaxTreeNode main_class_child = MainClass();
  goal_node.AddChildNode(main_class_child);

  while (current_token_pose_ < (token_type_list_.size() - 1) &&
      token_type_list_.at(current_token_pose_) == TokenType::CLASS) {
    SyntaxTreeNode class_declaration_child = ClassDeclaration();
    goal_node.AddChildNode(class_declaration_child);
  }

  match(TokenType::EOF_TOKEN);
  return goal_node;
}

/*
 * MainClass-> "class" Identifier "{" "public" "static" "void" "main" "(" "String" "[" "]" Identifier ")" "{" Statement "}" "}
 */
SyntaxTreeNode Parser::MainClass() {
  SyntaxTreeNode main_class_node;
  main_class_node.SetNodeType(NodeType::DECLARATION);
  main_class_node.SetDeclaration(Declaration::MAIN_CLASS);

  match(TokenType::CLASS);
  if (token_type_list_.at(current_token_pose_) == TokenType::IDENTIFIER) {
    SyntaxTreeNode class_name_node;
    class_name_node.SetNodeType(NodeType::CLASS_NAME);
    class_name_node.SetValue(MJavaUtils::TokenTypeToString(token_type_list_.at(current_token_pose_)));
    main_class_node.AddChildNode(class_name_node);
    current_token_pose_++;
  } else {
    current_token_pose_++;
    output_error_file_ << ErrorMsgBuilder::BuildErrorMsg("class name needed before " +
        CurrentTokenToString());
  }

  match(TokenType::L_BRACE);
  match(TokenType::PUBLIC);
  match(TokenType::STATIC);
  match(TokenType::VOID);
  match(TokenType::MAIN);
  match(TokenType::L_PARENTHESES);
  match(TokenType::STRING);
  match(TokenType::L_PARENTHESIS);
  match(TokenType::R_PARENTHESIS);

  if (token_type_list_.at(current_token_pose_) == TokenType::IDENTIFIER) {
    SyntaxTreeNode main_args_name;
    main_args_name.SetNodeType(NodeType::MAIN_ARGS_NAME);
    main_args_name.SetValue("Args");
    main_class_node.AddChildNode(main_args_name);
    current_token_pose_++;
  } else {
    current_token_pose_++;
    output_error_file_ << ErrorMsgBuilder::BuildErrorMsg("Main Args name needed before " +
        CurrentTokenToString());
  }

  match(TokenType::R_PARENTHESES);
  match(TokenType::L_BRACE);

  SyntaxTreeNode statement_node = Statement();
  main_class_node.AddChildNode(statement_node);

  match(TokenType::R_BRACE);
  match(TokenType::R_BRACE);

  return main_class_node;
}

SyntaxTreeNode Parser::ClassDeclaration() {
  SyntaxTreeNode class_decl_node;
  class_decl_node.SetNodeType(NodeType::DECLARATION);
  class_decl_node.SetDeclaration(Declaration::CLASS_DECLARATION);

  match(TokenType::CLASS);

  if (token_type_list_.at(current_token_pose_) == TokenType::IDENTIFIER) {
    SyntaxTreeNode class_name_node;
    class_name_node.SetNodeType(NodeType::CLASS_NAME);
    class_name_node.SetValue(MJavaUtils::TokenTypeToString(token_type_list_.at(current_token_pose_)));
    class_decl_node.AddChildNode(class_name_node);
    current_token_pose_++;
  } else {
    current_token_pose_++;
    output_error_file_ << ErrorMsgBuilder::BuildErrorMsg("class name needed before " +
        CurrentTokenToString());
  }

  if (token_type_list_.at(current_token_pose_) == TokenType::EXTENDS) {
    current_token_pose_++;
    if (token_type_list_.at(current_token_pose_) == TokenType::IDENTIFIER) {
      SyntaxTreeNode extends_class_name_node;
      extends_class_name_node.SetNodeType(NodeType::CLASS_NAME);
      extends_class_name_node.SetValue(MJavaUtils::TokenTypeToString(token_type_list_.at(current_token_pose_)));
      class_decl_node.AddChildNode(extends_class_name_node);
      current_token_pose_++;
    } else {
      current_token_pose_++;
      output_error_file_ << ErrorMsgBuilder::BuildErrorMsg("Extends class name needed before " +
          CurrentTokenToString());
    }
  }

  match(TokenType::L_BRACE);

  while (!(token_type_list_.at(current_token_pose_) == TokenType::PUBLIC) ||
      (token_type_list_.at(current_token_pose_) == TokenType::R_BRACE)) {
    SyntaxTreeNode var_decl_node = VarDeclaration();
    class_decl_node.AddChildNode(var_decl_node);
    current_token_pose_++;
  }

  while (token_type_list_.at(current_token_pose_) == TokenType::PUBLIC) {
    SyntaxTreeNode method_decl_node = MethodDeclaration();
    class_decl_node.AddChildNode(method_decl_node);
    current_token_pose_++;
  }

  match(TokenType::R_BRACE);

  return class_decl_node;
}

SyntaxTreeNode Parser::VarDeclaration() {
  SyntaxTreeNode var_decl_node;
  var_decl_node.SetNodeType(NodeType::DECLARATION);
  var_decl_node.SetDeclaration(Declaration::VAR_DECLARATION);

  SyntaxTreeNode type_node = Type();
  var_decl_node.AddChildNode(type_node);
  current_token_pose_++;

  if (token_type_list_.at(current_token_pose_) == TokenType::IDENTIFIER) {
    SyntaxTreeNode var_name;
    var_name.SetNodeType(NodeType::VAR_NAME);
    var_name.SetValue("VarName");
    current_token_pose_++;
  } else {
    current_token_pose_++;
    output_error_file_ << ErrorMsgBuilder::BuildErrorMsg("Identifier needed at " +
        CurrentTokenToString());
  }

  return var_decl_node;
}

SyntaxTreeNode Parser::MethodDeclaration() {
  SyntaxTreeNode method_decl_node;
  method_decl_node.SetNodeType(NodeType::DECLARATION);
  method_decl_node.SetDeclaration(Declaration::METHOD_DECLARATION);

  match(TokenType::PUBLIC);

  SyntaxTreeNode type_node = Type();
  method_decl_node.AddChildNode(type_node);
  current_token_pose_++;

  if (token_type_list_.at(current_token_pose_) == TokenType::IDENTIFIER) {
    SyntaxTreeNode var_name_node;
    var_name_node.SetNodeType(NodeType::VAR_NAME);
    var_name_node.SetValue("VarName");
    method_decl_node.AddChildNode(var_name_node);
    current_token_pose_++;
  } else {
    current_token_pose_++;
    output_error_file_ << ErrorMsgBuilder::BuildErrorMsg("Variable name needed at " +
        CurrentTokenToString());
  }

  match(TokenType::L_PARENTHESES);
  if (!(token_type_list_.at(current_token_pose_) == TokenType::R_PARENTHESES)) {
    method_decl_node.AddChildNode(Type());
    current_token_pose_++;

    if (token_type_list_.at(current_token_pose_) == TokenType::IDENTIFIER) {
      SyntaxTreeNode var_name_node;
      var_name_node.SetNodeType(NodeType::VAR_NAME);
      var_name_node.SetValue("VarName");
      method_decl_node.AddChildNode(var_name_node);
      current_token_pose_++;
    } else {
      output_error_file_ << ErrorMsgBuilder::BuildErrorMsg("Variable name needed at " +
          CurrentTokenToString());
      current_token_pose_++;
    }

    while (token_type_list_.at(current_token_pose_) == TokenType::COMMA) {
      current_token_pose_++;
      method_decl_node.AddChildNode(Type());
      current_token_pose_++;

      if (token_type_list_.at(current_token_pose_) == TokenType::IDENTIFIER) {
        SyntaxTreeNode var_name_node;
        var_name_node.SetNodeType(NodeType::VAR_NAME);
        var_name_node.SetValue("VarName");
        method_decl_node.AddChildNode(var_name_node);
        current_token_pose_++;
      } else {
        output_error_file_ << ErrorMsgBuilder::BuildErrorMsg("Variable name needed at " +
            CurrentTokenToString());
        current_token_pose_++;
      }
    }
  }

  match(TokenType::R_PARENTHESES);
  match(TokenType::L_BRACE);

  auto tmp_current_token_type = token_type_list_.at(current_token_pose_);
  while (tmp_current_token_type == TokenType::INT ||
      tmp_current_token_type == TokenType::BOOLEAN ||
      (tmp_current_token_type == TokenType::IDENTIFIER &&
          !(token_type_list_.at(current_token_pose_ + 1) == TokenType::ASSIGNMENT) &&
          !(token_type_list_.at(current_token_pose_ + 1) == TokenType::L_PARENTHESIS))
      ) {
    method_decl_node.AddChildNode(VarDeclaration());
  }

  while (token_type_list_.at(current_token_pose_) != TokenType::RETURN) {
    SyntaxTreeNode statement_child_node = Statement();
    if (!statement_child_node.IsNull()) {
      method_decl_node.AddChildNode(statement_child_node);
    }
  }

  match(TokenType::RETURN);
  method_decl_node.AddChildNode(Expression());
  match(TokenType::SEMICOLON);
  match(TokenType::R_BRACE);

  return method_decl_node;
}

SyntaxTreeNode Parser::Type() {
  SyntaxTreeNode type_node;
  type_node.SetNodeType(NodeType::TYPE);

  if (token_type_list_.at(current_token_pose_) == TokenType::INT) {
    current_token_pose_++;
    if (token_type_list_.at(current_token_pose_) == TokenType::L_PARENTHESIS) {
      match(TokenType::L_PARENTHESIS);
      match(TokenType::R_PARENTHESIS);
      type_node.SetVarType(VarType::INT_ARRAY);
    } else {
      type_node.SetVarType(VarType::INT);
    }
  } else if (token_type_list_.at(current_token_pose_) == TokenType::BOOLEAN) {
    current_token_pose_++;
    type_node.SetVarType(VarType::BOOLEAN);
  } else if (token_type_list_.at(current_token_pose_) == TokenType::IDENTIFIER) {
    type_node.SetIdentifierType(true);
    type_node.SetValue("Identifier");
    current_token_pose_++;
  } else {
    output_error_file_ << ErrorMsgBuilder::BuildErrorMsg("Error type " +
        CurrentTokenToString());
    current_token_pose_++;
  }

  return type_node;
}

SyntaxTreeNode Parser::Statement() {
  SyntaxTreeNode statement_node;
  switch (token_type_list_.at(current_token_pose_)) {
    case TokenType::L_BRACE: {
      statement_node = StatementSeries();
      match(TokenType::R_BRACE);
      return statement_node;
    }
    case TokenType::WHILE: {
      statement_node = WhileStatement();
      return statement_node;
    }
    case TokenType::IF: {
      statement_node = IfStatement();
      return statement_node;
    }
    case TokenType::SYSTEM_OUT_PRINTLN: {
      statement_node = PrintStatement();
      return statement_node;
    }
    case TokenType::IDENTIFIER: {
      statement_node = AssignStatement();
      return statement_node;
    }
    default: {
      output_error_file_ << ErrorMsgBuilder::BuildErrorMsg("Invalid token " +
          CurrentTokenToString());
      current_token_pose_++;
      if (token_type_list_.at(current_token_pose_) == TokenType::SEMICOLON) {
        current_token_pose_++;
      }
      statement_node.SetIsNull(true);
      return statement_node;
    }
  }
}

SyntaxTreeNode Parser::StatementSeries() {
  SyntaxTreeNode statement_node;
  statement_node.SetNodeType(NodeType::STATEMENT);
  statement_node.SetStatement(Statement::SERIES_STATEMENT);

  match(TokenType::L_BRACE);
  while (token_type_list_.at(current_token_pose_) != TokenType::R_BRACE) {
    auto child_node = Statement();
    if (!child_node.IsNull()) {
      statement_node.AddChildNode(child_node);
    }
  }

  return statement_node;
}

SyntaxTreeNode Parser::IfStatement() {
  SyntaxTreeNode statement_node;
  statement_node.SetNodeType(NodeType::STATEMENT);
  statement_node.SetStatement(Statement::IF_STATEMENT);

  match(TokenType::IF);
  match(TokenType::L_PARENTHESES);

  auto exp_node = Expression();
  if (!exp_node.IsNull()) {
    statement_node.AddChildNode(exp_node);
  }

  match(TokenType::R_PARENTHESES);

  auto state_child_node = Statement();
  if (!state_child_node.IsNull()) {
    statement_node.AddChildNode(state_child_node);
  }

  match(TokenType::ELSE);

  auto state_child2_node = Statement();
  if (!state_child2_node.IsNull()) {
    statement_node.AddChildNode(state_child2_node);
  }

  return statement_node;
}

SyntaxTreeNode Parser::WhileStatement() {
  SyntaxTreeNode statement_node;
  statement_node.SetNodeType(NodeType::STATEMENT);
  statement_node.SetStatement(Statement::WHILE_STATEMENT);

  match(TokenType::WHILE);
  match(TokenType::L_PARENTHESES);

  auto exp_node = Expression();
  if (!exp_node.IsNull()) {
    statement_node.AddChildNode(exp_node);
  }

  match(TokenType::R_PARENTHESES);

  auto state_child_node = Statement();
  if (!state_child_node.IsNull()) {
    statement_node.AddChildNode(state_child_node);
  }

  return statement_node;
}

SyntaxTreeNode Parser::PrintStatement() {
  SyntaxTreeNode statement_node;
  statement_node.SetNodeType(NodeType::STATEMENT);
  statement_node.SetStatement(Statement::PRINT_STATEMENT);

  match(TokenType::SYSTEM_OUT_PRINTLN);
  match(TokenType::L_PARENTHESES);

  auto exp_node = Expression();
  if (!exp_node.IsNull()) {
    statement_node.AddChildNode(exp_node);
  }

  match(TokenType::R_PARENTHESES);
  match(TokenType::SEMICOLON);

  return statement_node;
}

SyntaxTreeNode Parser::AssignStatement() {
  current_token_pose_++;
  switch (token_type_list_.at(current_token_pose_)) {
    case TokenType::ASSIGNMENT: {
      current_token_pose_--;
      return VarAssignStatement();
    }
    case TokenType::L_PARENTHESIS: {
      current_token_pose_--;
      return ArrayAssignStatement();
    }
    default: {
      output_error_file_ << ErrorMsgBuilder::BuildErrorMsg("Invalid statement " +
          CurrentTokenToString());
      current_token_pose_++;
      if (token_type_list_.at(current_token_pose_) == TokenType::SEMICOLON) {
        current_token_pose_++;
      }
      SyntaxTreeNode assign_node;
      assign_node.SetIsNull(true);
      return assign_node;
    }
  }
}

SyntaxTreeNode Parser::VarAssignStatement() {
  SyntaxTreeNode var_assign_node;
  var_assign_node.SetNodeType(NodeType::STATEMENT);
  var_assign_node.SetStatement(Statement::VAR_ASSIGN_STATEMENT);

  if (token_type_list_.at(current_token_pose_) == TokenType::IDENTIFIER) {
    SyntaxTreeNode var_name;
    var_name.SetNodeType(NodeType::VAR_NAME);
    var_name.SetValue("VarName ");
    var_assign_node.AddChildNode(var_name);
    current_token_pose_++;
  } else {
    output_error_file_ << ErrorMsgBuilder::BuildErrorMsg("Identifier needed at " +
        CurrentTokenToString());
    current_token_pose_++;
  }

  match(TokenType::ASSIGNMENT);

  auto exp_node = Expression();
  if (!exp_node.IsNull()) {
    var_assign_node.AddChildNode(exp_node);
  }

  match(TokenType::SEMICOLON);
  return var_assign_node;
}

SyntaxTreeNode Parser::ArrayAssignStatement() {
  SyntaxTreeNode array_assign_node;
  array_assign_node.SetNodeType(NodeType::STATEMENT);
  array_assign_node.SetStatement(Statement::ARRAY_ASSIGN_STATEMENT);

  if (token_type_list_.at(current_token_pose_) == TokenType::IDENTIFIER) {
    SyntaxTreeNode var_name;
    var_name.SetNodeType(NodeType::VAR_NAME);
    var_name.SetValue("VarName ");
    array_assign_node.AddChildNode(var_name);
    current_token_pose_++;
  } else {
    output_error_file_ << ErrorMsgBuilder::BuildErrorMsg("Identifier needed at " +
        CurrentTokenToString());
    current_token_pose_++;
  }

  match(TokenType::L_PARENTHESIS);

  auto exp_node = Expression();
  if (!exp_node.IsNull()) {
    array_assign_node.AddChildNode(exp_node);
  }

  match(TokenType::R_PARENTHESIS);
  match(TokenType::ASSIGNMENT);

  array_assign_node.AddChildNode(Expression());

  match(TokenType::SEMICOLON);
  return array_assign_node;
}

SyntaxTreeNode Parser::Expression() {
  SyntaxTreeNode exp_node;
  switch (token_type_list_.at(current_token_pose_)) {
    case TokenType::INT: {
      exp_node = IntExpression();
      return exp_node;
    }
    case TokenType::TRUE: {
      exp_node = TrueExpression();
      return exp_node;
    }
    case TokenType::FALSE: {
      exp_node = FalseExpression();
      return exp_node;
    }
    case TokenType::IDENTIFIER: {
      exp_node = IdentifierExpression();
      return exp_node;
    }
    case TokenType::THIS: {
      exp_node = ThisExpression();
      return exp_node;
    }
    case TokenType::NEW: {
      current_token_pose_++;
      if (token_type_list_.at(current_token_pose_) == TokenType::INT) {
        exp_node = NewArrayExpression();
        return exp_node;
      } else if (token_type_list_.at(current_token_pose_) == TokenType::IDENTIFIER) {
        exp_node = NewExpression();
        return exp_node;
      } else {
        output_error_file_ << ErrorMsgBuilder::BuildErrorMsg("Unexpected token " +
            CurrentTokenToString());
        current_token_pose_++;
        exp_node.SetIsNull(true);
        return exp_node;
      }
    }
    case TokenType::UN : {
      exp_node = NotExpression();
      return exp_node;
    }
    case TokenType::L_PARENTHESES: {
      exp_node = BraceExpression();
      return exp_node;
    }
    default: {
      output_error_file_ << ErrorMsgBuilder::BuildErrorMsg("Unexpected token " +
          CurrentTokenToString());
      current_token_pose_++;
      if (token_type_list_.at(current_token_pose_) == TokenType::SEMICOLON) {
        current_token_pose_++;
      }
      exp_node.SetIsNull(true);
      return exp_node;
    }
  }
}

SyntaxTreeNode Parser::IntExpression() {
  SyntaxTreeNode int_exp_node;
  int_exp_node.SetNodeType(NodeType::EXPRESSION);
  int_exp_node.SetExpression(Expression::INT_EXPRESSION);

  if (token_type_list_.at(current_token_pose_) == TokenType::INT) {
    SyntaxTreeNode digit_name;
    digit_name.SetNodeType(NodeType::NUM);
    digit_name.SetValue("Digit");
    int_exp_node.AddChildNode(digit_name);
    current_token_pose_++;
  } else {
    output_error_file_ << ErrorMsgBuilder::BuildErrorMsg("Identifier needed at " +
        CurrentTokenToString());
    current_token_pose_++;
  }

  auto exp_node = SubExpStatament();
  if (!exp_node.IsNull()) {
    int_exp_node.AddChildNode(exp_node);
  }

  return int_exp_node;
}

SyntaxTreeNode Parser::TrueExpression() {
  SyntaxTreeNode true_exp_node;
  true_exp_node.SetNodeType(NodeType::EXPRESSION);
  true_exp_node.SetExpression(Expression::TRUE_EXPRESSION);

  match(TokenType::TRUE);

  auto exp_node = SubExpStatament();
  if (!exp_node.IsNull()) {
    true_exp_node.AddChildNode(exp_node);
  }
  return true_exp_node;
}

SyntaxTreeNode Parser::FalseExpression() {
  SyntaxTreeNode false_exp_node;
  false_exp_node.SetNodeType(NodeType::EXPRESSION);
  false_exp_node.SetExpression(Expression::FALSE_EXPRESSION);

  match(TokenType::FALSE);

  auto exp_node = SubExpStatament();
  if (!exp_node.IsNull()) {
    false_exp_node.AddChildNode(exp_node);
  }
  return false_exp_node;
}

SyntaxTreeNode Parser::IdentifierExpression() {
  SyntaxTreeNode identifier_exp_node;
  identifier_exp_node.SetNodeType(NodeType::EXPRESSION);
  identifier_exp_node.SetExpression(Expression::IDENTIFIER_EXPRESSION);

  if (token_type_list_.at(current_token_pose_) == TokenType::IDENTIFIER) {
    SyntaxTreeNode identifier_name;
    identifier_name.SetNodeType(NodeType::EXPRESSION_IDENTIFIER);
    identifier_name.SetValue("Identifier");
    identifier_exp_node.AddChildNode(identifier_name);
    current_token_pose_++;
  } else {
    output_error_file_ << ErrorMsgBuilder::BuildErrorMsg("Identifier needed at " +
        CurrentTokenToString());
    current_token_pose_++;
  }

  auto exp_node = SubExpStatament();
  if (!exp_node.IsNull()) {
    identifier_exp_node.AddChildNode(exp_node);
  }

  return identifier_exp_node;
}

SyntaxTreeNode Parser::ThisExpression() {
  SyntaxTreeNode this_exp_node;
  this_exp_node.SetNodeType(NodeType::EXPRESSION);
  this_exp_node.SetExpression(Expression::THIS_EXPRESSION);

  match(TokenType::THIS);

  auto exp_node = SubExpStatament();
  if (!exp_node.IsNull()) {
    this_exp_node.AddChildNode(exp_node);
  }
  return this_exp_node;
}

SyntaxTreeNode Parser::NewArrayExpression() {
  SyntaxTreeNode new_array_exp_node;
  new_array_exp_node.SetNodeType(NodeType::EXPRESSION);
  new_array_exp_node.SetExpression(Expression::NEW_ARRAY_EXPRESSION);

  match(TokenType::INT);
  match(TokenType::L_PARENTHESIS);

  auto exp_node = Expression();
  if (!exp_node.IsNull()) {
    new_array_exp_node.AddChildNode(exp_node);
  }

  auto sub_exp_node = SubExpStatament();
  if (!sub_exp_node.IsNull()) {
    new_array_exp_node.AddChildNode(sub_exp_node);
  }

  return new_array_exp_node;
}

SyntaxTreeNode Parser::NewExpression() {
  SyntaxTreeNode new_exp_node;
  new_exp_node.SetNodeType(NodeType::EXPRESSION);
  new_exp_node.SetExpression(Expression::NEW_EXPRESSION);

  if (token_type_list_.at(current_token_pose_) == TokenType::IDENTIFIER) {
    SyntaxTreeNode identifier_name;
    identifier_name.SetNodeType(NodeType::EXPRESSION_IDENTIFIER);
    identifier_name.SetValue("Identifier");
    new_exp_node.AddChildNode(identifier_name);
    current_token_pose_++;
  } else {
    output_error_file_ << ErrorMsgBuilder::BuildErrorMsg("Identifier needed at " +
        CurrentTokenToString());
    current_token_pose_++;
  }

  match(TokenType::L_PARENTHESES);
  match(TokenType::R_PARENTHESES);

  auto exp_node = SubExpStatament();
  if (!exp_node.IsNull()) {
    new_exp_node.AddChildNode(exp_node);
  }

  return new_exp_node;
}

SyntaxTreeNode Parser::NotExpression() {
  SyntaxTreeNode not_exp_node;
  not_exp_node.SetNodeType(NodeType::EXPRESSION);
  not_exp_node.SetExpression(Expression::NOT_EXPRESSION);

  match(TokenType::UN);

  auto exp_node = Expression();
  if (!exp_node.IsNull()) {
    not_exp_node.AddChildNode(exp_node);
  }

  auto sub_exp_node = SubExpStatament();
  if (!sub_exp_node.IsNull()) {
    not_exp_node.AddChildNode(sub_exp_node);
  }

  return not_exp_node;
}

SyntaxTreeNode Parser::BraceExpression() {
  SyntaxTreeNode brace_exp_node;
  brace_exp_node.SetNodeType(NodeType::EXPRESSION);
  brace_exp_node.SetExpression(Expression::BRACE_EXPRESSION);

  match(TokenType::L_PARENTHESES);

  auto exp_node = Expression();
  if (!exp_node.IsNull()) {
    brace_exp_node.AddChildNode(exp_node);
  }

  match(TokenType::R_PARENTHESES);

  auto sub_exp_node = SubExpStatament();
  if (!sub_exp_node.IsNull()) {
    brace_exp_node.AddChildNode(sub_exp_node);
  }

  return brace_exp_node;
}

SyntaxTreeNode Parser::SubExpStatament() {
  SyntaxTreeNode sub_exp_node;
  switch (token_type_list_.at(current_token_pose_)) {
    case TokenType::AND: {
      sub_exp_node = OpSubExp();
      return sub_exp_node;
    }
    case TokenType::SUB: {
      sub_exp_node = OpSubExp();
      return sub_exp_node;
    }
    case TokenType::ADD: {
      sub_exp_node = OpSubExp();
      return sub_exp_node;
    }
    case TokenType::LESS_THAN: {
      sub_exp_node = OpSubExp();
      return sub_exp_node;
    }
    case TokenType::MULTI: {
      sub_exp_node = OpSubExp();
      return sub_exp_node;
    }
    case TokenType::L_PARENTHESIS: {
      sub_exp_node = ExpSubExp();
      return sub_exp_node;
    }
    case TokenType::POINT: {
      current_token_pose_++;
      if (token_type_list_.at(current_token_pose_) == TokenType::LENGTH) {
        sub_exp_node = LengthSubExp();
        return sub_exp_node;
      } else if (token_type_list_.at(current_token_pose_) == TokenType::IDENTIFIER) {
        sub_exp_node = MethodSubExp();
        return sub_exp_node;
      } else {
        output_error_file_ << ErrorMsgBuilder::BuildErrorMsg("Unexpected token " +
            CurrentTokenToString());
        current_token_pose_++;
        sub_exp_node.SetIsNull(true);
        return sub_exp_node;
      }
    }
    default: {
      sub_exp_node = NullSubExp();
      return sub_exp_node;
    }
  }
}

SyntaxTreeNode Parser::OpSubExp() {
  SyntaxTreeNode op_sub_exp_node;
  op_sub_exp_node.SetNodeType(NodeType::SUB_EXP_EXP);
  op_sub_exp_node.SetSubExpExp(SubExpExp::OP_SUB_EXP);
  op_sub_exp_node.SetValue(MJavaUtils::TokenTypeToString(
      token_type_list_.at(current_token_pose_)));

  current_token_pose_++;

  auto exp_node = Expression();
  if (!exp_node.IsNull()) {
    op_sub_exp_node.AddChildNode(exp_node);
  }

  auto sub_exp_node = SubExpStatament();
  if (!sub_exp_node.IsNull()) {
    op_sub_exp_node.AddChildNode(sub_exp_node);
  }

  return op_sub_exp_node;
}

SyntaxTreeNode Parser::ExpSubExp() {
  SyntaxTreeNode exp_sub_exp_node;
  exp_sub_exp_node.SetNodeType(NodeType::SUB_EXP_EXP);
  exp_sub_exp_node.SetSubExpExp(SubExpExp::EXP_SUB_EXP);

  match(TokenType::L_PARENTHESIS);

  auto exp_node = Expression();
  if (!exp_node.IsNull()) {
    exp_sub_exp_node.AddChildNode(exp_node);
  }

  match(TokenType::R_PARENTHESIS);

  auto sub_exp_node = SubExpStatament();
  if (!sub_exp_node.IsNull()) {
    exp_sub_exp_node.AddChildNode(sub_exp_node);
  }

  return exp_sub_exp_node;
}

SyntaxTreeNode Parser::LengthSubExp() {
  SyntaxTreeNode exp_sub_exp_node;
  exp_sub_exp_node.SetNodeType(NodeType::SUB_EXP_EXP);
  exp_sub_exp_node.SetSubExpExp(SubExpExp::LENGTH_SUB_EXP);

  match(TokenType::LENGTH);

  auto sub_exp_node = SubExpStatament();
  if (!sub_exp_node.IsNull()) {
    exp_sub_exp_node.AddChildNode(sub_exp_node);
  }

  return exp_sub_exp_node;
}

SyntaxTreeNode Parser::MethodSubExp() {
  SyntaxTreeNode method_sub_exp_node;
  method_sub_exp_node.SetNodeType(NodeType::SUB_EXP_EXP);
  method_sub_exp_node.SetSubExpExp(SubExpExp::METHOD_SUB_EXP);

  if (token_type_list_.at(current_token_pose_) == TokenType::IDENTIFIER) {
    SyntaxTreeNode identifier_name;
    identifier_name.SetNodeType(NodeType::METHOD_NAME);
    identifier_name.SetValue("Identifier");
    method_sub_exp_node.AddChildNode(identifier_name);
    current_token_pose_++;
  } else {
    output_error_file_ << ErrorMsgBuilder::BuildErrorMsg("Method needed at " +
        CurrentTokenToString());
    current_token_pose_++;
  }

  match(TokenType::L_PARENTHESES);

  if (token_type_list_.at(current_token_pose_) != TokenType::R_PARENTHESES) {
    auto exp_child_node = Expression();
    if (!exp_child_node.IsNull()) {
      method_sub_exp_node.AddChildNode(exp_child_node);
    }
    while (token_type_list_.at(current_token_pose_) != TokenType::COMMA) {
      current_token_pose_++;
      auto exp_child2_node = Expression();
      if (!exp_child2_node.IsNull()) {
        method_sub_exp_node.AddChildNode(exp_child2_node);
      }
    }
  }

  match(TokenType::R_PARENTHESES);

  auto exp_node = SubExpStatament();
  if (!exp_node.IsNull()) {
    method_sub_exp_node.AddChildNode(exp_node);
  }

  return method_sub_exp_node;
}

SyntaxTreeNode Parser::NullSubExp() {
  SyntaxTreeNode null_node;
  null_node.SetNodeType(NodeType::SUB_EXP_EXP);
  null_node.SetSubExpExp(SubExpExp::NULL_SUB_EXP);

  return null_node;
}

std::string Parser::CurrentTokenToString() {
  return MJavaUtils::TokenTypeToString(token_type_list_.at(current_token_pose_));
}
