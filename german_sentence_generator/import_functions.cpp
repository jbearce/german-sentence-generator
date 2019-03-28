#ifndef IMPORT_FUNCTIONS_CPP
#define IMPORT_FUNCTIONS_CPP
#include "import_functions.h"
using namespace std;

/****************************************************\
 * Functions. Details found in import_functions.h
\* **************************************************/
QString import_functions::strip_spaces(QString& input) {
    QString outputQString;
    int inputSize = input.length();
    for (int i = 0; i < inputSize; ++i) {
        //if the scrutinized character is not a space, or is both preceded by a non-space and followed by a non-space
        if ( input[i] != ' ' || ( (i > 0 && input[i-1] != ' ') && (i < inputSize -1 && input[i+1] != ' ') ) )
            outputQString += input[i]; //add it to the output
    }
    return outputQString;
}

vector<QString> import_functions::generate_array(QString& input, char delimeter) {
    vector<QString> output;
    QString cell;
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

vector<vector<QString>> import_functions::import_file(QString& input) {
    vector<vector<QString>> output;
    QString cell;
    QString rawLine;
    QString delimeter = ",";
    QFile file(input);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&file);
        while (!stream.atEnd()){
            rawLine = stream.readLine();
            vector<QString> line;
            int rawLineLength = rawLine.size();
            for(int i = 0; i < rawLineLength; ++i) {
                if (delimeter == rawLine[i]) {
                    line.push_back(strip_spaces(cell));
                    cell = "";
                } else {
                    cell += rawLine[i];
                }
            }
            output.push_back(line);
        }
    }
    file.close();
    return output;
}

std::vector<std::vector<QString>> import_functions::get_matches(vector<vector<QString>>& input, QString matchVal, int matchPos) {
    vector<vector<QString>> output;
    int loopSize = input.size();
    for(int i = 0; i < loopSize; ++i) {
        if (matchVal == input[i][matchPos]) {
            output.push_back(input[i]);
        }
    }
    return output;
}

QString import_functions::get_QString_vector_vector (vector<vector<QString>>& input) {
    int loopSize = input.size();
    QString output;
    for(int i = 0; i < loopSize; ++i) {
        int innerLoopSize = input[i].size();
        for(int j = 0; j < innerLoopSize; ++j) {
            output += input[i][j];
            if ((innerLoopSize -1) > j) {
                output += ", ";
            }
        }
        output += "\n";
    }
    return output;
}

QString import_functions::get_QString_vector_vector (std::vector<std::vector<QString>>& input, int col) {
    QString output;
    int numItems = input.size();
    for(int i = 0; i < numItems; ++i) {
        if (input[i].size() >= col){
            output += input[i][col] + "\n";
        }
    }
    return output;
}

void import_functions::remove_invalid_entries(vector<vector<QString>>& input, int expectedEntrySize, int& invalidEntryCount) {
    int loopSize = input.size();
    for(int i = 0; i < loopSize; ++i) {
        if ((expectedEntrySize +1) != input[i].size()) {
            input.erase(input.begin() + i);
            invalidEntryCount++;
        }
    }
}

QString import_functions::get_QString_vector (std::vector<QString>& input) {
    int loopSize = input.size();
    QString output;
    for (int i = 0; i < loopSize; ++i) {
        output += input[i] + "\n";
    }
    return output;
}

#endif // IMPORT_FUNCTIONS_CPP
