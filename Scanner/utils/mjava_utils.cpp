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


