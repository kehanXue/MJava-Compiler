//
// Created by kehan on 2020/4/17.
//

#ifndef MJAVA_SCANNER__MJAVA_UTILS_H_
#define MJAVA_SCANNER__MJAVA_UTILS_H_

#include <string>
#include <unordered_map>
#include "token_type.h"

class MJavaUtils {
 public:
  MJavaUtils();
  virtual ~MJavaUtils();
  static bool IsBlankChar(const char &input_char);
  bool IsKeyWords(const std::string &input_string, std::string &token);
  static bool IsLetterOrDigit(const char &input_char);
  static bool IsDigit(const char &input_char);
  static bool IsLetter(const char &input_char);
  static bool IsUnderLine(const char &input_char);
  bool IsSingleCharOperator(const char &input_char, std::string &token);
  bool IsDoubleCharOperatorFirst(const char &input_char);
  bool IsDoubleCharOperatorSecond(const char &input_char, const char &first_char, std::string &token);
  static bool BeginWithSystemOutPrintln(const std::string &each_line, const size_t &begin_pose);

  static TokenType StringToTokenType(const std::string& token_type);
  static std::string TokenTypeToString(const TokenType& token_type);

 private:
  std::unordered_map<std::string, std::string> umap_keywords_;
  std::unordered_map<char, std::string> umap_single_char_operators_;
  std::unordered_map<std::string, std::string> umap_double_char_operators_;
  std::unordered_map<std::string, TokenType> umap_token_types_;
};

#endif //MJAVA_SCANNER__MJAVA_UTILS_H_

