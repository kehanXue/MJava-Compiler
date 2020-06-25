//
// Created by kehan on 2020/4/16.
//

#ifndef SCANNER__SCANNER_H_
#define SCANNER__SCANNER_H_

#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

#include "utils/mjava_utils.h"
#include "utils/error_msg_builder.h"
#include "scanner/dfa_state.h"
#include "utils/token_type.h"

class Scanner {
 public:
  Scanner();
  virtual ~Scanner();
  std::vector<TokenType> Run(const std::string &input_file_name,
           const std::string &output_token_file_name);

 private:
  void ParseFile(std::vector<TokenType> &token_type_list);
  void ParseLine(const std::string &each_line,
      int line_number,
      std::vector<TokenType> &token_type_list);

  std::ifstream input_file_;
  std::string input_file_name_;
  std::ofstream output_token_file_;
  std::ofstream output_error_file_;

  DFAState current_dfa_state_;
  std::shared_ptr<MJavaUtils> p_mjava_utils_;
  std::string current_word_;
  char current_double_char_op_first_;
  // std::string error_msg_;
};

#endif //SCANNER__SCANNER_H_
