// ------------------------------------------------ ExpTree.cpp -------------------------------------------------------

// Giselle McNeill CSS343 - 11AM T/TH with Wooyoung Kim

// Creation Date 4/22/26

// Date of Last Modification 4/24/26

// --------------------------------------------------------------------------------------------------------------------

// Purpose:
// Defines the ExpTree class, which implements a binary tree that is used to represent and evaluate
// algebraic expressions.

// The tree is constructed from a valid infix expression, where it first converts the infix to postfix
// and constructs the tree so that operands act as leaf nodes and the operators are internal nodes

// This class supports inorder, preorder, and postorder traversals, expression evaluation when values
// are provided for variables in a map, as well as offering tree visualization in two different forms.
// It also supports functions such as calculating tree height and returning whether a tree is empty.

// This class also properly manages its own memory through the constructors, destructors, and
// the copy constructor, which performs a deep copy of the ExpTree.
// --------------------------------------------------------------------------------------------------------------------

#ifndef CSS343_PROGRAM2_EXPTREE_H
#define CSS343_PROGRAM2_EXPTREE_H
#include <string> //Used for the string variable types
#include <unordered_map> //Used for the map variable type
#include <iostream> //Used for the output operator



struct Node { //Declaring Node Object that will be used
    std::string value;
    Node* left;
    Node* right;

    // Constructor with a parameter to initialize the node value
    Node(const std::string& val);
};

class ExpTree {
public:
    ExpTree(); //Constructor: empty tree, head = nullptr
    ExpTree(const std::string& exp); //Constructor to build a expression tree

    ~ExpTree(); //Destructor

    ExpTree(const ExpTree& other); //Copy Constructor

    std::string inorder(); //Traverse tree printing values infix notation
    std::string preorder(); //Traverse tree printing values prefix notation
    std::string postorder(); //Traverse tree printing values postfix notation

    //Standard print of the ExpTree for human readability
    friend std::ostream& operator<<(std::ostream& os, const ExpTree& tree);

    //Sideways print of the ExpTree for human readability
    void displaySideways(std::ostream&os= std::cout) const;

    // evaluate the postfix expression using the postfix notation and a map of variables with values
    double evaluate_postfix(const std::string& postfix, const std::unordered_map<char, double>& exp_map);

    // Function to get the height of the tree.
    int getHeight();

    // Function to check if the tree is empty.
    bool isEmpty();



private:
    std::string expression; //Expression to be passed in to build tree
    Node* root; //Root of the tree, will be last performed operator

    //Helper Function to remove white space from passed in expression
    std::string removeWhiteSpace(const std::string& input);

    //Helper Function to determine precedence (order of operations) of operators
    int precedence(char op);

    //Helper Function to convert the infix expression to a postfix expression
    std::string inFixToPostFix(const std::string& infix);

    //Helper Function to deallocate allocated memory in the tree
    void destroyExpTree(Node*& node);

    //Helper function to perform a deep copy
    Node* copyTree(Node* node);

    //Helper function to perform traversal
    std::string inorder(Node* node);

    //Helper function to perform traversal
    std::string preorder(Node* node);

    //Helper function to perform traversal
    std::string postorder(Node* node);

    //Helper function to calculate height
    int getHeight(Node* node);

    //Helper function to print ExpTree for human readability
    void printTree(Node* node, std::ostream& os, std::string indent, bool isLeft) const;

    //Helper function to print ExpTree sideways for human readability
    void displaySideways(Node* node, int level, std::ostream& os) const;

    //Helper function to validate postfix expression
    bool validPostFix(const std::string& postfix);

};

#endif //CSS343_PROGRAM2_EXPTREE_H