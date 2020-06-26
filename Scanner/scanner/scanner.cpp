//
// Created by kehan on 2020/4/16.
//

#include "scanner.h"

Scanner::Scanner() :
    current_dfa_state_(DFAState::START),
    current_double_char_op_first_('\0') {
  p_mjava_utils_ = std::make_shared<MJavaUtils>();
}

Scanner::~Scanner() = default;

std::vector<TokenType> Scanner::Run(const std::string &input_file_name,
                                    const std::string &output_token_file_name) {
  if (input_file_.is_open()) {
    input_file_.close();
  }
  if (output_token_file_.is_open()) {
    input_file_.close();
  }
  if (output_error_file_.is_open()) {
    input_file_.close();
  }

  std::vector<TokenType> token_type_list;

  try {
    input_file_.open(input_file_name + ".txt");
    input_file_name_ = input_file_name;

    output_token_file_.open(output_token_file_name + ".txt");
    output_error_file_.open(output_token_file_name + "_scanner_error.txt");
  } catch (...) {
    std::cout << "Open file failed!" << std::endl;
    return token_type_list;
  }

  ScanFile(token_type_list);

  input_file_.close();
  output_token_file_.close();
  output_error_file_.close();

  return token_type_list;
}

void Scanner::ScanFile(std::vector<TokenType> &token_type_list) {
  current_dfa_state_ = DFAState::START;

  std::string each_line;
  int line_number = 1;
  while (!input_file_.eof()) {
    std::getline(input_file_, each_line);
    ScanLine(each_line, line_number, token_type_list);
    ++line_number;
  }

  token_type_list.emplace_back(TokenType::EOF_TOKEN);
}

void Scanner::ScanLine(const std::string &each_line,
                       int line_number,
                       std::vector<TokenType> &token_type_list) {
  int char_index = 0;
  bool is_index_forward = false;
  bool last_char_is_blank = true;

  while (char_index < each_line.size()) {
    const char current_char = each_line.at(char_index);

    switch (current_dfa_state_) {
      case DFAState::START: {
        if (p_mjava_utils_->IsBlankChar(current_char)) {
          is_index_forward = true;
          current_dfa_state_ = DFAState::START;
          output_token_file_ << current_char;
          last_char_is_blank = true;

        } else if (p_mjava_utils_->BeginWithSystemOutPrintln(each_line, char_index)) {
          is_index_forward = false;
          current_dfa_state_ = DFAState::START;
          output_token_file_ << "SYSTEM_OUT_PRINTLN";
          token_type_list.emplace_back(MJavaUtils::StringToTokenType("SYSTEM_OUT_PRINTLN"));
          last_char_is_blank = false;
          char_index += std::string("System.out.println").length();

        } else if (p_mjava_utils_->IsLetter(current_char)) {
          is_index_forward = true;
          current_dfa_state_ = DFAState::STRING;
          current_word_.clear();
          current_word_.push_back(current_char);

        } else if (p_mjava_utils_->IsDigit(current_char)) {
          is_index_forward = true;
          current_dfa_state_ = DFAState::DIGIT;

        } else if (p_mjava_utils_->IsDoubleCharOperatorFirst(current_char)) {
          is_index_forward = true;
          current_dfa_state_ = DFAState::FIRST_CHAR_OF_DOUBLE_CHAR_OPERATOR;
          current_double_char_op_first_ = current_char;

        } else {
          std::string token;
          if (p_mjava_utils_->IsSingleCharOperator(current_char, token)) {
            is_index_forward = true;
            current_dfa_state_ = DFAState::START;
            if (!last_char_is_blank) {
              output_token_file_ << " ";
            }
            output_token_file_ << token;
            token_type_list.emplace_back(MJavaUtils::StringToTokenType(token));
            last_char_is_blank = false;

          } else {
            is_index_forward = true;
            current_dfa_state_ = DFAState::START;
            output_error_file_
                << ErrorMsgBuilder::BuildErrorMsg(input_file_name_,
                                                  "incorrect syntax!",
                                                  line_number,
                                                  char_index + 1,
                                                  current_char);
          }
        }
        break;
      }

      case DFAState::STRING: {
        if (p_mjava_utils_->IsLetterOrDigit(current_char)) {
          is_index_forward = true;
          current_dfa_state_ = DFAState::STRING;
          current_word_.push_back(current_char);

        } else if (p_mjava_utils_->IsUnderLine(current_char)) {
          is_index_forward = true;
          current_dfa_state_ = DFAState::UNDERLINE;
          current_word_.push_back(current_char);

        } else {
          is_index_forward = false;
          current_dfa_state_ = DFAState::START;
          std::string token;

          if (!last_char_is_blank) {
            output_token_file_ << " ";
          }
          last_char_is_blank = false;

          if (p_mjava_utils_->IsKeyWords(current_word_, token)) {
            output_token_file_ << token;
            token_type_list.emplace_back(MJavaUtils::StringToTokenType(token));
          } else {
            output_token_file_ << "IDENTIFIER";
            token_type_list.emplace_back(MJavaUtils::StringToTokenType("IDENTIFIER"));
          }
        }
        break;
      }

      case DFAState::DIGIT: {
        if (p_mjava_utils_->IsDigit(current_char)) {
          is_index_forward = true;
          current_dfa_state_ = DFAState::DIGIT;
        } else {
          is_index_forward = false;
          current_dfa_state_ = DFAState::START;

          if (!last_char_is_blank) {
            output_token_file_ << " ";
          }
          last_char_is_blank = false;

          output_token_file_ << "DIGIT";
          token_type_list.emplace_back(MJavaUtils::StringToTokenType("DIGIT"));
        }
        break;
      }

      case DFAState::FIRST_CHAR_OF_DOUBLE_CHAR_OPERATOR: {
        std::string token;
        if (p_mjava_utils_->
            IsDoubleCharOperatorSecond(current_char,
                                       current_double_char_op_first_,
                                       token)) {
          is_index_forward = true;
          current_dfa_state_ = DFAState::START;

          if (!last_char_is_blank) {
            output_token_file_ << " ";
          }
          last_char_is_blank = false;

          output_token_file_ << token;
          token_type_list.emplace_back(MJavaUtils::StringToTokenType(token));

        } else {
          is_index_forward = false;
          current_dfa_state_ = DFAState::START;
          output_error_file_
              << ErrorMsgBuilder::BuildErrorMsg(input_file_name_,
                                                "undefined operator!",
                                                line_number,
                                                char_index + 1,
                                                current_double_char_op_first_);
        }
        break;
      }

      case DFAState::UNDERLINE: {
        if (p_mjava_utils_->IsLetterOrDigit(current_char)) {
          is_index_forward = true;
          current_dfa_state_ = DFAState::STRING;
          current_word_.push_back(current_char);
        } else {
          is_index_forward = false;
          current_dfa_state_ = DFAState::START;
          output_error_file_
              << ErrorMsgBuilder::BuildErrorMsg(input_file_name_,
                                                "before, has incorrect definition syntax!",
                                                line_number,
                                                char_index + 1,
                                                current_char);
        }
        break;
      }
    }

    if (is_index_forward) {
      char_index++;
    }
  }

  output_token_file_ << "\r\n";
}

