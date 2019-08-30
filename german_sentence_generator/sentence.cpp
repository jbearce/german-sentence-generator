#ifndef SENTENCE_CPP
#define SENTENCE_CPP
#include "sentence.h"
#include "import_functions.h"
using namespace std;

vector<QString> sentence::choose_word(vector<vector<QString>> input) {
    int choice = int(rand() % int(input.size()));
    vector<QString> wordData = input[u_long(choice)];
    return wordData;
}

bool sentence::match_exists (QString val, vector<QString> searchRange) {
    int searchRangeSize = int(searchRange.size());
    for(int i = 0; i < searchRangeSize; ++i) {
        if (searchRange[u_int(i)] == val) {
            return true;
        }
    }
    return false;
}

vector<QString> sentence::sentence_case (vector<QString>& input, QString punctuation) {
    vector<QString> cleanSentence;
    int inputSize = int(input.size());
    for(int i = 0; i < inputSize; ++i) {
        QString formattedOutput = input[u_long(i)];
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
    int loopRange = int(searchRange.size());
    for(int i = 0; i < loopRange; ++i) {
        if (searchRange[u_long(i)][u_long(searchCol)] == inValue[u_long(searchCol)]) {
            return searchRange[u_long(i)];
        }
    }
    return output;
}

void sentence::import_word_list(language& input, std::vector<std::vector<QString>> wordList) {
    //controls import file format requirements
    int nounRowSize = 5;
    int verbRowSize = 9;
    int adjRowSize = 2;
    int prepRowSize = 3;

    input.set_noun_list(import_functions::get_matches(wordList, "noun", 1));
    input.set_noun_list(import_functions::remove_invalid_entries(input.get_noun_list(), nounRowSize));

    input.set_verb_list(import_functions::get_matches(wordList, "verb", 1));
    input.set_verb_list(import_functions::remove_invalid_entries(input.get_verb_list(), verbRowSize));

    input.set_adjective_list(import_functions::get_matches(wordList, "adjective", 1));
    input.set_adjective_list(import_functions::remove_invalid_entries(input.get_adjective_list(), adjRowSize));

    input.set_preposition_list(import_functions::get_matches(wordList, "preposition", 1));
    input.set_preposition_list(import_functions::remove_invalid_entries(input.get_preposition_list(), prepRowSize));

    int wordCount = 0;
    wordCount += input.get_noun_list().size();;
    wordCount += input.get_verb_list().size();
    wordCount += input.get_adjective_list().size();
    wordCount += input.get_preposition_list().size();
    std::cout << wordCount << " words imported." << endl;
}

sentence::sentence() {
    srand(u_int(time(nullptr)));

    //create base import vectors
    QString germanFileLocation = "data_files/german_list.csv";
    vector<vector<QString>> germanWordList = import_functions::import_file(germanFileLocation);
    language germanImport;
    std::cout << "Loading German data... ";
    import_word_list(germanImport, germanWordList);

    //english data import/modificaiton below:
    QString englishFileLocation = "data_files/english_list.csv";
    vector<vector<QString>> englishWordList = import_functions::import_file(englishFileLocation);
    language englishImport;
    std::cout << "Loading English data... ";
    import_word_list(englishImport, englishWordList);

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
    german.clear_sentence();
    german.set_subject_noun(sentence::choose_word(german.get_noun_list()));
    german.set_subject_adjective(sentence::choose_word(german.get_adjective_list()));
    german.set_verb(sentence::choose_word(german.get_verb_list()));
    german.set_preposition(sentence::choose_word(german.get_preposition_list()));
    german.set_predicate_noun(sentence::choose_word(german.get_noun_list()));
    german.set_predicate_adjective(sentence::choose_word(german.get_adjective_list()));

    english.clear_sentence();
    english.set_subject_noun(sentence::get_match(german.get_subject_noun(), english.get_noun_list(), 0));
    english.set_subject_adjective(sentence::get_match(german.get_subject_adjective(), english.get_adjective_list(), 0));
    english.set_verb(sentence::get_match(german.get_verb(), english.get_verb_list(), 0));
    english.set_preposition(sentence::get_match(german.get_preposition(), english.get_preposition_list(), 0));
    english.set_predicate_noun(sentence::get_match(german.get_predicate_noun(), english.get_noun_list(), 0));
    english.set_predicate_adjective(sentence::get_match(german.get_predicate_adjective(), english.get_adjective_list(), 0));

    german.build_sentence_list();
    english.build_sentence_list();
}

QString sentence::output(QString langID) {
    language inLang = langList.get_language(langID);
    std::vector<QString>sentenceList = inLang.sentenceList;
    QString outputValue;
    sentenceList = sentence::sentence_case(sentenceList, ".");
    int sentenceListSize = int(sentenceList.size());
    for(int i = 0; i < sentenceListSize; ++i) {
       outputValue += sentenceList[u_int(i)];
       outputValue += " ";
    }
    return outputValue;
}

QString sentence::get_words(QString langID) {
    language langWords = langList.get_language(langID);
    QString output;

    output += import_functions::get_QString_vector_vector(langWords.get_noun_list(), 3);
    output += import_functions::get_QString_vector_vector(langWords.get_adjective_list(), 2);
    output += import_functions::get_QString_vector_vector(langWords.get_verb_list(), 3);
    output += import_functions::get_QString_vector_vector(langWords.get_preposition_list(), 2);
    return output;
}

#endif // SENTENCE_CPP
