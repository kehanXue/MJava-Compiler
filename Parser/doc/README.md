[TOC]

# MJava 语法规则

- Goal-> MainClass *{* ClassDeclaration *}* EOF
- MainClass-> **"class"** Identifier **"{"** **"public"** **"static"** **"void"** **"main"** **"("** **"String"** **"["** **"]"** Identifier **")"** **"{"** Statement **"}"** **"}"**
- ClassDeclaration-> **"class"** Identifier *[* **"extends"** Identifier *]* **"{"** *{* VarDeclaration *}* *{* MethodDeclaration *}* **"}"**
- VarDeclaration-> Type Identifier **";"**
- MethodDeclaration-> **"public"** Type Identifier **"("** *[* Type Identifier *{* **","** Type Identifier *}* *]* **")"** **"{"** *{* VarDeclaration *}* *{* Statement *}* **"return"** Expression **";"** **"}"**
- Type-> **"int"** **"["** **"]"***|***"boolean"***|***"int"***|* Identifier
- Statement-> **"{"** *{* Statement *}* **"}"***|***"if"** **"("** Expression **")"** Statement **"else"** Statement *|***"while"** **"("** Expression **")"** Statement *|***"System.out.println"** **"("** Expression **")"** **";"***|* Identifier **"="** Expression **";"***|* Identifier **"["** Expression **"]"** **"="** Expression **";"**
- Expression-> Expression *(* "&&" | "<" | "+" | "-" | "*" *)* Expression *|* Expression **"["** Expression **"]"***|* Expression **"."** **"length"***|* Expression **"."** Identifier **"("** *[* Expression *{* **","** Expression *}* *]* **")"***|* IntegerLiteral *|***"true"***|***"false"***|* Identifier *|***"this"***|***"new"** **"int"** **"["** Expression **"]"***|***"new"** Identifier "(" ")"*|* **"!"** Expression *|***"("** Expression **")"**

# 抽象语法树

## 消除左递归

- Goal-> MainClass *{* ClassDeclaration *}* EOF

- MainClass-> **"class"** Identifier **"{"** **"public"** **"static"** **"void"** **"main"** **"("** **"String"** **"["** **"]"** Identifier **")"** **"{"** Statement **"}"** **"}"**

- ClassDeclaration-> **"class"** Identifier *[* **"extends"** Identifier *]* **"{"** *{* VarDeclaration *}* *{* MethodDeclaration *}* **"}"**

- VarDeclaration-> Type Identifier ";"

- MethodDeclaration-> **"public"** Type Identifier **"("** *[* Type Identifier *{* **","** Type Identifier *}* *]* **")"** **"{"** *{* VarDeclaration *}* *{* Statement *}* **"return"** Expression **";"** **"}"**

- Type-> **"int"** **"["** **"]"***|***"boolean"***|***"int"***|* Identifier

- Statement-> **"{"** *{* Statement *}* **"}"***|***"if"** **"("** Expression **")"** Statement **"else"** Statement *|***"while"** **"("** Expression **")"** Statement *|***"System.out.println"** **"("** Expression **")"** **";"***|* Identifier **"="** Expression **";"***|* Identifier **"["** Expression **"]"** **"="** Expression **";"**

- Expression-> IntegerLiteral Exp’ /

  "true" Exp’/

  "false" Exp’/

  Identifier Exp’/

  "this" Exp’/

  "new" "int" "[" Expression "]" Exp’/

  "new" Identifier "(" ")" A Exp’/

  "!" Expression Exp’/

  "(" Expression ")" Exp’

- Exp’-> ( "&&" | "<" | "+" | "-" | "*" ) Expression Exp’/

   "[" Expression "]" Exp’/

   "." "length" Exp’/

   "." Identifier "(" [ Expression { "," Expression } ] ")" Exp’/ 

   ε

## 画出抽象语法树

- Goal-> MainClass *{* ClassDeclaration *}* EOF

  <img src="assets/SyntaxTree.png" alt="SyntaxTree" style="zoom:50%;" />

- MainClass-> **"class"** Identifier **"{"** **"public"** **"static"** **"void"** **"main"** **"("** **"String"** **"["** **"]"** Identifier **")"** **"{"** Statement **"}"** **"}"**

  <img src="assets/SyntaxTree (1).png" alt="SyntaxTree (1)" style="zoom:50%;" />

- ClassDeclaration-> **"class"** Identifier *[* **"extends"** Identifier *]* **"{"** *{* VarDeclaration *}* *{* MethodDeclaration *}* **"}"**

  <img src="assets/SyntaxTree-3067073.png" alt="SyntaxTree" style="zoom:50%;" />

- VarDeclaration-> Type Identifier **";"**

  <img src="assets/SyntaxTree (2).png" alt="SyntaxTree (2)" style="zoom:50%;" />

- MethodDeclaration-> **"public"** Type Identifier **"("** *[* Type Identifier *{* **","** Type Identifier *}* *]* **")"** **"{"** *{* VarDeclaration *}* *{* Statement *}* **"return"** Expression **";"** **"}"**

  <img src="assets/SyntaxTree (3)-3066787.png" alt="SyntaxTree (3)" style="zoom:50%;" />

- Type-> **"int"** **"["** **"]"***|***"boolean"***|***"int"***|* Identifier

  ![SyntaxTree2](assets/SyntaxTree2.png)

- Statement-> StatementSeries | if_Statement | While_Statement | Print_Statement | VarAssign_Statement | ArrayAssign_Statement

  <img src="assets/SyntaxTree2 (1).png" alt="SyntaxTree2 (1)" style="zoom:50%;" />

- StatementSeries-> **"{"** { Statement } **"}"**

  <img src="assets/SyntaxTree2 (2).png" alt="SyntaxTree2 (2)" style="zoom:50%;" />

- If_Satement-> **"if"** **"("** Expression **")"** Statement **"else"** Statement

  <img src="assets/SyntaxTree2 (3).png" alt="SyntaxTree2 (3)" style="zoom:50%;" />

- While_Satement-> **"while"** **"("** Expression **")"** Statement 

  <img src="assets/SyntaxTree2 (4).png" alt="SyntaxTree2 (4)" style="zoom:50%;" />

- Print_Statement-> **"System.out.println"** **"("** Expression **")"** **";"**

  <img src="assets/SyntaxTree2 (5).png" alt="SyntaxTree2 (5)" style="zoom:50%;" />

- VarAssign_Statement-> identifier **"="** Expression **";"**

  <img src="assets/SyntaxTree2 (6).png" alt="SyntaxTree2 (6)" style="zoom:50%;" />

- ArrayAssign_Statement-> identifier **"["** Expression **"]"** **"="** Expression **";**

  ![SyntaxTree2 (7)](assets/SyntaxTree2 (7).png)

- Expression-> int_Expression | true_Expression | false_Expression | identifier_Expression | this_Expression | newArray_Expression | new_Expression | not_Expression | brace_Expression

  <img src="assets/SyntaxTree2 (8).png" alt="SyntaxTree2 (8)" style="zoom:50%;" />

- int_Expression-> IntegerLiteral **Exp’**

  <img src="assets/SyntaxTree2 (9).png" alt="SyntaxTree2 (9)" style="zoom:50%;" />

- true_Expression**-> "true"** **Exp’**

  <img src="assets/SyntaxTree2 (10).png" alt="SyntaxTree2 (10)" style="zoom:50%;" />

- false_Expression**-> "false"** **Exp’**

  <img src="assets/SyntaxTree2 (11).png" alt="SyntaxTree2 (11)" style="zoom:50%;" />

- identifier_Expression-> Identifier **Exp’**

  <img src="assets/SyntaxTree2 (12).png" alt="SyntaxTree2 (12)" style="zoom:50%;" />

- this_Expression**-> "this"** **Exp’**

  <img src="assets/SyntaxTree2 (13).png" alt="SyntaxTree2 (13)" style="zoom:50%;" />

- newArray_Expression**-> "new"** **"int"** **"["** **Expression** **"]"** **Exp’**

  <img src="assets/SyntaxTree2 (14).png" alt="SyntaxTree2 (14)" style="zoom:50%;" />

- new_Expression**-> "new"** Identifier "(" ")" **Exp’**

  <img src="assets/SyntaxTree2 (15).png" alt="SyntaxTree2 (15)" style="zoom:50%;" />

- not_Expression**-> "!"** **Expression** **Exp’**

  <img src="assets/SyntaxTree2 (16).png" alt="SyntaxTree2 (16)" style="zoom:50%;" />

- brace_Expression-> **"("** **Expression** **")"** **Exp’**

  <img src="assets/SyntaxTree2 (17).png" alt="SyntaxTree2 (17)" style="zoom:50%;" />

- **Exp’**-> op_ **Exp’** | experssion_ **Exp’** | length_ **Exp’** | method_ **Exp’** | null_ **Exp’**

  <img src="assets/SyntaxTree3.png" alt="SyntaxTree3" style="zoom:50%;" />

- Op_ **Exp’**-> ( "&&" | "<" | "+" | "-" | "*" ) **Expression** **Exp’**

  <img src="assets/SyntaxTree2 (18).png" alt="SyntaxTree2 (18)" style="zoom:50%;" />

- Experssion_ **Exp’**-> **"["** **Expression** **"]"** **Exp’**

  ![SyntaxTree2 (19)](assets/SyntaxTree2 (19).png)

- Length_ **Exp’**-> **"."** **"length"** **Exp’**

  <img src="assets/SyntaxTree2 (20).png" alt="SyntaxTree2 (20)" style="zoom:50%;" />

- Method_ **Exp’**-> **"."** Identifier **"("** [ **Expression** { **","** **Expression** } ] **")"** **Exp’**

  <img src="assets/SyntaxTree3 (1).png" alt="SyntaxTree3 (1)" style="zoom:50%;" />

- Null_ **Exp’**-> ε

  <img src="assets/SyntaxTree2 (21).png" alt="SyntaxTree2 (21)" style="zoom:50%;" />