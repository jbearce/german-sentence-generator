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
        std::vector<QString> choose_word(std::vector<std::vector<QString>>&);

        /***********************************
        * Check whether the given input QString exists within the search range.
        ************************************/
        bool match_exists (QString&, std::vector<QString>&);

        /***********************************
         * Input a word. Checks whether it's a pronoun. Supports English and German.
         * ********************************/
        bool is_pronoun (QString&);

        /***********************************
         * Takes a QString value and converts it to the correct integer position in the array
         * Input must be one of: "nominative", "accusative", "dative", or "genetive"
         * ********************************/
        int case_to_int(QString&);

        /***********************************
         * Modifies the input word to use the correct case (nominative/accusative/dative/genetive)
         * ********************************/
        QString caseify(QString, QString&, int, bool, int);

        /***********************************
         * Adds the subject noun grouping as a component to germanSentenceList
         * ********************************/
        void add_subject(std::vector<QString>&, std::vector<QString>&, std::vector<QString>&, int);

        /*************************************
         * Adds the verb as a component to germanSentenceList
         * **********************************/
        void add_verb(std::vector<QString>&, std::vector<QString>&, std::vector<QString>&, int&, int);

        /*************************************
         * Adds the preposition the germanSentenceList
         * **********************************/
        void add_preposition(std::vector<QString>&, std::vector<QString>&, int);

        /************************************
         * Adds the predicate noun grouping as a component to germanSentenceList
         * *********************************/
        void add_predicate(std::vector<QString>&, std::vector<QString>&, std::vector<QString>&, std::vector<QString>&, int&, int);

        /************************************
        * Takes the vector components of a sentence and converts it to sentence format
        * eg: "The, big, dog, chased, the, yellow, cat.";
        * ***********************************/
        std::vector<QString> sentence_case (std::vector<QString>&, QString);

        /************************************
         * Returns the row in a 2D vector that contains
         * the specified word in the specified column
         * *********************************/
        std::vector<QString> get_match (std::vector<QString>&, std::vector<std::vector<QString>>&, int);

    public:

        /**********************************
         * Imports word data from CSVs and generates a sentence from it
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
