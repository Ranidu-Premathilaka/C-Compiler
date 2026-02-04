University of Colombo School of Computing
SCS 2312 - Computational Models and Programming Language Concepts
Take-home Assignment
Write a C program (parser.c) to read a source file containing following code, parse the
code and execute the logic. The program must be executable via the command line and
accept the source file as the first argument. Example Command: ./parser inputfile

```C
int y = 5;
int x = 20;
int z = x + y;
print(z);
```

Task breakdown
1. Define a Context-Free Grammar (CFG) that accurately represents the given code structure (15 marks).
2. Implement a tokeniser to identify and categorise tokens (keywords, identifiers, and operators) (20 marks).
3. Build the parse logic which correctly follows the created CFG rules (30 marks).
4. Implement detection for syntax errors and semantic errors (20 marks).
5. Correctly perform the arithmetic operations and display the final result (15 marks).

Submissions
1. A single C file containing your complete implementation. It should be error free and should be compiled in the examiners computer.
2. PDF with CFG, code explanations and other relevant evidence

Evaluation
• Examiners will execute the program with two files, one with a correct code and the other with errors to check the accuracy of the program.
Note: All submissions will undergo plagiarism detection and marks will be given based on a viva examination