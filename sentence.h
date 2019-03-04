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
        vector<vector<string>> gNouns;
        vector<vector<string>> gVerbs;
        vector<vector<string>> gAdjectives;
        vector<vector<string>> gPrepositions;
        vector<vector<string>> eNouns;
        vector<vector<string>> eVerbs;
        vector<vector<string>> eAdjectives;
        vector<vector<string>> ePrepositions;

        int tense = 0;
        int numTenses = 3; //change this if more tenses are added

        // sentence components to populate with generate(), 
        // in the order they appear in a standard sentence
        vector<string> chosenGSubjectNoun;
        vector<string> chosenGSubjectAdjective;
        vector<string> chosenGVerb;
        vector<string> chosenGPreposition;
        vector<string> chosenGPredicateNoun;
        vector<string> chosenGPredicateAdjective;

        vector<string> chosenESubjectNoun;
        vector<string> chosenESubjectAdjective;
        vector<string> chosenEVerb;
        vector<string> chosenEPreposition;
        vector<string> chosenEPredicateNoun;
        vector<string> chosenEPredicateAdjective;

        //vector package of sentence components, built by build_sentence()
        vector<string> germanSentenceList;
        vector<string> englishSentenceList;

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
        // Requires: vector<string> input (word data), string gender (der/die/das for German, he/she/it for English), 
        //           string wordCase (nominative/accusative/dative), bool plural (is the noun plural?), int language = 0 for German, 1 for English
        string get_adjective_case (vector<string> &input, string &gender, string wordCase, bool plural, int language) {
            if (language == 0) {
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
            } else if (language == 1) {
                if (plural == false) {
                    return input[2];
                } else if (plural == true) {
                    return input[3];
                }
            }  
            
            return "REDACTED";
        }

        string get_the_conjugation(string &gender, string wordCase, bool plural, int language) {
            if (language == 0) {
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
            } else if (language == 1) {
                return "the";
            }
           
        }

        // Adds the subject noun grouping as a component to germanSentenceList
        void add_subject(vector<string> &sentenceList, vector<string> &word, vector<string> &wordAdjective, int language) {
            sentenceList.push_back(get_the_conjugation(word[2], "nominative", false, language));
            sentenceList.push_back(get_adjective_case(wordAdjective, word[2], "nominative", false, language));
            sentenceList.push_back(word[3]);
        }

        // Adds the verb as a component to germanSentenceList
        void add_verb(vector<string> &sentenceList, vector<string> &word, vector<string> &subjectNoun, int &tense, int language) {
            string output = "";
            if (is_pronoun(subjectNoun[3]) != true) {
                output = word[6];

                // TODO: handle verb tenses other than present
            } else { 
                // TODO: pronoun handling for all 6 cases
            }
            sentenceList.push_back(output);
        }

        // Adds the preposition the germanSentenceList
        void add_preposition(vector<string> &sentenceList, vector<string> &word, int language) {
            sentenceList.push_back(word[2]);
        }
        // Adds the predicate noun grouping as a component to germanSentenceList
        void add_predicate(vector<string> &sentenceList, vector<string> &word, vector<string> &wordAdjective, vector<string> &wordPreposition, int &tense, int language) {
            sentenceList.push_back(get_the_conjugation(word[2], wordPreposition[3], false, language));
            sentenceList.push_back(get_adjective_case(wordAdjective, word[2], wordPreposition[3], false, language));
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

        vector<string> get_match (vector<string> &inValue, vector<vector<string>> &searchRange, int searchCol) {
            vector<string> output;
            int loopRange = searchRange.size();
            for(int i = 0; i < loopRange; i++) {
                if (searchRange[i][searchCol] == inValue[searchCol]) {
                    return searchRange[i];
                }
            }
            return output;
        }
    public:
    
        sentence(   
            vector<vector<string>> &inputGNouns, 
            vector<vector<string>> &inputGVerbs, 
            vector<vector<string>> &inputGAdjectives,
            vector<vector<string>> &inputGPrepositions,
            vector<vector<string>> &inputENouns,
            vector<vector<string>> &inputEVerbs,
            vector<vector<string>> &inputEAdjectives,
            vector<vector<string>> &inputEPrepositions
        ) {
            gNouns = inputGNouns;
            gVerbs = inputGVerbs;
            gAdjectives = inputGAdjectives;
            gPrepositions = inputGPrepositions;
            
            eNouns = inputENouns;
            eVerbs = inputEVerbs;
            eAdjectives = inputEAdjectives;
            ePrepositions = inputEPrepositions;        
        }
        ~sentence() {}

        // Generates a sentence that can then be displayed/used with other functions.
        // NOTE: Running this deletes the stored word. Only run this when a new sentence is needed.
        void generate() {
            //tense = rand() % numTenses; //choose present, past, or future (perfekt)
            tense = 0;
            germanSentenceList.clear();
            englishSentenceList.clear();

            chosenGSubjectNoun = choose_word(gNouns);
            chosenGSubjectAdjective = choose_word(gAdjectives);
            chosenGVerb = choose_word(gVerbs);
            chosenGPreposition = choose_word(gPrepositions);
            chosenGPredicateNoun = choose_word(gNouns);
            chosenGPredicateAdjective = choose_word(gAdjectives);
            
            chosenESubjectNoun = get_match(chosenGSubjectNoun, eNouns, 0);
            chosenESubjectAdjective = get_match(chosenGSubjectAdjective, eAdjectives, 0);
            chosenEVerb = get_match(chosenGVerb, eVerbs, 0);
            chosenEPreposition = get_match(chosenGPreposition, ePrepositions, 0);
            chosenEPredicateNoun = get_match(chosenGPredicateNoun, eNouns, 0);
            chosenEPredicateAdjective = get_match(chosenGPredicateAdjective, eAdjectives, 0);

            // Populate German sentence list
            add_subject(germanSentenceList, chosenGSubjectNoun, chosenGSubjectAdjective, 0);
            add_verb(germanSentenceList, chosenGVerb, chosenGSubjectNoun, tense, 0);
            add_preposition(germanSentenceList, chosenGPreposition, 0);
            add_predicate(germanSentenceList, chosenGPredicateNoun, chosenGPredicateAdjective, chosenGPreposition, tense, 0);

            // Populate English sentence list
            add_subject(englishSentenceList, chosenESubjectNoun, chosenESubjectAdjective, 1);
            add_verb(englishSentenceList, chosenEVerb, chosenESubjectNoun, tense, 1);
            add_preposition(englishSentenceList, chosenEPreposition, 1);
            add_predicate(englishSentenceList, chosenEPredicateNoun, chosenEPredicateAdjective, chosenEPreposition, tense, 1);
     
        }

        // Writes the generated sentence to the terminal
        // input: vector<string> sentenceList -- input a {lang}SentenceList
        void output(int language) {
            vector<string>sentenceList;
            if (language == 0) {
                sentenceList = germanSentenceList;
            } else if (language == 1) {
                sentenceList = englishSentenceList;
            } 

            vector<string> cleanSentenceList = sentence_case(sentenceList, ".");
            for(int i = 0; i < cleanSentenceList.size(); i++) {
                cout << cleanSentenceList[i] << " ";
            }
            cout << endl;
        }
};