#ifndef SENTENCE_CPP
#define SENTENCE_CPP
#include "sentence.h"
#include "import_functions.h"
using namespace std;

vector<QString> sentence::choose_word(vector<vector<QString>> input) {
    int choice = rand() % input.size();
    vector<QString> wordData = input[choice];
    return wordData;
}

bool sentence::match_exists (QString val, vector<QString> searchRange) {
    int searchRangeSize = searchRange.size();
    for(int i = 0; i < searchRangeSize; ++i) {
        if (searchRange[i] == val) {
            return true;
        }
    }
    return false;
}

bool sentence::is_pronoun (QString& input, language& lang) {
    bool output = false;
    if (match_exists(input, lang.get_pronoun_list())) {
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

QString sentence::caseify(language& inLang, std::vector<QString> word, bool plural) {
    std::vector<std::vector<QString>> wordEndings = inLang.get_word_endings();
    if (wordEndings[0].size() > 0) {
        int loopSize = germanWordEndings[0].size();
        int genderNum = 0;
        for(int i = 0; i < loopSize; ++i) {
            if (germanWordEndings[0][i] == word[5]) {
                genderNum = i;
                break;
            }
        }

        if ("the" == word[2]) {
            return germanTheForms[wordCase+1][genderNum];
        } else if (!plural) {
            return word[2] + germanWordEndings[wordCase+1][genderNum];
        } else {
            return word[2] + germanWordEndings
        }

    } else {
        return "";
    }
}

void sentence::add_subject(language& input, language& keyLang) {
    input.set_subject_adjective(input, keyLang);
    input.set_subject_noun(input, keyLang);
}

void sentence::add_verb(language& input, language& keyLang) {
    QString output = "";
    if (!is_pronoun(keyLang.get_subject_noun()[3])) {
        output = word[6];

        // TODO: handle verb tenses other than present
    } else {
        // TODO: pronoun handling for all 6 cases
    }
    sentenceList.push_back(output);
}

void sentence::add_preposition(language& input, language& keyLang) {
    if (input.get_id() == keyLang.get_id()) {
        input.set_preposition(sentence::choose_word(input.get_preposition_list()));
    } else {
        input.set_preposition(sentence::get_match(keyLang.get_preposition(), input.get_preposition_list(), 0));
    }
}

void sentence::add_predicate(language& input, language& keyLang) {
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

vector<QString> sentence::get_match (vector<QString> inValue, vector<vector<QString>> searchRange, int searchCol) {
    vector<QString> output;
    int loopRange = searchRange.size();
    for(int i = 0; i < loopRange; ++i) {
        if (searchRange[i][searchCol] == inValue[searchCol]) {
            return searchRange[i];
        }
    }
    return output;
}

// Populate single sentence
void sentence::populate_sentence(language& inLang, language& keyLang) {
    sentence::add_subject(inLang, keyLang);
    sentence::add_verb(inLang, keyLang);
    sentence::add_preposition(inLang, keyLang);
    sentence::add_predicate(inLang, keyLang);
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
    germanImport.set_noun_list(import_functions::get_matches(germanWordList, "noun", 1));
    germanImport.set_noun_list(import_functions::remove_invalid_entries(germanImport.get_noun_list(), nounRowSize));

    germanImport.set_verb_list(import_functions::get_matches(germanWordList, "verb", 1));
    germanImport.set_verb_list(import_functions::remove_invalid_entries(germanImport.get_verb_list(), verbRowSize));

    germanImport.set_adjective_list(import_functions::get_matches(germanWordList, "adjective", 1));
    germanImport.set_adjective_list(import_functions::remove_invalid_entries(germanImport.get_adjective_list(), adjRowSize));

    germanImport.set_preposition_list(import_functions::get_matches(germanWordList, "preposition", 1));
    germanImport.set_preposition_list(import_functions::remove_invalid_entries(germanImport.get_preposition_list(), prepRowSize));

    std::cout << "German data loaded. ";
    int wordCount = 0;
    wordCount += germanImport.get_noun_list().size();;
    wordCount += germanImport.get_verb_list().size();
    wordCount += germanImport.get_adjective_list().size();
    wordCount += germanImport.get_preposition_list().size();
    cout << wordCount << " words imported." << endl;

    //english data import/modificaiton below:
    QString englishFileLocation = "data_files/english_list.csv";
    vector<vector<QString>> englishWordList = import_functions::import_file(englishFileLocation);
    invalidRowCount = 0;
    language englishImport;

    //divide import vectors into word types (stored in a struct). Also removes invalid data entries.
    englishImport.set_noun_list(import_functions::get_matches(englishWordList, "noun", 1));
    englishImport.set_noun_list(import_functions::remove_invalid_entries(englishImport.get_noun_list(), nounRowSize));

    englishImport.set_verb_list(import_functions::get_matches(englishWordList, "verb", 1));
    englishImport.set_verb_list(import_functions::remove_invalid_entries(englishImport.get_verb_list(), verbRowSize));

    englishImport.set_adjective_list(import_functions::get_matches(englishWordList, "adjective", 1));
    englishImport.set_adjective_list(import_functions::remove_invalid_entries(englishImport.get_adjective_list(), adjRowSize));

    englishImport.set_preposition_list(import_functions::get_matches(englishWordList, "preposition", 1));
    englishImport.set_preposition_list(import_functions::remove_invalid_entries(englishImport.get_preposition_list(), prepRowSize));

    cout << "English data loaded. ";
    wordCount = 0;
    wordCount += englishImport.get_noun_list().size();
    wordCount += englishImport.get_verb_list().size();
    wordCount += englishImport.get_adjective_list().size();
    wordCount += englishImport.get_preposition_list().size();
    cout << wordCount << " words imported." << endl;

    //store generated languages and construct parallel sentences
    german = std::move(germanImport);
    german.set_id("german");
    german.set_pronoun_list(germanPronounList);
    german.set_the_forms(germanTheForms);
    german.set_word_endings(germanWordEndings);

    english = std::move(englishImport);
    english.set_id("english");
    english.set_pronoun_list(englishPronounList);
    sentence::generate();
}

sentence::sentence(language& germanImport, language& englishImport) {
    german = std::move(germanImport);
    german.set_id("german");
    german.set_pronoun_list(germanPronounList);
    english = std::move(englishImport);
    english.set_id("english");
    english.set_pronoun_list(englishPronounList);
    sentence::generate();
}

sentence::~sentence() {}

void sentence::generate() {
    //tense = rand() % numTenses; //leave 0 for now. planned choices: present, past, or future (perfekt)
    tense = 0;
    bool plural = rand() % 1;
    germanSentenceList.clear();
    englishSentenceList.clear();

    german.set_subject_noun(sentence::choose_word(german.get_noun_list()));
    german.set_subject_adjective(sentence::choose_word(german.get_adjective_list()));
    german.set_verb(sentence::choose_word(german.get_verb_list()));
    german.set_preposition(sentence::choose_word(german.get_preposition_list()));
    german.set_predicate_noun(sentence::choose_word(german.get_noun_list()));
    german.set_predicate_adjective(sentence::choose_word(german.get_adjective_list()));

    english.set_subject_noun(sentence::get_match(german.get_subject_noun(), english.get_noun_list(), 0));
    english.set_subject_adjective(sentence::get_match(german.get_subject_adjective(), english.get_adjective_list(), 0));
    english.set_verb(sentence::get_match(german.get_verb(), english.get_verb_list(), 0));
    english.set_preposition(sentence::get_match(german.get_preposition(), english.get_preposition_list(), 0));
    english.set_predicate_noun(sentence::get_match(german.get_predicate_noun(), english.get_noun_list(), 0));
    english.set_predicate_adjective(sentence::get_match(german.get_predicate_adjective(), english.get_adjective_list(), 0));

    sentence::populate_sentence(german, german);
    sentence::populate_sentence(english, german);
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
    output += import_functions::get_QString_vector_vector(langWords.get_noun_list(), 3);
    output += import_functions::get_QString_vector_vector(langWords.get_adjective_list(), 2);
    output += import_functions::get_QString_vector_vector(langWords.get_verb_list(), 3);
    output += import_functions::get_QString_vector_vector(langWords.get_preposition_list(), 2);
    return output;
}

#endif // SENTENCE_CPP
