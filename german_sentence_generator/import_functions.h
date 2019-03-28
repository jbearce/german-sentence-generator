#ifndef IMPORT_FUNCTIONS_H
#define IMPORT_FUNCTIONS_H

#include "header.h"

/**********************\
 * Function Prototypes
\**********************/

namespace import_functions {

// strips spaces on the beginning/end of the input string, but not encapsulated spaces
QString strip_spaces(QString&);

// creates a simple vector from an input, split by a customizable delimeter.
// Spaces around delimeters are discarded.
std::vector<QString> generate_array(QString&, char);

//outputs a multidimensional vector of strings from an input file
std::vector<std::vector<QString>> import_file(QString&);

// outputs every row in the multidimensional input vector that matches the input parameters
// requres:
// - pointer to a multidimensional input vector (vector<vector<string>>)
// - value to search for (string)
// - column in vector array to search for match (zero-based)
std::vector<std::vector<QString>> get_matches(std::vector<std::vector<QString>>&, QString, int);

// outputs the contents of a 2-dimensional vector of strings to the console in CSV format.
// requires: vector<vector<string>> input val
QString get_QString_vector_vector (std::vector<std::vector<QString>>&);

//prints the specified column of each row in the QString 2D vector provided
QString get_QString_vector_vector (std::vector<std::vector<QString>>&, int);

// Takes a vector of vectors of strings and **directly modifies it** to delete malformed lines.
// This fixes any errors caused by attempting to access array positions that *should* be valid,
// but aren't due to garbage data.
// Inputs: vector<vector<string>> input vector, int numRows (0-based), int removedRows
void remove_invalid_entries(std::vector<std::vector<QString>>&, int, int&);

//prints all contents of the QString vector provided
QString get_QString_vector (std::vector<QString>&);

//prints all contents of the QString vector provided
QString get_QString_vector (std::vector<QString>&);

}

#endif // IMPORT_FUNCTIONS_H
