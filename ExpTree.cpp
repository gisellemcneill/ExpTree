// ------------------------------------------------ ExpTree.cpp -------------------------------------------------------

// Giselle McNeill CSS343 - 11AM T/TH with Wooyoung Kim

// Creation Date 4/22/26

// Date of Last Modification 4/24/26

// --------------------------------------------------------------------------------------------------------------------

// Purpose:
// Implements the ExpTree class using a binary tree structure. Supports the construction of an expression tree
// from an infix expreeion by converting it to a postfix expression that can be used to build the tree.

// Expression Tree functions include:
// inorder(), preorder(), postorder(), evaluate_postfix(), getHeight(), isEmpty(), displaySideways(), operator<<

// Additional Helper functions were created as well:
// There are four helper methods for the constructor to perform the infix to postfix notation
// inFixToPostFix(), precedence(), removeWhiteSpace(), validPostFix()
// There is one helper method for the destructor: destroyExpTree()
// One helper for the copy constructor: copyTree()
// One helper for each traversal: inorder(), preorder(), postorder()
// One helper for calculating height: getHeight()
// One helper for operator<<: printTree()
// One helper for displaySideways(): displaySideways()
// --------------------------------------------------------------------------------------------------------------------


#include "ExpTree.h"

#include <string> //Used for string
#include <stack> //Used for stack
#include <algorithm> //Used for max computation
#include <cmath> //Used for evaluate exponents
using namespace std; //Used for naming convenience


// ------------------------------------ Node Constructor ------------------------------------
// Description:
// Initializes a Node with the given value and sets child pointers to nullptr
//
// Preconditions:
// A valid string value is provided
//
// Postconditions:
// Node is created with left and right pointers initialized to nullptr
// --------------------------------------------------------------------------------------------
Node::Node(const string &val) {
    value = val;
    left = nullptr;
    right = nullptr;
}
// End of Node Constructor


// ------------------------------------ ExpTree Default Constructor ------------------------------------
// Description:
// Initializes an empty expression tree
//
// Preconditions:
// None
//
// Postconditions:
// root is set to nullptr representing an empty tree
// --------------------------------------------------------------------------------------------
ExpTree::ExpTree() {
    root = nullptr;
}
//End of Default Constructor


// ------------------------------------ ExpTree Constructor ------------------------------------
// Description:
// Constructs an expression tree from a given infix expression by removing
// whitespace, converting to postfix notation, and building the binary tree
//
// Preconditions:
// exp is a valid algebraic expression (may contain whitespace)
//
// Postconditions:
// If valid, root points to a fully constructed expression tree
// If invalid, root is set to nullptr (empty tree)
// --------------------------------------------------------------------------------------------
ExpTree::ExpTree(const string &exp) {

    //Perform helper methods to ensure tree can be built
    string cleaned = removeWhiteSpace(exp);
    string postfix = inFixToPostFix(cleaned);

    if (postfix == "" || !validPostFix(postfix)) {
        root = nullptr;
        return;
    }

    stack<Node *> nodeStack;

    for (int i = 0; i < postfix.length(); i++) {
        char c = postfix[i];

        //If operand push into stack
        if (isalpha(c)) {
            Node *newNode = new Node(string(1, c));
            nodeStack.push(newNode);
        } else {

            //If operator is found store two operands
            Node *right = nodeStack.top();
            nodeStack.pop();
            Node *left = nodeStack.top();
            nodeStack.pop();

            //Store operator as internal node, place operands as children
            Node *operatorNode = new Node(string(1, c));
            operatorNode->left = left;
            operatorNode->right = right;

            nodeStack.push(operatorNode);
        }
    }

    if (nodeStack.size() != 1) {
        destroyExpTree(nodeStack.top());
        root = nullptr;
        return;
    }

    root = nodeStack.top();
}
//End of Constructor


// ------------------------------------ ExpTree Copy Constructor ------------------------------------
// Description:
// Creates a deep copy of another ExpTree object
// Calls on helper method to perform logic 
//
// Preconditions:
// other is a valid ExpTree object
//
// Postconditions:
// A new independent tree is created with identical structure and values
// --------------------------------------------------------------------------------------------
ExpTree::ExpTree(const ExpTree &other) {
    root = copyTree(other.root);
}
//End of Copy Constructor


// ------------------------------------ ExpTree Destructor ------------------------------------
// Description:
// Frees all dynamically allocated nodes in the expression tree
// Calls on helper method to perform logic of recursion
//
// Preconditions:
// Tree may contain allocated nodes
//
// Postconditions:
// All nodes are deleted, and the root is set to nullptr
// --------------------------------------------------------------------------------------------
ExpTree::~ExpTree() {
    destroyExpTree(root);
    root = nullptr;
}
//End of Destructor


// ------------------------------------ ExpTree inorder() ------------------------------------
// Description:
// Performs an inorder traversal of the expression tree
// Calls on helper method to perform logic of recursion
//
// Preconditions:
// Tree may be empty or non-empty
//
// Postconditions:
// Returns a string representing the infix expression
// --------------------------------------------------------------------------------------------
string ExpTree::inorder() {
    return inorder(root);
}
//End of inorder()


// ------------------------------------ ExpTree preorder() ------------------------------------
// Description:
// Performs a preorder traversal of the expression tree
// Calls on helper method to perform logic of recursion
//
// Preconditions:
// Tree may be empty or non-empty
//
// Postconditions:
// Returns a string representing the prefix expression
// --------------------------------------------------------------------------------------------
string ExpTree::preorder() {
    return preorder(root);
}
//End of preorder()


// ------------------------------------ ExpTree postorder() ------------------------------------
// Description:
// Performs a postorder traversal of the expression tree
// Calls on helper method to perform logic of recursion
//
// Preconditions:
// Tree may be empty or non-empty
//
// Postconditions:
// Returns a string representing the postfix expression
// --------------------------------------------------------------------------------------------
string ExpTree::postorder() {
    return postorder(root);
}
//End of postorder()


// ------------------------------------ ExpTree operator<<() ------------------------------------
// Description:
// Outputs the expression tree in a hierarchical human-readable format
// As levels progress deeper the spacing will be increased by 6 spaces
//
// Preconditions:
// Tree object exists
//
// Postconditions:
// Tree structure is printed to output stream
// --------------------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const ExpTree &tree) {

    if (tree.root == nullptr) {
        return os;
    }

    os << "Root: " << tree.root->value << endl;

    tree.printTree(tree.root->left, os, "      ", true);
    tree.printTree(tree.root->right, os, "      ", false);

    return os;
}
//End of operator<<()


// ------------------------------------ ExpTree displaySideways() ------------------------------------
// Description:
// Displays the expression tree rotated 90 degrees counterclockwise making it legible to humans
// Calls on helper method to perform logic of recursion
//
// Preconditions:
// Tree may be empty or non-empty
//
// Postconditions:
// Tree is printed sideways for visualization
// --------------------------------------------------------------------------------------------
void ExpTree::displaySideways(std::ostream &os) const {
    displaySideways(root, 0, os);
}
//End of printSideways()


// ------------------------------------ ExpTree evaluate_postfix() ------------------------------------
// Description:
// Evaluates a postfix expression using a stack and variable map
//
// Preconditions:
// postfix is a valid postfix expression
// exp_map contains mappings and values for all variables
//
//
// Postconditions:
// Returns computed result or NaN if expression is invalid
// --------------------------------------------------------------------------------------------
double ExpTree::evaluate_postfix(const std::string &postfix, const std::unordered_map<char, double> &exp_map) {

    stack<double> final;

    for (char c: postfix) {
        //Check if value operand exists in map
        if (isalpha(c)) {
            if (exp_map.count(c) == 0) {
                return NAN;
            }

            final.push(exp_map.at(c));
        } else {
            //if operator there must be at least 2 operators in stack
            if (final.size() < 2) {
                return NAN;
            }

            //store two values from stack to calculate
            double right = final.top();
            final.pop();
            double left = final.top();
            final.pop();

            double result = 0;

            //calculate results depending on the operator
            switch (c) {
                case '+':
                    result = left + right;
                    break;
                case '-':
                    result = left - right;
                    break;
                case '*':
                    result = left * right;
                    break;
                case '/':
                    if (right == 0) { //undefined check
                        return NAN;
                    }
                    result = left / right;
                    break;
                case '^':
                    result = pow(left, right);
                    break;
                default:
                    return NAN; //undefined operator/character check
            }
            final.push(result);
        }
    }

    //Only one value should now exist in the stack
    if (final.size() != 1) {
        return NAN;
    }

    return final.top();
}
//End of evaluate_postfix()


// ------------------------------------ getHeight() ------------------------------------
// Description:
// Computes the height of the expression tree by calling on helper method
//
// Preconditions:
// Tree may be empty or non-empty
//
// Postconditions:
// Returns height of tree, empty tree = 0
// --------------------------------------------------------------------------------------------
int ExpTree::getHeight() {
    return getHeight(root);
}
//End of getHeight()


// ------------------------------------ isEmpty() ------------------------------------
// Description:
// Checks whether the expression tree is empty
//
// Preconditions:
// None
//
// Postconditions:
// Returns true if root is nullptr, otherwise false
// --------------------------------------------------------------------------------------------
bool ExpTree::isEmpty() {
    return root == nullptr;
}
//End of isEmpty()


// ------------------------------------ Helper removeWhiteSpace() ------------------------------------
// Description:
// Removes all whitespace characters from a string
//
// Preconditions:
// input is a valid string
//
// Postconditions:
// Returns a new string with all spaces and tabs removed
// --------------------------------------------------------------------------------------------
string ExpTree::removeWhiteSpace(const string &input) {
    string final;

    for (int i = 0; i < input.length(); i++) {
        if (input[i] != ' ' && input[i] != '\t') {
            final.push_back(input[i]);
        }
    }

    return final;
}
//End of removeWhiteSpace()


// ------------------------------------ Helper precedence() ------------------------------------
// Description:
// Determines operator precedence for infix-to-postfix conversion
//
// Preconditions:
// op is a valid operator character
//
// Postconditions:
// Returns integer priority value of operator
// --------------------------------------------------------------------------------------------
int ExpTree::precedence(char op) {
    if (op == '^') {
        return 3;
    } else if (op == '*' || op == '/') {
        return 2;
    } else if (op == '+' || op == '-') {
        return 1;
    } else {
        return 0;
    }
}
//End of precedence()


// ------------------------------------ Helper infixToPostfix() ------------------------------------
// Description:
// Converts an infix expression to postfix notation using a stack
//
// Preconditions:
// infix is a valid algebraic expression (may contain whitespace or tabs)
//
// Postconditions:
// Returns postfix expression as a string
// Invalid expressions  return empty string
// --------------------------------------------------------------------------------------------
string ExpTree::inFixToPostFix(const string &infix) {

    if (infix.length() == 0) {
        return "";
    }


    stack<char> operatorStack;
    string postfix;
    bool parenthesisFlag = false;

    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];

        //If operand is found, add to expression
        if (isalpha(c)) {
            postfix += c;
            parenthesisFlag = true;

        //If opening bracket add to stack
        } else if (c == '(') {
            operatorStack.push(c);
            parenthesisFlag = false;

        //If closing bracket pop and add to expression until open bracket is found
        } else if (c == ')') {

            if (!parenthesisFlag) {
                return "";
            }
            while (!operatorStack.empty()
                   && operatorStack.top() != '(') {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            if (!operatorStack.empty()) {
                operatorStack.pop();
            }

         //If operator check precedence, add and pop if greater than or equal to c
        } else if (c == '+' || c == '-'
                   || c == '*' || c == '/') {
            while (!operatorStack.empty() &&
                   precedence(operatorStack.top()) >= precedence(c)) {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(c);

        //If exponent check precedence and if greater add and pop
        } else if (c == '^') {
            while (!operatorStack.empty() &&
                   precedence(operatorStack.top()) > precedence(c)) {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(c);

        //If invalid return empty
        } else {
            return "";
        }
    }

    //Add all remaining characters to expression
    while (!operatorStack.empty()) {
        postfix += operatorStack.top();
        operatorStack.pop();
    }

    return postfix;
}
//End of inFixToPostFix()

// ------------------------------------ Helper destroyExpTree() ------------------------------------
// Description:
// Recursively deallocates all nodes in the expression tree
//
// Preconditions:
// node is either nullptr or a valid tree node
//
// Postconditions:
// All nodes in the subtree are deleted and memory is freed
// --------------------------------------------------------------------------------------------
void ExpTree::destroyExpTree(Node *&node) {
    if (node == nullptr) {
        return;
    }

    destroyExpTree(node->left);
    destroyExpTree(node->right);
    delete node;
}
//End of destroyExpTree

// ------------------------------------ Helper copyTree() ------------------------------------
// Description:
// Performs a deep copy of a subtree rooted at the given node
//
// Preconditions:
// node is either nullptr or a valid tree node
//
// Postconditions:
// Returns a new subtree identical in structure and values to the original
// --------------------------------------------------------------------------------------------
Node *ExpTree::copyTree(Node *node) {
    if (node == nullptr) {
        return nullptr;
    } else {
        Node *newNode = new Node(node->value);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }
}
//End of copyTree()


// ------------------------------------ Helper inorder() ------------------------------------
// Description:
// Recursively performs inorder traversal starting from a given node
//
// Preconditions:
// node is either nullptr or a valid tree node
//
// Postconditions:
// Returns a string representing the inorder traversal of the subtree
// --------------------------------------------------------------------------------------------
std::string ExpTree::inorder(Node *node) {
    if (node == nullptr) {
        return "";
    }

    string final;

    final += inorder(node->left);
    final += node->value;
    final += inorder(node->right);

    return final;
}
//End of inorder()


// ------------------------------------ Helper preorder() ------------------------------------
// Description:
// Recursively performs preorder traversal starting from a given node
//
// Preconditions:
// node is either nullptr or a valid tree node
//
// Postconditions:
// Returns a string representing the preorder traversal of the subtree
// --------------------------------------------------------------------------------------------
std::string ExpTree::preorder(Node *node) {
    if (node == nullptr) {
        return "";
    }

    string final;

    final += node->value;
    final += preorder(node->left);
    final += preorder(node->right);

    return final;
}
//End of preorder


// ------------------------------------ Helper postorder() ------------------------------------
// Description:
// Recursively performs postorder traversal starting from a given node
//
// Preconditions:
// node is either nullptr or a valid tree node
//
// Postconditions:
// Returns a string representing the postorder traversal of the subtree
// --------------------------------------------------------------------------------------------
std::string ExpTree::postorder(Node *node) {
    if (node == nullptr) {
        return "";
    }

    string final;

    final += postorder(node->left);
    final += postorder(node->right);
    final += node->value;

    return final;
}
//End of postorder

// ------------------------------------ Helper getHeight() ------------------------------------
// Description:
// Recursively computes the height of a subtree
//
// Preconditions:
// node is either nullptr or a valid tree node
//
// Postconditions:
// Returns height of subtree (nullptr = 0, leaf = 1)
// --------------------------------------------------------------------------------------------
int ExpTree::getHeight(Node *node) {
    if (node == nullptr) {
        return 0;
    }

    int left = getHeight(node->left);
    int right = getHeight(node->right);

    return 1 + std::max(left, right);
}
//End of getHeight()


// ------------------------------------ Helper printTree() ------------------------------------
// Description:
// Prints the expression tree in a structured hierarchical format
//
// Preconditions:
// node may be nullptr or a valid tree node
//
// Postconditions:
// Tree structure is output to the provided stream
// --------------------------------------------------------------------------------------------
void ExpTree::printTree(Node *node, std::ostream &os, string indent, bool isLeft) const {
    if (node == nullptr) {
        return;
    }
    if (isLeft == true) {
        os << indent << "L --- " << node->value << endl;
    } else {
        os << indent << "R --- " << node->value << endl;
    }

    printTree(node->left, os, indent + "    ", true);
    printTree(node->right, os, indent + "    ", false);
}
//End of printTree()


// ------------------------------------ Helper displaySideways() ------------------------------------
// Description:
// Recursively prints the tree rotated 90 degrees counterclockwise
//
// Preconditions:
// node may be nullptr or valid tree node
//
// Postconditions:
// Tree is printed sideways for visualization
// --------------------------------------------------------------------------------------------
void ExpTree::displaySideways(Node *node, int level, std::ostream &os) const {
    if (node == nullptr) {
        return;
    }

    displaySideways(node->right, level + 1, os);

    for (int i = 0; i < level; i++) {
        os << "      ";
    }

    os << node->value << endl;


    displaySideways(node->left, level + 1, os);
}
//End of displaySideways()


// ------------------------------------ Helper validPostfix() ------------------------------------
// Description:
// Validates whether a postfix expression is structurally correct
//
// Preconditions:
// postfix is a non-empty string
//
// Postconditions:
// Returns true if postfix expression is valid, otherwise false
// --------------------------------------------------------------------------------------------
bool ExpTree::validPostFix(const string &postfix) {
    int balance = 0;

    for (char c: postfix) {
        if (isalpha(c)) {
            balance++;
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            if (balance < 2) {
                return false;
            }
            balance -= 2;
            balance += 1;
        } else {
            return false;
        }
    }

    return balance == 1;
}
//End of validPostFix
