# COMPILER-LAB

[![download](https://img.shields.io/badge/Direct_Download-zip-blue.svg?logo=appveyor\&longCache=true\&style=for-the-badge)](https://github.com/5heron/COMPILER-LAB/archive/refs/heads/main.zip)

B.Tech CSE Compiler Design Lab

University: APJ Abdul Kalam Technological University

## 📌 Content

* **[Lex](Lex)**

  * Lexical Analysis Programs:

    * [armstrong.l](Lex/armstrong.l)
    * [calculator.l](Lex/calculator.l)
    * [evenOdd.l](Lex/evenOdd.l)
    * [nLinesSpacesTabs.l](Lex/nLinesSpacesTabs.l)
    * [palindrome.l](Lex/palindrome.l)
    * [positivesCnt.l](Lex/positivesCnt.l)
    * [prime.l](Lex/prime.l)
    * [vowelConsonant.l](Lex/vowelConsonant.l)
    * [lex.l](Lex/lex.l)
  * Input Files:

    * [input.txt](Lex/input.txt)
    * [inputNumbers.txt](Lex/inputNumbers.txt)

* **[Yacc](Yacc)**

  * Parser Programs:

    * [ExpressionEval.y](Yacc/ExpressionEval.y)
    * [ExpressionEval.l](Yacc/ExpressionEval.l)

* **Other Programs**

  * [firstNFollw.c](firstNFollw.c) : First and Follow set computation
  * [IntermediateCodeGen.c](IntermediateCodeGen.c) : Intermediate code generation
  * [shiftReduce.c](shiftReduce.c) : Shift-Reduce parser example
  * [lex.c](lex.c) : Generic lex program

---

## 🔧 Requirements

1. **Flex & Bison**

   * Linux: install via package manager (`sudo apt install flex bison`)
   * Windows: install via [Cygwin](https://www.cygwin.com/) or [WSL](https://learn.microsoft.com/en-us/windows/wsl/)

2. **GCC Compiler**

   * Linux: usually pre-installed
   * Windows: [TDM-GCC MinGW Compiler](https://sourceforge.net/projects/tdm-gcc/)

3. **Any Text Editor**

   * [VS Code](https://code.visualstudio.com/)
   * [Sublime Text](https://www.sublimetext.com/)
   * [Atom](https://atom.io/)

---

## 🚀 Getting Started

Clone this repo:

```sh
$ git clone https://github.com/5heron/COMPILER-LAB.git
```

Switch to the program folder:

```sh
$ cd COMPILER-LAB
```

### **🖥️ Running Lex Programs**

1. **Compile using Flex**

```sh
$ flex filename.l
$ gcc lex.yy.c -o program -lfl
```

2. **Run the program**

```sh
$ ./program
```

### **🖥️ Running Yacc/Bison Programs**

1. **Generate parser and lexer**

```sh
$ bison -d ExpressionEval.y
$ flex ExpressionEval.l
```

2. **Compile both**

```sh
$ gcc y.tab.c lex.yy.c -o expr_eval -lfl
```

3. **Run the program**

```sh
$ ./expr_eval
```

---

## ⭐ Spread the Word!

If you found this helpful, give it a ⭐ and share it with your peers!

 next?
