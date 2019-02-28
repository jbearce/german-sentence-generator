#ifndef CONSOLE
#define CONSOLE
#include <iostream>
#include <iomanip>
#include <fstream>
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef RANDOM
#define RANDOM
#include <time.h>
#include <random>
#endif

#ifndef STRING
#define STRING
#include <string>
#include <ctype.h>
#endif

using namespace std;

//repackage words into a class `sentence`
class sentence {
    private:
        vector<vector<string>> nouns;
        vector<vector<string>> verbs;
        vector<vector<string>> adjectives;
        vector<vector<string>> prepositions;

        int tense = 0;
        int numTenses = 3; //change this if more tenses are added

        // sentence components to populate with generate(), 
        // in the order they appear in a standard sentence
        vector<string> chosenSubjectNoun;
        vector<string> chosenSubjectAdjective;
        vector<string> chosenVerb;
        vector<string> chosenPreposition;
        vector<string> chosenPredicateNoun;
        vector<string> chosenPredicateAdjective;

        //vector package of sentence components, built by build_sentence()
        vector<string> sentenceList;

        // Chooses a word for the input list. The list should only contain
        // words you are okay choosing from. Use the get_matches() 
        // helper function in import_functions.h to get a workable sublist
        vector<string> choose_word(vector<vector<string>> &input) {
            int choice = rand() % input.size();
            vector<string> wordData = input[choice];
            return wordData;
        }
        bool is_pronoun (string &input) {
            bool output = false;
            if (input == "ich" || input == "du" || input == "er" || input == "sie" || input == "es" || input == "wir" || input == "ihr" || input == "Sie") {
                output = true;
            }
            return output;
        }
        // Appends the correct ending to the adjective based on gender, case, and plurality (or lack thereof)
        string get_adjective_case (vector<string> &input, string &gender, string wordCase, bool plural) {
            string suffix = "";
            if (gender == "der") {
                if (wordCase == "nominative" || wordCase == "nominativ") {
                    suffix = "e";
                } else if (wordCase == "accusative" || wordCase == "akkusativ") {
                    suffix = "en";
                } else if (wordCase == "dative" || wordCase == "dativ") {
                    suffix = "en";
                }
                 else if (wordCase == "genetive" || wordCase == "genetiv") {
                    suffix = "en";
                }
            } else if (gender == "die" && plural == false) {
                if (wordCase == "nominative" || wordCase == "nominativ") {
                    suffix = "e";
                } else if (wordCase == "accusative" || wordCase == "akkusativ") {
                    suffix = "e";
                } else if (wordCase == "dative" || wordCase == "dativ") {
                    suffix = "en";
                }
                 else if (wordCase == "genetive" || wordCase == "genetiv") {
                    suffix = "en";
                }
            }
            else if (gender == "das") {
                if (wordCase == "nominative" || wordCase == "nominativ") {
                    suffix = "e";
                } else if (wordCase == "accusative" || wordCase == "akkusativ") {
                    suffix = "e";
                } else if (wordCase == "dative" || wordCase == "dativ") {
                    suffix = "en";
                }
                 else if (wordCase == "genetive" || wordCase == "genetiv") {
                    suffix = "en";
                }
            } else if (gender == "die" && plural == true) {
                if (wordCase == "nominative" || wordCase == "nominativ") {
                    suffix = "en";
                } else if (wordCase == "accusative" || wordCase == "akkusativ") {
                    suffix = "en";
                } else if (wordCase == "dative" || wordCase == "dativ") {
                    suffix = "en";
                }
                 else if (wordCase == "genetive" || wordCase == "genetiv") {
                    suffix = "en";
                }
            }
            string output = input[2] + suffix;
            return output;
        }

        string get_the_conjugation(string &gender, string wordCase, bool plural) {
            string theConjugation = "der";
            if (gender == "der") {
                if (wordCase == "nominative" || wordCase == "nominativ") {
                    theConjugation = "der";
                } else if (wordCase == "accusative" || wordCase == "akkusativ") {
                    theConjugation = "den";
                } else if (wordCase == "dative" || wordCase == "dativ") {
                    theConjugation = "dem";
                }
                 else if (wordCase == "genetive" || wordCase == "genetiv") {
                    theConjugation = "des";
                }
            } else if (gender == "die" && plural == false) {
                if (wordCase == "nominative" || wordCase == "nominativ") {
                    theConjugation = "die";
                } else if (wordCase == "accusative" || wordCase == "akkusativ") {
                    theConjugation = "die";
                } else if (wordCase == "dative" || wordCase == "dativ") {
                    theConjugation = "der";
                }
                 else if (wordCase == "genetive" || wordCase == "genetiv") {
                    theConjugation = "der";
                }
            }
            else if (gender == "das") {
                if (wordCase == "nominative" || wordCase == "nominativ") {
                    theConjugation = "das";
                } else if (wordCase == "accusative" || wordCase == "akkusativ") {
                    theConjugation = "das";
                } else if (wordCase == "dative" || wordCase == "dativ") {
                    theConjugation = "dem";
                }
                 else if (wordCase == "genetive" || wordCase == "genetiv") {
                    theConjugation = "des";
                }
            } else if (gender == "die" && plural == true) {
                if (wordCase == "nominative" || wordCase == "nominativ") {
                    theConjugation = "die";
                } else if (wordCase == "accusative" || wordCase == "akkusativ") {
                    theConjugation = "die";
                } else if (wordCase == "dative" || wordCase == "dativ") {
                    theConjugation = "den";
                }
                 else if (wordCase == "genetive" || wordCase == "genetiv") {
                    theConjugation = "der";
                }
            }
            return theConjugation;
        }
        // Adds the subject noun grouping as a component to sentenceList
        void add_subject(vector<string> &word, vector<string> &wordAdjective) {
            sentenceList.push_back(get_the_conjugation(word[2], "nominative", false));
            string temp = get_adjective_case(wordAdjective, word[2], "nominative", false);
            sentenceList.push_back(temp);
            sentenceList.push_back(word[3]);
        }

        // Adds the verb as a component to sentenceList
        void add_verb(vector<string> &word, vector<string> &subjectNoun, int &tense) {
            string output = "";
            if (is_pronoun(subjectNoun[3]) != true) {
                output = word[6];

                // TODO: handle verb tenses other than present
            } else { 
                // TODO: pronoun handling for all 6 cases
            }
            sentenceList.push_back(output);
        }

        // Adds the preposition the sentenceList
        void add_preposition(vector<string> &word) {
            sentenceList.push_back(word[2]);
        }
        // Adds the predicate noun grouping as a component to sentenceList
        void add_predicate(vector<string> &word, vector<string> &wordAdjective, vector<string> &wordPreposition, int &tense) {
            sentenceList.push_back(get_the_conjugation(word[2], wordPreposition[3], false));
            sentenceList.push_back(get_adjective_case(wordAdjective, word[2], wordPreposition[3], false));
            sentenceList.push_back(word[3]);
        }

        // Takes the vector components of a sentence and converts it to sentence format
        // eg: "The, big, dog, chased, the, yellow, cat.";
        vector<string> sentence_case (vector<string> &input, string punctuation) {
            vector<string> cleanSentence;
            for(int i = 0; i < input.size(); i++) {
                string formattedOutput = input[i];
                if (i == 0) {
                    formattedOutput[0] = toupper(formattedOutput[0]);
                } else if (i == (input.size() - 1)) {
                    formattedOutput += punctuation;
                }
                cleanSentence.push_back(formattedOutput);
            }
            return cleanSentence;
        }

    public:
    
        sentence(   
            vector<vector<string>> &inputNouns, 
            vector<vector<string>> &inputVerbs, 
            vector<vector<string>> &inputAdjectives,
            vector<vector<string>> &inputPrepositions
        ) {
            nouns = inputNouns;
            verbs = inputVerbs;
            adjectives = inputAdjectives;
            prepositions = inputPrepositions;        
        }
        ~sentence() {}

        // Generates a sentence that can then be displayed/used with other functions.
        // NOTE: Running this deletes the stored word. Only run this when a new sentence is needed.
        void generate() {
            //tense = rand() % numTenses; //choose present, past, or future (perfekt)
            sentenceList.clear();

            chosenSubjectNoun = choose_word(nouns);
            chosenSubjectAdjective = choose_word(adjectives);
            chosenVerb = choose_word(verbs);
            chosenPreposition = choose_word(prepositions);
            chosenPredicateNoun = choose_word(nouns);
            chosenPredicateAdjective = choose_word(adjectives);
            add_subject(chosenSubjectNoun, chosenSubjectAdjective);
            add_verb(chosenVerb, chosenSubjectNoun, tense);
            add_preposition(chosenPreposition);
            add_predicate(chosenPredicateNoun, chosenPredicateAdjective, chosenPreposition, tense);
            
        }

        void output() {
            vector<string> cleanSentenceList = sentence_case(sentenceList, ".");
            for(int i = 0; i < cleanSentenceList.size(); i++) {
                cout << cleanSentenceList[i] << " ";
            }
            cout << endl;
        }
};