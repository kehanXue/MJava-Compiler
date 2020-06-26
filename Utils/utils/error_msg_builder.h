//
// Created by kehan on 2020/4/17.
//

#ifndef SCANNER__ERROR_MSG_BUILDER_H_
#define SCANNER__ERROR_MSG_BUILDER_H_

#include <string>

class ErrorMsgBuilder {
 public:
  static std::string BuildErrorMsg(const std::string &file_name,
                                   const std::string &error,
                                   int line_number,
                                   int col_number,
                                   char error_character) {
    return file_name + ":" +
        std::to_string(line_number) + ":" +
        std::to_string(col_number) + " error: \"" +
        error_character + "\", " + error + "\r\n";
  }

  static std::string BuildErrorMsg(const std::string &file_name,
                                   const std::string &error,
                                   int line_number,
                                   int col_number,
                                   const std::string &error_character) {
    return file_name + ":" +
        std::to_string(line_number) + ":" +
        std::to_string(col_number) + " error: \"" +
        error_character + "\", " + error + "\r\n";
  }

  static std::string BuildErrorMsg(const std::string &error) {
    return error + "\r\n";
  }
};

#endif //SCANNER__ERROR_MSG_BUILDER_H_
