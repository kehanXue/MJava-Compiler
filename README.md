# MJava-Compiler

A simple compiler front-end.

代码结构说明：

[Scanner](./Scanner) 是词法分析程序，采用构建的DFA进行识别。

[Parser](./Parser) 是语法分析程序，采用递归下降法进行分析。

Scanner 将扫描后的 token 列表传递给 Parser。

<div align="center">
  <img src="assets/image-20200627010723750.png" alt="image-20200627010723750" style="zoom:50%;" />
</div>
