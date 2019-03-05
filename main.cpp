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

    cout << "German data imported. Input data had " << invalidRowCount << " invalid entries." << endl;
    cout << "nouns are: " << endl;
    print_string_vector_vector(germanNouns);
    cout << "verbs are: " << endl;
    print_string_vector_vector(germanVerbs);
    cout << "adjectives are: " << endl;
    print_string_vector_vector(germanAdjectives);
    cout << "prepositions are: " << endl;
    print_string_vector_vector(germanPrepositions);

    //english data import/modificaiton below: 
    string englishFileLocation = "data_files/english_list.csv";
    vector<vector<string>> englishWordList = import_file(englishFileLocation);
    invalidRowCount = 0;
    int eNounRowSize = 4;
    int eVerbRowSize = 9;
    int eAdjRowSize = 2;
    int ePrepRowSize = 3;

     //divide import vectors into word types
    vector<vector<string>> englishNouns = get_matches(englishWordList, "noun", 1);
    remove_invalid_entries(englishNouns, eNounRowSize, invalidRowCount);
    vector<vector<string>> englishVerbs = get_matches(englishWordList, "verb", 1);
    remove_invalid_entries(englishVerbs, eVerbRowSize, invalidRowCount);
    vector<vector<string>> englishAdjectives = get_matches(englishWordList, "adjective", 1);
    remove_invalid_entries(englishAdjectives, eAdjRowSize, invalidRowCount);
    vector<vector<string>> englishPrepositions = get_matches(englishWordList, "preposition", 1);
    remove_invalid_entries(englishPrepositions, ePrepRowSize, invalidRowCount);

    //store it all in a single object
    sentence mySentence { germanNouns, germanVerbs, germanAdjectives, germanPrepositions, 
                          englishNouns, englishVerbs, englishAdjectives, englishPrepositions };
    string input;

    cout << "English data imported. Input data had " << invalidRowCount << " invalid entries." << endl;
    cout << "nouns are: " << endl;
    print_string_vector_vector(englishNouns);
    cout << "verbs are: " << endl;
    print_string_vector_vector(englishVerbs);
    cout << "adjectives are: " << endl;
    print_string_vector_vector(englishAdjectives);
    cout << "prepositions are: " << endl;
    print_string_vector_vector(englishPrepositions);

    while ("n" != input) {
        cout << "Generate sentence?" << endl;
        cin >> input;
        if ("y" == input || "n" == input) {
        } else {
            cout << "Invalid input: y|n" << endl;
        }
        if ("y" == input) {
            mySentence.generate();
            mySentence.output(0);
            mySentence.output(1);
        }
    }
    return 0;
}