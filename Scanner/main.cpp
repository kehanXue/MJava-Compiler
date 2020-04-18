#include "scanner/scanner.h"

int main(int argc, char **argv) {
  Scanner scanner;
  scanner.Run("专用符号/test6.txt", "专用符号/test6_token");
  scanner.Run("专用符号/test7.txt", "专用符号/test7_token");
  scanner.Run("关键字/test3.txt", "关键字/test3_token");
  scanner.Run("关键字/test4.txt", "关键字/test4_token");
  scanner.Run("整数/test5.txt", "整数/test5_token");
  scanner.Run("标识符/test1.txt", "标识符/test1_token");
  scanner.Run("标识符/test2.txt", "标识符/test2_token");
  scanner.Run("自定义测试方案/test8.txt", "自定义测试方案/test8_token");
  return 0;
}
