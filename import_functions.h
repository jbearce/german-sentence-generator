/**********************\
 * Structs & Globals  *
\**********************/
struct language {
    std::vector<std::vector<std::string>> nouns;
    std::vector<std::vector<std::string>> verbs;
    std::vector<std::vector<std::string>> adjectives;
    std::vector<std::vector<std::string>> prepositions;
};

/**********************\
 * Function Prototypes
\**********************/
// strips spaces on the beginning/end of the input string, but not encapsulated spaces
string strip_spaces(std::string&);

// creates a simple vector from an input, split by a customizable delimeter. 
// Spaces around delimeters are discarded.
std::vector<std::string> generate_array(std::string&, char);

//outputs a multidimensional vector of strings from an input file
std::vector<std::vector<std::string>> import_file(std::string&);

// outputs every row in the multidimensional input vector that matches the input parameters
// requres: 
// - pointer to a multidimensional input vector (vector<vector<string>>)
// - value to search for (string)
// - column in vector array to search for match (zero-based)
std::vector<std::vector<std::string>> get_matches(std::vector<std::vector<std::string>>&, std::string, int);

// outputs the contents of a 2-dimensional vector of strings to the console in CSV format.
// requires: vector<vector<string>> input val
void print_string_vector_vector (std::vector<std::vector<std::string>>&);

// Takes a vector of vectors of strings and **directly modifies it** to delete malformed lines.
// This fixes any errors caused by attempting to access array positions that *should* be valid,
// but aren't due to garbage data.
// Inputs: vector<vector<string>> input vector, int numRows (0-based), int removedRows
void remove_invalid_entries(std::vector<std::vector<std::string>>&, int, int&);
