#ifndef SENTENCE_CPP
#define SENTENCE_CPP
#include "sentence.h"
#include "import_functions.h"
using namespace std;

vector<QString> sentence::choose_word(vector<vector<QString>>& input) {
    int choice = rand() % input.size();
    vector<QString> wordData = input[choice];
    return wordData;
}

bool sentence::match_exists (QString& val, vector<QString>& searchRange) {
    int searchRangeSize = searchRange.size();
    for(int i = 0; i < searchRangeSize; ++i) {
        if (searchRange[i] == val) {
            return true;
        }
    }
    return false;
}

bool sentence::is_pronoun (QString& input) {
    bool output = false;
    if (match_exists(input, germanPronounList) || match_exists(input, englishPronounList)) {
        output = true;
    }
    return output;
}

int sentence::case_to_int(QString& input) {
    if ("nominative" == input) {
        return 0;
    } else if ("accusative" == input) {
        return 1;
    } else if ("dative" == input) {
        return 2;
    } else if ("genetive" == input) {
        return 3;
    }
    return 0;
}

QString sentence::caseify(QString baseWord, QString& gender, int wordCase, bool plural, int language) {
    if (0 == language) {
        vector<vector<QString>> germanWordEndings = {
            { "masculine",  "feminine", "neuter",   "plural" },
            { "e",          "e",        "e",        "en" },
            { "en",         "e",        "e",        "en" },
            { "en",         "en",       "en",       "en" },
            { "en",         "en",       "en",       "en" }
        };
        vector<vector<QString>> germanTheForms = {
            { "masculine",  "feminine", "neuter",   "plural" },
            { "der",        "die",      "das",      "die" },
            { "den",        "die",      "das",      "die" },
            { "dem",        "der",      "dem",      "den" },
            { "des",        "der",      "des",      "der" }
        };
        int loopSize = germanWordEndings[0].size();
        int genderNum = 0;
        for(int i = 0; i < loopSize; ++i) {
            if (germanWordEndings[0][i] == gender) {
                genderNum = i;
                break;
            }
        }
        if ("the" == baseWord) {
            return germanTheForms[wordCase+1][genderNum];
        } else {
            return baseWord + germanWordEndings[wordCase+1][genderNum];
        }

    } else if (1 == language) {
        return baseWord;
    } else {
        return "";
    }
}

void sentence::add_subject(vector<QString>& sentenceList, vector<QString>& word, vector<QString>& wordAdjective, int language) {
    sentenceList.push_back(sentence::caseify("the", word[5], 0, false, language));
    sentenceList.push_back(sentence::caseify(wordAdjective[2], word[5], 0, false, language));
    sentenceList.push_back(word[3]);
}

void sentence::add_verb(vector<QString>& sentenceList, vector<QString>& word, vector<QString>& subjectNoun, int& tense, int language) {
    QString output = "";
    if (!is_pronoun(subjectNoun[3])) {
        output = word[6];

        // TODO: handle verb tenses other than present
    } else {
        // TODO: pronoun handling for all 6 cases
    }
    sentenceList.push_back(output);
}

void sentence::add_preposition(vector<QString>& sentenceList, vector<QString>& word, int language) {
    sentenceList.push_back(word[2]);
}

void sentence::add_predicate(vector<QString>& sentenceList, vector<QString>& word, vector<QString>& wordAdjective, vector<QString>& wordPreposition, int& tense, int language) {
    sentenceList.push_back(sentence::caseify("the", word[5], case_to_int(wordPreposition[3]), false, language));
    sentenceList.push_back(sentence::caseify(wordAdjective[2], word[5], case_to_int(wordPreposition[3]), false, language));
    sentenceList.push_back(word[3]);
}

vector<QString> sentence::sentence_case (vector<QString>& input, QString punctuation) {
    vector<QString> cleanSentence;
    int inputSize = input.size();
    for(int i = 0; i < inputSize; ++i) {
        QString formattedOutput = input[i];
        if (0 == i) {
            formattedOutput[0] = formattedOutput[0].toUpper();
        } else if ((inputSize - 1) == i) {
            formattedOutput += punctuation;
        }
        cleanSentence.push_back(formattedOutput);
    }
    return cleanSentence;
}

vector<QString> sentence::get_match (vector<QString>& inValue, vector<vector<QString>>& searchRange, int searchCol) {
    vector<QString> output;
    int loopRange = searchRange.size();
    for(int i = 0; i < loopRange; ++i) {
        if (searchRange[i][searchCol] == inValue[searchCol]) {
            return searchRange[i];
        }
    }
    return output;
}

sentence::sentence() {
    srand(time(NULL));

    //controls import file format requirements
    int invalidRowCount = 0;
    int nounRowSize = 5;
    int verbRowSize = 9;
    int adjRowSize = 2;
    int prepRowSize = 3;

    //create base import vectors
    QString germanFileLocation = "data_files/german_list.csv";
    vector<vector<QString>> germanWordList = import_functions::import_file(germanFileLocation);

    language germanImport;

    //divide import vectors into word types (stored in a struct). Also removes invalid data entries.
    germanImport.nouns = import_functions::get_matches(germanWordList, "noun", 1);
    import_functions::remove_invalid_entries(germanImport.nouns, nounRowSize, invalidRowCount);
    germanImport.verbs = import_functions::get_matches(germanWordList, "verb", 1);
    import_functions::remove_invalid_entries(germanImport.verbs, verbRowSize, invalidRowCount);
    germanImport.adjectives = import_functions::get_matches(germanWordList, "adjective", 1);
    import_functions::remove_invalid_entries(germanImport.adjectives, adjRowSize, invalidRowCount);
    germanImport.prepositions = import_functions::get_matches(germanWordList, "preposition", 1);
    import_functions::remove_invalid_entries(germanImport.prepositions, prepRowSize, invalidRowCount);

    cout << "German data imported. Input data had " << invalidRowCount << " invalid entries." << endl;
    int wordCount = 0;
    wordCount += germanImport.nouns.size();;
    wordCount += germanImport.verbs.size();
    wordCount += germanImport.adjectives.size();
    wordCount += germanImport.prepositions.size();
    cout << wordCount << " words imported." << endl;

    //english data import/modificaiton below:
    QString englishFileLocation = "data_files/english_list.csv";
    vector<vector<QString>> englishWordList = import_functions::import_file(englishFileLocation);
    invalidRowCount = 0;
    language englishImport;

    //divide import vectors into word types (stored in a struct). Also removes invalid data entries.
    englishImport.nouns = import_functions::get_matches(englishWordList, "noun", 1);
    import_functions::remove_invalid_entries(englishImport.nouns, nounRowSize, invalidRowCount);
    englishImport.verbs = import_functions::get_matches(englishWordList, "verb", 1);
    import_functions::remove_invalid_entries(englishImport.verbs, verbRowSize, invalidRowCount);
    englishImport.adjectives = import_functions::get_matches(englishWordList, "adjective", 1);
    import_functions::remove_invalid_entries(englishImport.adjectives, adjRowSize, invalidRowCount);
    englishImport.prepositions = import_functions::get_matches(englishWordList, "preposition", 1);
    import_functions::remove_invalid_entries(englishImport.prepositions, prepRowSize, invalidRowCount);

    cout << "English data imported. Input data had " << invalidRowCount << " invalid entries." << endl;
    wordCount = 0;
    wordCount += englishImport.nouns.size();;
    wordCount += englishImport.verbs.size();
    wordCount += englishImport.adjectives.size();
    wordCount += englishImport.prepositions.size();
    cout << wordCount << " words imported." << endl;

    //store it all in a single object
    german = germanImport;
    english = englishImport;
    sentence::generate();
}

sentence::sentence(language& germanImport, language& englishImport) {
    german = germanImport;
    english = englishImport;
}

sentence::~sentence() {}

void sentence::generate() {
    //tense = rand() % numTenses; //choose present, past, or future (perfekt)
    tense = 0;
    germanSentenceList.clear();
    englishSentenceList.clear();

    germanSentence.sNoun = sentence::choose_word(german.nouns);
    germanSentence.sAdjective = sentence::choose_word(german.adjectives);
    germanSentence.verb = sentence::choose_word(german.verbs);
    germanSentence.preposition = sentence::choose_word(german.prepositions);
    germanSentence.pNoun = sentence::choose_word(german.nouns);
    germanSentence.pAdjective = sentence::choose_word(german.adjectives);

    englishSentence.sNoun = sentence::get_match(germanSentence.sNoun, english.nouns, 0);
    englishSentence.sAdjective = sentence::get_match(germanSentence.sAdjective, english.adjectives, 0);
    englishSentence.verb = sentence::get_match(germanSentence.verb, english.verbs, 0);
    englishSentence.preposition = sentence::get_match(germanSentence.preposition, english.prepositions, 0);
    englishSentence.pNoun = sentence::get_match(germanSentence.pNoun, english.nouns, 0);
    englishSentence.pAdjective = sentence::get_match(germanSentence.pAdjective, english.adjectives, 0);

    // Populate German sentence list
    sentence::add_subject(germanSentenceList, germanSentence.sNoun, germanSentence.sAdjective, 0);
    sentence::add_verb(germanSentenceList, germanSentence.verb, germanSentence.sNoun, tense, 0);
    sentence::add_preposition(germanSentenceList, germanSentence.preposition, 0);
    sentence::add_predicate(germanSentenceList, germanSentence.pNoun, germanSentence.pAdjective, germanSentence.preposition, tense, 0);

    // Populate English sentence list
    sentence::add_subject(englishSentenceList, englishSentence.sNoun, englishSentence.sAdjective, 1);
    sentence::add_verb(englishSentenceList, englishSentence.verb, englishSentence.sNoun, tense, 1);
    sentence::add_preposition(englishSentenceList, englishSentence.preposition, 1);
    sentence::add_predicate(englishSentenceList, englishSentence.pNoun, englishSentence.pAdjective, englishSentence.preposition, tense, 1);

}

QString sentence::output(int language) {
    QString outputValue;
    vector<QString>sentenceList;
    if (0 == language) {
        sentenceList = germanSentenceList;
    } else if (1 == language) {
        sentenceList = englishSentenceList;
    }

    sentenceList = sentence::sentence_case(sentenceList, ".");
    int sentenceListSize = sentenceList.size();
    for(int i = 0; i < sentenceListSize; ++i) {
       outputValue += sentenceList[i];
       outputValue += " ";
    }
    return outputValue;
}

QString sentence::getWords(int lang) {
    language langWords;
    QString output;
    if (0 == lang) {
        langWords = german;
    } else if (1 == lang) {
        langWords = english;
    }
    output += import_functions::get_QString_vector_vector(langWords.nouns, 3);
    output += import_functions::get_QString_vector_vector(langWords.adjectives, 2);
    output += import_functions::get_QString_vector_vector(langWords.verbs, 3);
    output += import_functions::get_QString_vector_vector(langWords.prepositions, 2);
    return output;
}

#endif // SENTENCE_CPP
