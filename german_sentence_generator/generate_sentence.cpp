#ifndef HEADER_H
#define HEADER_H
#include "header.h"
#endif
#include "sentence.cpp"
using namespace std;
sentence generate_sentence() {
    srand(time(NULL));
    
    //controls import file format requirements
    int invalidRowCount = 0;
    int nounRowSize = 5;
    int verbRowSize = 9;
    int adjRowSize = 2;
    int prepRowSize = 3;

    //create base import vectors
    QString germanFileLocation = "data_files/german_list.csv";
    vector<vector<QString>> germanWordList = import_file(germanFileLocation);

    cout << "germanWordsList has " << germanWordList.size() << " lines.";

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
    cout << german.nouns.size() << " nouns found." << endl;
    cout << german.verbs.size() << " verbs found." << endl;
    cout << german.adjectives.size() << " adjectives found." << endl;
    cout << german.prepositions.size() << " prepositions found." << endl;

    //english data import/modificaiton below: 
    QString englishFileLocation = "data_files/english_list.csv";
    vector<vector<QString>> englishWordList = import_file(englishFileLocation);
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

    cout << "English data imported. Input data had " << invalidRowCount << " invalid entries." << endl;
    cout << english.nouns.size() << " nouns found." << endl;
    cout << english.verbs.size() << " verbs found." << endl;
    cout << english.adjectives.size() << " adjectives found." << endl;
    cout << english.prepositions.size() << " prepositions found." << endl;

    //store it all in a single object
    sentence mySentence { german, english };
    return mySentence;
}
