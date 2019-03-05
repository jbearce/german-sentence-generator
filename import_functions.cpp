#include "import_functions.h"
using namespace std;

/****************************************************\
 * Functions. Details found in import_functions.h
\* **************************************************/
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

vector<string> generate_array(string &input, char delimeter) {
    vector<string> output;
    string cell;
    int loopSize = input.length();
    for(int i = 0; i < loopSize; ++i) {
        if (delimeter == input[i]) {
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
    if (inputFile.is_open()) {
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
    for(int i = 0; i < loopSize; ++i) {
        if (matchVal == input[i][matchPos]) {
            output.push_back(input[i]);
        }
    }
    return output;
}

void print_string_vector_vector (vector<vector<string>> &input) {
    int loopSize = input.size();
    for(int i = 0; i < loopSize; ++i) {
        int innerLoopSize = input[i].size();
        for(int j = 0; j < innerLoopSize; ++j) {
            cout << input[i][j];
            if ((innerLoopSize -1) > j) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

void remove_invalid_entries(vector<vector<string>> &input, int expectedEntrySize, int &invalidEntryCount) {
    int loopSize = input.size();
    for(int i = 0; i < loopSize; ++i) {
        if ((expectedEntrySize +1) != input[i].size()) {
            input.erase(input.begin() + i);
            invalidEntryCount++;
        }
    }
}

void print_string_vector (vector<string> &input) {
    int loopSize = input.size();
    for (int i = 0; i < loopSize; ++i) {
        cout << input[i];
    }
    cout << endl;
}