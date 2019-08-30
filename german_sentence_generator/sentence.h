#ifndef SENTENCE_H
#define SENTENCE_H
#include "header.h"
#include "language.h"
#include "rosettastone.h"

/******************************
 * Takes input data and processes it into parallel English and German sentences
 * ***************************/
class sentence {
    private:

        language german;
        language english;

        rosettaStone langList{german, english};

        std::vector<QString> germanPronounList = { "ich", "du", "er", "sie", "es", "wir", "ihr", "Sie" };
        std::vector<std::vector<QString>> germanWordEndings = {
            { "masculine",  "feminine", "neuter",   "plural" },
            { "e",          "e",        "e",        "en" },
            { "en",         "e",        "e",        "en" },
            { "en",         "en",       "en",       "en" },
            { "en",         "en",       "en",       "en" }
        };
        std::vector<std::vector<QString>> germanTheForms = {
            { "masculine",  "feminine", "neuter",   "plural" },
            { "der",        "die",      "das",      "die" },
            { "den",        "die",      "das",      "die" },
            { "dem",        "der",      "dem",      "den" },
            { "des",        "der",      "des",      "der" }
        };

        std::vector<QString> englishPronounList = { "I", "you", "he", "she", "it", "we", "y'all", "they" };

        /***********************************
        * Chooses a word for the input list. The list should only contain
        * words you are okay choosing from. Use the get_matches()
        * helper function in import_functions.h to get a workable sublist
        * ***********************************/
        std::vector<QString> choose_word(std::vector<std::vector<QString>>);

        /***********************************
        * Check whether the given input QString exists within the search range.
        ************************************/
        bool match_exists (QString, std::vector<QString>);

        /************************************
        * Takes the vector components of a sentence and converts it to sentence format
        * eg: "The, big, dog, chased, the, yellow, cat.";
        * ***********************************/
        std::vector<QString> sentence_case (std::vector<QString>&, QString);

        /************************************
         * Returns the row in a 2D vector that contains
         * the specified word in the specified column
         * *********************************/
        std::vector<QString> get_match (std::vector<QString>, std::vector<std::vector<QString>>, int);

        void import_word_list(language& input, std::vector<std::vector<QString>> wordList);

    public:

        /**********************************
         * Imports word data from CSVs and generates a sentence from it. Relise on the import functions.
         * *******************************/
        sentence();

        /**********************************
         * Constructs a sentence object from the desired word lists.
         * *******************************/
        sentence(language&, language&);

        ~sentence();

        /************************************
        * Generates a sentence that can then be displayed/used with other functions.
        * NOTE: Running this deletes the stored word. Only run this when a new sentence is needed.
        * **********************************/
        void generate();

        /************************************
        * Writes the generated sentence to the terminal
        * input: vector<QString> sentenceList -- input a {lang}SentenceList
        * ***********************************/
        QString output(QString);

        /************************************
        * Returns a list of available words for the given language (int)
        * 0 = German; 1 = English
        * ***********************************/
        QString get_words(QString);
};
#endif //SENTENCE_H
