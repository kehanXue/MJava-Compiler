//
// Created by kehan on 2020/4/17.
//

#include "mjava_utils.h"

MJavaUtils::MJavaUtils() {
  /*
   * Keywords:
   * class, public, static, void, main, String,
   * extends, return, int, boolean, if, else,
   * while, System.out.println , length, true,
   * false, this, new
   */
  umap_keywords_.insert({"class", "CLASS"});
  umap_keywords_.insert({"public", "PUBLIC"});
  umap_keywords_.insert({"static", "STATIC"});
  umap_keywords_.insert({"void", "VOID"});
  umap_keywords_.insert({"main", "MAIN"});
  umap_keywords_.insert({"String", "STRING"});
  umap_keywords_.insert({"extends", "EXTENDS"});
  umap_keywords_.insert({"return", "RETURN"});
  umap_keywords_.insert({"int", "INT"});
  umap_keywords_.insert({"boolean", "BOOLEAN"});
  umap_keywords_.insert({"if", "IF"});
  umap_keywords_.insert({"else", "ELSE"});
  umap_keywords_.insert({"while", "WHILE"});
  umap_keywords_.insert({"System.out.println", "SYSTEM.OUT.PRINTLN"});
  umap_keywords_.insert({"length", "LENGTH"});
  umap_keywords_.insert({"true", "TRUE"});
  umap_keywords_.insert({"false", "FALSE"});
  umap_keywords_.insert({"this", "THIS"});
  umap_keywords_.insert({"new", "NEW"});

  /*
   * Single char operators:
   * [ ] ( ) { } , ; = && < + - * . !
   */
  umap_single_char_operators_.insert({'[', "L_PARENTHESIS"});
  umap_single_char_operators_.insert({']', "R_PARENTHESIS"});
  umap_single_char_operators_.insert({'(', "L_PARENTHESES"});
  umap_single_char_operators_.insert({')', "R_PARENTHESES"});
  umap_single_char_operators_.insert({'{', "L_BRACE"});
  umap_single_char_operators_.insert({'}', "R_BRACE"});
  umap_single_char_operators_.insert({',', "COMMA"});
  umap_single_char_operators_.insert({';', "SEMICOLON"});
  umap_single_char_operators_.insert({'=', "ASSIGNMENT"});
  umap_single_char_operators_.insert({'<', "LESS_THAN"});
  umap_single_char_operators_.insert({'+', "ADD"});
  umap_single_char_operators_.insert({'-', "SUB"});
  umap_single_char_operators_.insert({'*', "MULTI"});
  umap_single_char_operators_.insert({'.', "POINT"});
  umap_single_char_operators_.insert({'!', "UN"});

  /*
   * Double char operators:
   * &&
   */
  umap_double_char_operators_.insert({"&&", "AND"});

}

MJavaUtils::~MJavaUtils() = default;

bool MJavaUtils::IsBlankChar(const char &input_char) {
  return input_char == '\t' ||
      input_char == '\r' ||
      input_char == '\n' ||
      input_char == ' ';
}

bool MJavaUtils::IsKeyWords(const std::string &input_string, std::string &token) {
  /*
   * Found key words
   */
  if (umap_keywords_.find(input_string) != umap_keywords_.end()) {
    token = umap_keywords_.at(input_string);
    return true;
  }
  return false;
}

bool MJavaUtils::IsLetterOrDigit(const char &input_char) {
  return IsLetter(input_char) || IsDigit(input_char);
}

bool MJavaUtils::IsDigit(const char &input_char) {
  return input_char >= '0' && input_char <= '9';
}

bool MJavaUtils::IsLetter(const char &input_char) {
  return (input_char >= 'a' && input_char <= 'z') ||
      (input_char >= 'A' && input_char <= 'Z');
}

bool MJavaUtils::IsUnderLine(const char &input_char) {
  return input_char == '_';
}

bool MJavaUtils::IsSingleCharOperator(const char &input_char, std::string &token) {
  /*
   * Found unary operator
   */
  if (umap_single_char_operators_.find(input_char) != umap_single_char_operators_.end()) {
    token = umap_single_char_operators_.at(input_char);
    return true;
  }
  return false;
}

bool MJavaUtils::IsDoubleCharOperatorFirst(const char &input_char) {
  for (const auto &double_char_operator : umap_double_char_operators_) {
    if (double_char_operator.first.size() == 2 &&
        double_char_operator.first.at(0) == input_char) {
      return true;
    }
  }
  return false;
}

bool MJavaUtils::IsDoubleCharOperatorSecond(const char &input_char,
                                            const char &first_char,
                                            std::string &token) {
  std::string double_char_operator{first_char, input_char};
  if (umap_double_char_operators_.find(double_char_operator) != umap_double_char_operators_.end()) {
    token = umap_double_char_operators_.at(double_char_operator);
    return true;
  }
  return false;
}

bool MJavaUtils::BeginWithSystemOutPrintln(const std::string &each_line, const size_t &begin_pose) {
  if (begin_pose != each_line.find("System.out.println", begin_pose)) {
    return false;
  }
  if (begin_pose + std::string("System.out.println").length() >= each_line.length()) {
    return false;
  }
  auto following_char = each_line.at(begin_pose + std::string("System.out.println").length());
  return !(IsLetter(following_char) || IsDigit(following_char) || IsUnderLine(following_char));
}

TokenType MJavaUtils::StringToTokenType(const std::string &token_type) {
  /*
   * String to TokenTypes
   */
  if (token_type == "CLASS") {
    return TokenType::CLASS;
  } else if (token_type == "PUBLIC") {
    return TokenType::PUBLIC;
  } else if (token_type == "STATIC") {
    return TokenType::STATIC;
  } else if (token_type == "VOID") {
    return TokenType::VOID;
  } else if (token_type == "MAIN") {
    return TokenType::MAIN;
  } else if (token_type == "STRING") {
    return TokenType::STRING;
  } else if (token_type == "EXTENDS") {
    return TokenType::EXTENDS;
  } else if (token_type == "RETURN") {
    return TokenType::RETURN;
  } else if (token_type == "INT") {
    return TokenType::INT;
  } else if (token_type == "BOOLEAN") {
    return TokenType::BOOLEAN;
  } else if (token_type == "IF") {
    return TokenType::IF;
  } else if (token_type == "ELSE") {
    return TokenType::ELSE;
  } else if (token_type == "WHILE") {
    return TokenType::WHILE;
  } else if (token_type == "SYSTEM_OUT_PRINTLN") {
    return TokenType::SYSTEM_OUT_PRINTLN;
  } else if (token_type == "LENGTH") {
    return TokenType::LENGTH;
  } else if (token_type == "TRUE") {
    return TokenType::TRUE;
  } else if (token_type == "FALSE") {
    return TokenType::FALSE;
  } else if (token_type == "THIS") {
    return TokenType::THIS;
  } else if (token_type == "NEW") {
    return TokenType::NEW;
  } else if (token_type == "IDENTIFIER") {
    return TokenType::IDENTIFIER;
  } else if (token_type == "DIGIT") {
    return TokenType::DIGIT;
  } else if (token_type == "L_PARENTHESIS") {
    return TokenType::L_PARENTHESIS;
  } else if (token_type == "R_PARENTHESIS") {
    return TokenType::R_PARENTHESIS;
  } else if (token_type == "L_PARENTHESES") {
    return TokenType::L_PARENTHESES;
  } else if (token_type == "R_PARENTHESES") {
    return TokenType::R_PARENTHESES;
  } else if (token_type == "L_BRACE") {
    return TokenType::L_BRACE;
  } else if (token_type == "R_BRACE") {
    return TokenType::R_BRACE;
  } else if (token_type == "COMMA") {
    return TokenType::COMMA;
  } else if (token_type == "SEMICOLON") {
    return TokenType::SEMICOLON;
  } else if (token_type == "ASSIGNMENT") {
    return TokenType::ASSIGNMENT;
  } else if (token_type == "LESS_THAN") {
    return TokenType::LESS_THAN;
  } else if (token_type == "ADD") {
    return TokenType::ADD;
  } else if (token_type == "SUB") {
    return TokenType::SUB;
  } else if (token_type == "MULTI") {
    return TokenType::MULTI;
  } else if (token_type == "POINT") {
    return TokenType::POINT;
  } else if (token_type == "UN") {
    return TokenType::UN;
  } else if (token_type == "AND") {
    return TokenType::AND;
  }

  return TokenType::ERROR;
}

std::string MJavaUtils::TokenTypeToString(const TokenType &token_type) {
  /*
    * String to TokenTypes
    */
  if (token_type == TokenType::CLASS) {
    return "CLASS";
  } else if (token_type == TokenType::PUBLIC) {
    return "PUBLIC";
  } else if (token_type == TokenType::STATIC) {
    return "STATIC";
  } else if (token_type == TokenType::VOID) {
    return "VOID";
  } else if (token_type == TokenType::MAIN) {
    return "MAIN";
  } else if (token_type == TokenType::STRING) {
    return "STRING";
  } else if (token_type == TokenType::EXTENDS) {
    return "EXTENDS";
  } else if (token_type == TokenType::RETURN) {
    return "RETURN";
  } else if (token_type == TokenType::INT) {
    return "INT";
  } else if (token_type == TokenType::BOOLEAN) {
    return "BOOLEAN";
  } else if (token_type == TokenType::IF) {
    return "IF";
  } else if (token_type == TokenType::ELSE) {
    return "ELSE";
  } else if (token_type == TokenType::WHILE) {
    return "WHILE";
  } else if (token_type == TokenType::SYSTEM_OUT_PRINTLN) {
    return "SYSTEM_OUT_PRINTN";
  } else if (token_type == TokenType::LENGTH) {
    return "LENGTH";
  } else if (token_type == TokenType::TRUE) {
    return "TRUE";
  } else if (token_type == TokenType::FALSE) {
    return "FALSE";
  } else if (token_type == TokenType::THIS) {
    return "THIS";
  } else if (token_type == TokenType::NEW) {
    return "NEW";
  } else if (token_type == TokenType::IDENTIFIER) {
    return "IDENTIFIER";
  } else if (token_type == TokenType::DIGIT) {
    return "DIGIT";
  } else if (token_type == TokenType::L_PARENTHESIS) {
    return "L_PARENTHESIS";
  } else if (token_type == TokenType::R_PARENTHESIS) {
    return "R_PARENTHESIS";
  } else if (token_type == TokenType::L_PARENTHESES) {
    return "L_PARENTHESES";
  } else if (token_type == TokenType::R_PARENTHESES) {
    return "R_PARENTHESES";
  } else if (token_type == TokenType::L_BRACE) {
    return "L_BRACE";
  } else if (token_type == TokenType::R_BRACE) {
    return "R_BRACE";
  } else if (token_type == TokenType::COMMA) {
    return "COMMA";
  } else if (token_type == TokenType::SEMICOLON) {
    return "SEMICOLON";
  } else if (token_type == TokenType::ASSIGNMENT) {
    return "ASSIGNMENT";
  } else if (token_type == TokenType::LESS_THAN) {
    return "LESS_THAN";
  } else if (token_type == TokenType::ADD) {
    return "ADD";
  } else if (token_type == TokenType::SUB) {
    return "SUB";
  } else if (token_type == TokenType::MULTI) {
    return "MULTI";
  } else if (token_type == TokenType::POINT) {
    return "POINT";
  } else if (token_type == TokenType::UN) {
    return "UN";
  } else if (token_type == TokenType::AND) {
    return "AND";
  }

  return "ERROR";
}


