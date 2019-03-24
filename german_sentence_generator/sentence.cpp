#include "sentence.h"
using namespace std;

//repackage words into a class `sentence`
class sentence {
    private:

        language german;
        language english;

        int tense = 0;
        int numTenses = 3; //change this if more tenses are added

        enum sentenceCases { nominative, accusative, dative, genetive };

        enum germanGenders { der, die, das };
        vector<QString> germanPronounList = { "ich", "du", "er", "sie", "es", "wir", "ihr", "Sie" };

        enum englishGenders { masculine, feminine, neuter };
        vector<QString> englishPronounList = { "I", "you", "he", "she", "it", "we", "y'all", "they" };

        //package of sentence components, built by build_sentence()
        struct singleSentence {
            vector<QString> sNoun;
            vector<QString> sAdjective;
            vector<QString> verb;
            vector<QString> preposition;
            vector<QString> pNoun;
            vector<QString> pAdjective;
        };
        singleSentence germanSentence;
        singleSentence englishSentence;
        vector<QString> germanSentenceList;
        vector<QString> englishSentenceList;

        // Chooses a word for the input list. The list should only contain
        // words you are okay choosing from. Use the get_matches() 
        // helper function in import_functions.h to get a workable sublist
        vector<QString> choose_word(vector<vector<QString>>& input) {
            int choice = rand() % input.size();
            vector<QString> wordData = input[choice];
            return wordData;
        }

        // Check whether the given input QString exists within the search range.
        bool match_exists (QString& val, vector<QString>& searchRange) {
            int searchRangeSize = searchRange.size();
            for(int i = 0; i < searchRangeSize; ++i) {
                if (searchRange[i] == val) {
                    return true;
                }
            }
            return false;
        }

        // Input a word. Checks whether it's a pronoun. Supports English and German.
        bool is_pronoun (QString& input) {
            bool output = false;
            if (match_exists(input, germanPronounList) || match_exists(input, englishPronounList)) {
                output = true;
            }
            return output;
        }

        int case_to_int(QString& input) {
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

        // Modifies the input word to use the correct case (nominative/accusative/dative/genetive)
        QString caseify(QString baseWord, QString& gender, int wordCase, bool plural, int language) {
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

        // Adds the subject noun grouping as a component to germanSentenceList
        void add_subject(vector<QString>& sentenceList, vector<QString>& word, vector<QString>& wordAdjective, int language) {
            sentenceList.push_back(caseify("the", word[5], 0, false, language));
            sentenceList.push_back(caseify(wordAdjective[2], word[5], 0, false, language));
            sentenceList.push_back(word[3]);
        }

        // Adds the verb as a component to germanSentenceList
        void add_verb(vector<QString>& sentenceList, vector<QString>& word, vector<QString>& subjectNoun, int& tense, int language) {
            QString output = "";
            if (!is_pronoun(subjectNoun[3])) {
                output = word[6];

                // TODO: handle verb tenses other than present
            } else { 
                // TODO: pronoun handling for all 6 cases
            }
            sentenceList.push_back(output);
        }

        // Adds the preposition the germanSentenceList
        void add_preposition(vector<QString>& sentenceList, vector<QString>& word, int language) {
            sentenceList.push_back(word[2]);
        }
        // Adds the predicate noun grouping as a component to germanSentenceList
        void add_predicate(vector<QString>& sentenceList, vector<QString>& word, vector<QString>& wordAdjective, vector<QString>& wordPreposition, int& tense, int language) {
            sentenceList.push_back(caseify("the", word[5], case_to_int(wordPreposition[3]), false, language));
            sentenceList.push_back(caseify(wordAdjective[2], word[5], case_to_int(wordPreposition[3]), false, language));
            sentenceList.push_back(word[3]);
        }

        // Takes the vector components of a sentence and converts it to sentence format
        // eg: "The, big, dog, chased, the, yellow, cat.";
        vector<QString> sentence_case (vector<QString>& input, QString punctuation) {
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

        vector<QString> get_match (vector<QString>& inValue, vector<vector<QString>>& searchRange, int searchCol) {
            vector<QString> output;
            int loopRange = searchRange.size();
            for(int i = 0; i < loopRange; ++i) {
                if (searchRange[i][searchCol] == inValue[searchCol]) {
                    return searchRange[i];
                }
            }
            return output;
        }

    public:
    
        sentence(language& germanImport, language& englishImport) {
            german = germanImport;
            english = englishImport;     
        }

        ~sentence() {}

        // Generates a sentence that can then be displayed/used with other functions.
        // NOTE: Running this deletes the stored word. Only run this when a new sentence is needed.
        void generate() {
            //tense = rand() % numTenses; //choose present, past, or future (perfekt)
            tense = 0;
            germanSentenceList.clear();
            englishSentenceList.clear();

            germanSentence.sNoun = choose_word(german.nouns);
            germanSentence.sAdjective = choose_word(german.adjectives);
            germanSentence.verb = choose_word(german.verbs);
            germanSentence.preposition = choose_word(german.prepositions);
            germanSentence.pNoun = choose_word(german.nouns);
            germanSentence.pAdjective = choose_word(german.adjectives);
            
            englishSentence.sNoun = get_match(germanSentence.sNoun, english.nouns, 0);
            englishSentence.sAdjective = get_match(germanSentence.sAdjective, english.adjectives, 0);
            englishSentence.verb = get_match(germanSentence.verb, english.verbs, 0);
            englishSentence.preposition = get_match(germanSentence.preposition, english.prepositions, 0);
            englishSentence.pNoun = get_match(germanSentence.pNoun, english.nouns, 0);
            englishSentence.pAdjective = get_match(germanSentence.pAdjective, english.adjectives, 0);

            // Populate German sentence list
            add_subject(germanSentenceList, germanSentence.sNoun, germanSentence.sAdjective, 0);
            add_verb(germanSentenceList, germanSentence.verb, germanSentence.sNoun, tense, 0);
            add_preposition(germanSentenceList, germanSentence.preposition, 0);
            add_predicate(germanSentenceList, germanSentence.pNoun, germanSentence.pAdjective, germanSentence.preposition, tense, 0);

            // Populate English sentence list
            add_subject(englishSentenceList, englishSentence.sNoun, englishSentence.sAdjective, 1);
            add_verb(englishSentenceList, englishSentence.verb, englishSentence.sNoun, tense, 1);
            add_preposition(englishSentenceList, englishSentence.preposition, 1);
            add_predicate(englishSentenceList, englishSentence.pNoun, englishSentence.pAdjective, englishSentence.preposition, tense, 1);
    
        }

        // Writes the generated sentence to the terminal
        // input: vector<QString> sentenceList -- input a {lang}SentenceList
        QString output(int language) {
            QString outputValue;
            vector<QString>sentenceList;
            if (0 == language) {
                sentenceList = germanSentenceList;
            } else if (1 == language) {
                sentenceList = englishSentenceList;
            } 

            sentenceList = sentence_case(sentenceList, ".");
            int sentenceListSize = sentenceList.size();
            for(int i = 0; i < sentenceListSize; ++i) {
               outputValue += sentenceList[i];
               outputValue += " ";
            }
            return outputValue;
        }
};
