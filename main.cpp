#include "header.h"

int main() {
    srand(time(NULL));
    
    //controls import file format requirements
    int invalidRowCount = 0;
    int nounRowSize = 4;
    int verbRowSize = 9;
    int adjRowSize = 2;
    int prepRowSize = 3;

    //create base import vectors
    string germanFileLocation = "data_files/german_list.csv";
    vector<vector<string>> germanWordList = import_file(germanFileLocation);

    language german;

    //divide import vectors into word types (stored in a struct). Also removes invalid data entries.
    german.nouns = get_matches(germanWordList, "noun", 1);
    remove_invalid_entries(german.nouns, nounRowSize, invalidRowCount);
    german.verbs = get_matches(germanWordList, "verb", 1);
    remove_invalid_entries(german.verbs, verbRowSize, invalidRowCount);
    german.adjectives = get_matches(germanWordList, "adjective", 1);
    remove_invalid_entries(german.adjectives, adjRowSize, invalidRowCount);
    german.prepositions = get_matches(germanWordList, "preposition", 1);
    remove_invalid_entries(german.prepositions, prepRowSize, invalidRowCount);

    cout << "German data imported. Input data had " << invalidRowCount << " invalid entries." << endl;
    cout << "nouns are: " << endl;
    print_string_vector_vector(german.nouns);
    cout << "verbs are: " << endl;
    print_string_vector_vector(german.verbs);
    cout << "adjectives are: " << endl;
    print_string_vector_vector(german.adjectives);
    cout << "prepositions are: " << endl;
    print_string_vector_vector(german.prepositions);

    //english data import/modificaiton below: 
    string englishFileLocation = "data_files/english_list.csv";
    vector<vector<string>> englishWordList = import_file(englishFileLocation);
    invalidRowCount = 0;
    language english;

    //divide import vectors into word types (stored in a struct). Also removes invalid data entries.
    english.nouns = get_matches(englishWordList, "noun", 1);
    remove_invalid_entries(english.nouns, nounRowSize, invalidRowCount);
    english.verbs = get_matches(englishWordList, "verb", 1);
    remove_invalid_entries(english.verbs, verbRowSize, invalidRowCount);
    english.adjectives = get_matches(englishWordList, "adjective", 1);
    remove_invalid_entries(english.adjectives, adjRowSize, invalidRowCount);
    english.prepositions = get_matches(englishWordList, "preposition", 1);
    remove_invalid_entries(english.prepositions, prepRowSize, invalidRowCount);

    //store it all in a single object
    sentence mySentence { german, english };
    string input;

    cout << "English data imported. Input data had " << invalidRowCount << " invalid entries." << endl;
    cout << "nouns are: " << endl;
    print_string_vector_vector(english.nouns);
    cout << "verbs are: " << endl;
    print_string_vector_vector(english.verbs);
    cout << "adjectives are: " << endl;
    print_string_vector_vector(english.adjectives);
    cout << "prepositions are: " << endl;
    print_string_vector_vector(english.prepositions);

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