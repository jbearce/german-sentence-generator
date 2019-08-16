#ifndef SENTENCE_H
#define SENTENCE_H
#include "header.h"

/******************************
 * Takes input data and processes it into parallel English and German sentences
 * ***************************/
class sentence {
    private:

        language german;
        language english;

        int tense = 0;
        int numTenses = 3; //change this if more tenses are added

        enum sentenceCases { nominative, accusative, dative, genetive };

        enum germanGenders { der, die, das };
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

        enum englishGenders { masculine, feminine, neuter };
        std::vector<QString> englishPronounList = { "I", "you", "he", "she", "it", "we", "y'all", "they" };

        //package of sentence components, built by build_sentence()
        struct singleSentence {
            std::vector<QString> sNoun;
            std::vector<QString> sAdjective;
            std::vector<QString> verb;
            std::vector<QString> preposition;
            std::vector<QString> pNoun;
            std::vector<QString> pAdjective;
        };
        singleSentence germanSentence;
        singleSentence englishSentence;
        std::vector<QString> germanSentenceList;
        std::vector<QString> englishSentenceList;

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

        /***********************************
         * Input a word. Checks whether it's a pronoun. Supports English and German.
         * ********************************/
        bool is_pronoun (QString&, language&);

        /***********************************
         * Takes a QString value and converts it to the correct integer position in the array
         * Input must be one of: "nominative", "accusative", "dative", or "genetive"
         * ********************************/
        int case_to_int(QString&);

        /***********************************
         * Modifies the input word to use the correct case (nominative/accusative/dative/genetive)
         * ********************************/
        QString caseify(language&, std::vector<QString>, bool);

        /***********************************
         * Adds the subject noun grouping as a component to an instance of language
         * ********************************/
        void add_subject(language& inLang, language& keyLang);

        /*************************************
         * Adds the verb as a component to an instance of language
         * **********************************/
        void add_verb(language& inLang, language& keyLang);

        /*************************************
         * Adds the preposition as a component to an instance of language
         * **********************************/
        void add_preposition(language& inLang, language& keyLang);

        /************************************
         * Adds the predicate noun grouping as a component to an instance of language
         * *********************************/
        void add_predicate(language& inLang, language& keyLang);

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

        /************************************
         * NEW: populates the sentence components for the language.
         * Inputs: language& input, language& key
         * If input.name == key.name, a random sentence is generated.
         * Depends on add_subject, add_verb, etc., and their dependencies.
         * **********************************/
        void populate_sentence(language&, language&);

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
        QString output(int);

        /************************************
        * Returns a list of available words for the given language (int)
        * 0 = German; 1 = English
        * ***********************************/
        QString getWords(int);
};
#endif //SENTENCE_H
