# Expression Tree in C++

This project implements an algebraic expression tree in C++ that parses infix mathematical expressions and builds a binary tree representation using a stack-based algorithm.

The program supports tree traversal, expression evaluation using variable values, and proper dynamic memory management.

## Project Structure

- `ExpTree.h` – Class definition for the expression tree
- `ExpTree.cpp` – Implementation of tree construction, traversal, and evaluation
- `main.cpp` – Driver program used to compile and test the tree functionality
- `expressions.txt` – Input file containing infix expressions to parse
- `variable_map.txt` – File containing variable values used during evaluation

## Features

- Parses infix expressions with variables and operators
- Builds an expression tree using stacks
- Supports inorder, preorder, and postorder traversal
- Evaluates expressions using a provided variable map
- Demonstrates recursion, pointers, and dynamic memory management
- Includes destructor logic to prevent memory leaks

## How It Works

1. Expressions are read from `expressions.txt`
2. The program constructs a binary expression tree for each expression
3. Variable values are loaded from `variable_map.txt`
4. The tree is traversed and the expression is evaluated
5. Results and traversals are printed to the console

## Example

Expression from `expressions.txt`:
a + b * c

Variable values from `variable_map.txt`:

a = 2

b = 3

c = 4



Output:
- Inorder: a + b * c
- Preorder: + a * b c
- Postorder: a b c * +
- Evaluation Result: 14

## Concepts Demonstrated

This project focuses on fundamental computer science concepts:

- Stacks
- Binary Trees
- Expression Parsing
- Recursion
- Object-Oriented Design in C++
- Dynamic Memory Management
