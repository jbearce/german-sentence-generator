#include "header.h"

int main() {
    srand(time(NULL));

    //create base import vectors
    string germanFileLocation = "data_files/german_list.csv";
    vector<vector<string>> germanWordList = import_file(germanFileLocation);
    int invalidRowCount = 0;
    int gNounRowSize = 4;
    int gVerbRowSize = 9;
    int gAdjRowSize = 2;
    int gPrepRowSize = 3;

    //divide import vectors into word types
    vector<vector<string>> germanNouns = get_matches(germanWordList, "noun", 1);
    remove_invalid_entries(germanNouns, gNounRowSize, invalidRowCount);
    vector<vector<string>> germanVerbs = get_matches(germanWordList, "verb", 1);
    remove_invalid_entries(germanVerbs, gVerbRowSize, invalidRowCount);
    vector<vector<string>> germanAdjectives = get_matches(germanWordList, "adjective", 1);
    remove_invalid_entries(germanAdjectives, gAdjRowSize, invalidRowCount);
    vector<vector<string>> germanPrepositions = get_matches(germanWordList, "preposition", 1);
    remove_invalid_entries(germanPrepositions, gPrepRowSize, invalidRowCount);

    sentence germanSentence { germanNouns, germanVerbs, germanAdjectives, germanPrepositions };
    string input;

    cout << "Input data had " << invalidRowCount << " invalid entries." << endl;
    cout << "nouns are: " << endl;
    print_string_vector_vector(germanNouns);
    cout << "verbs are: " << endl;
    print_string_vector_vector(germanVerbs);
    cout << "adjectives are: " << endl;
    print_string_vector_vector(germanAdjectives);
    cout << "prepositions are: " << endl;
    print_string_vector_vector(germanPrepositions);

    while (input != "no" && input != "n") {
        cout << "Generate sentence?" << endl;
        cin >> input;
        if (input == "no" || input == "n" || input == "y" || input == "yes") {
        } else {
            cout << "Invalid input: y|n" << endl;
        }
        if (input == "y" || input == "yes") {
            germanSentence.generate();
            germanSentence.output();
        }
    }
    return 0;
}