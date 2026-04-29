// ------------------------------------------------ driver.cpp -------------------------------------------------------

// Giselle McNeill CSS343 - 11AM T/TH with Wooyoung Kim

// Creation Date 4/24/26

// Date of Last Modification 4/24/26

// --------------------------------------------------------------------------------------------------------------------

// Purpose:
// This driver program is designed to test the accuracy of the ExpTree implementations
// Verifies that each ExpTree operation behaves as expected

// functions tested are:
// inorder(), preorder(), postorder(), evaluate_postfix(), getHeight(), isEmpty(), displaySideways(), operator<<

// The goal of this file is to ensure logical correctness and proper implementation, valid postfix expression creation,
// , correct ExpTree building and good memory management that results in no memory leaks

// --------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------



#include <iostream>
#include <unordered_map>
#include <fstream>
#include "ExpTree.h"

using namespace std;

unordered_map<char, double> read_values(ifstream& infile, int count) {
    unordered_map<char, double> values;
    for (int i = 0; i < count; i++) {
        char var;
        double val;
        infile >> var >> val;
        values[var] = val;
    }
    return values;
}

//Function to test implementation of each function in the ExpTree
int test_a_tree(string expression, unordered_map<char, double> values) {

    //Testing Tree Building
    cout << "Building tree from expression: " << expression << "\n";
    ExpTree tree(expression);

    //Testing isEmpty and if trees exist
    cout << "First Tree Built (0 for built, 1 for not): " << tree.isEmpty() << "\n";

    //Testing if copy constructor worked
    ExpTree tree2(tree);
    cout << "Testing Copy Constructor: " <<  "\n";
    cout << "Second Tree Built (0 for built, 1 for not): " << tree.isEmpty() << "\n";

    //Testing height calculation
    cout << "Height: " << tree.getHeight() << "\n";

    //Testing print operator
    cout << "Print (operator<<):\n" << tree << "\n";

    //Testing print sideways
    cout << "Display sideways:\n";
    tree.displaySideways();
    cout << "\n";

    //Testing all traversals
    cout << "Traversals:\n";
    cout << "  Inorder:   " << tree.inorder() << "\n";
    cout << "  Preorder:  " << tree.preorder() << "\n";
    cout << "  Postorder: " << tree.postorder() << "\n";

    //Testing postfix evaluation
    cout << "Evaluation with provided variable map: ";
    double result = tree.evaluate_postfix(tree.postorder(), values);
    cout << result << "\n\n";


    return 0;
}


int main(){
    // Read the mapping of variables to values from the input file
    ifstream infile("variable_map.txt");
    if (!infile) {
        cerr << "Error opening variable map file!" << endl;
        return -1;
    }

    unordered_map<char, double> variable_map = read_values(infile, 7);
    string expression="";

    ifstream expfile("expressions.txt");
    if(!expfile) {
        cerr << "Error opening expressions file!" << endl;
        return -1;
    }


    while (getline(expfile, expression)) {
        if (expression == "exit") {
            break;
        }

        cout << "-------------------------------------------\n";
        cout << "\nProcessing expression: " << expression << endl;
        test_a_tree(expression, variable_map);

    }


    return 0;
}