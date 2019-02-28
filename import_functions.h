
/**********************\
 * Function Prototypes
\**********************/
#ifndef CONSOLE
#define CONSOLE
#include <iostream>
#include <iomanip>
#include <fstream>
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef RANDOM
#define RANDOM
#include <time.h>
#include <random>
#endif

#ifndef STRING
#define STRING
#include <string>
#include <ctype.h>
#endif

using namespace std;

// strips spaces on the beginning/end of the input string, but not encapsulated spaces
string strip_spaces(string&);

// creates a simple vector from an input, split by a customizable delimeter. 
// Spaces around delimeters are discarded.
vector<string> generate_array(string&, char);

//outputs a multidimensional vector of strings from an input file
vector<vector<string>> import_file(string&);

// outputs every row in the multidimensional input vector that matches the input parameters
// requres: 
// - pointer to a multidimensional input vector (vector<vector<string>>)
// - value to search for (string)
// - column in vector array to search for match (zero-based)
vector<vector<string>> get_matches(vector<vector<string>>&, string, int);

// outputs the contents of a 2-dimensional vector of strings to the console in CSV format.
// requires: vector<vector<string>> input val
void print_string_vector_vector (vector<vector<string>>&);

// Takes a vector of vectors of strings and **directly modifies it** to delete malformed lines.
// This fixes any errors caused by attempting to access array positions that *should* be valid,
// but aren't due to garbage data.
// Inputs: vector<vector<string>> input vector, int numRows (0-based), int removedRows
void remove_invalid_entries(vector<vector<string>>&, int, int&);

string strip_spaces(string &input) {
    string outputString;
    int inputSize = input.length();
    for (int i = 0; i < inputSize; i++) {
        //if the scrutinized character is not a space, or is both preceded by a non-space and followed by a non-space
        if ( input[i] != ' ' || ( (i > 0 && input[i-1] != ' ') && (i < inputSize -1 && input[i+1] != ' ') ) )
            outputString += input[i]; //add it to the output
    }
    return outputString;
}

void remove_invalid_entries(vector<vector<string>> &input, int expectedEntrySize, int &invalidEntryCount) {
    int loopSize = input.size();
    for(int i = 0; i < loopSize; i++) {
        if (input[i].size() != (expectedEntrySize +1)) {
            input.erase(input.begin() + i);
            invalidEntryCount++;
        }
    }
}

/**********************\
 * Functions
\* ********************/
vector<string> generate_array(string &input, char delimeter) {
    vector<string> output;
    string cell;
    int loopSize = input.length();
    for(int i = 0; i < loopSize; i++) {
        if (input[i] == delimeter) {
            output.push_back(strip_spaces(cell));
            cell = "";
        } else {
            cell += input[i];
        }
    }
    return output;
}

vector<vector<string>> import_file(string &input) {
    vector<vector<string>> output;
    ifstream inputFile(input);
    string line;
    if (inputFile.is_open() == true) {
        while (getline(inputFile, line)) {
            output.push_back(generate_array(line, ','));
        }
        inputFile.close();
    } else {
        cout << "Error: file " << input << " could not be opened or does not exist." << endl;
    }
    return output;
}

vector<vector<string>> get_matches(vector<vector<string>> &input, string matchVal, int matchPos) {
    vector<vector<string>> output;
    int loopSize = input.size();
    for(int i = 0; i < loopSize; i++) {
        if (input[i][matchPos] == matchVal) {
            output.push_back(input[i]);
        }
    }
    return output;
}

void print_string_vector_vector (vector<vector<string>> &input) {
    int loopSize = input.size();
    for(int i = 0; i < loopSize; i++) {
        int innerLoopSize = input[i].size();
        for(int j = 0; j < innerLoopSize; j++) {
            cout << input[i][j];
            if (j < (innerLoopSize -1)) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

void print_string_vector (vector<string> &input) {
    int loopSize = input.size();
    for (int i = 0; i < loopSize; i++) {
        cout << input[i];
    }
    cout << endl;
}