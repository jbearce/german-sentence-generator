#include "import_functions.h"
using namespace std;

/****************************************************\
 * Functions. Details found in import_functions.h
\* **************************************************/
QString strip_spaces(QString& input) {
    QString outputQString;
    int inputSize = input.length();
    for (int i = 0; i < inputSize; i++) {
        //if the scrutinized character is not a space, or is both preceded by a non-space and followed by a non-space
        if ( input[i] != ' ' || ( (i > 0 && input[i-1] != ' ') && (i < inputSize -1 && input[i+1] != ' ') ) )
            outputQString += input[i]; //add it to the output
    }
    return outputQString;
}

vector<QString> generate_array(QString& input, char delimeter) {
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

vector<vector<QString>> import_file(QString& input) {
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
        cout << "File " << input.toStdString() << " was opened successfully." << endl;
    }
    file.close();
    return output;
}

std::vector<std::vector<QString>> get_matches(vector<vector<QString>>& input, QString matchVal, int matchPos) {
    vector<vector<QString>> output;
    int loopSize = input.size();
    for(int i = 0; i < loopSize; ++i) {
        if (matchVal == input[i][matchPos]) {
            output.push_back(input[i]);
        }
    }
    return output;
}

void print_QString_vector_vector (vector<vector<QString>>& input) {
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
}

void remove_invalid_entries(vector<vector<QString>>& input, int expectedEntrySize, int& invalidEntryCount) {
    int loopSize = input.size();
    for(int i = 0; i < loopSize; ++i) {
        if ((expectedEntrySize +1) != input[i].size()) {
            input.erase(input.begin() + i);
            invalidEntryCount++;
        }
    }
}

QString print_QString_vector (std::vector<QString>& input) {
    int loopSize = input.size();
    QString output;
    for (int i = 0; i < loopSize; ++i) {
        output += input[i];
    }
    return output;
}
