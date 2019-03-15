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
            if ("ich" == input || "du" == input || "er" == input || "sie" == input || "es" == input || "wir" == input || "ihr" == input || "Sie" == input) {
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

                if ("der" == gender) {
                    if ("nominative" == wordCase || "nominativ" == wordCase) {
                        suffix = "e";
                    } else if ("accusative" == wordCase || "akkusativ" == wordCase) {
                        suffix = "en";
                    } else if ("dative" == wordCase || "dativ" == wordCase) {
                        suffix = "en";
                    } else if ("genetive" == wordCase || "genetiv" == wordCase) {
                        suffix = "en";
                    }
                } else if ("die" == gender && false == plural) {
                    if ("nominative" == wordCase || "nominativ" == wordCase) {
                        suffix = "e";
                    } else if ("accusative" == wordCase || "akkusativ" == wordCase) {
                        suffix = "e";
                    } else if ("dative" == wordCase || "dativ" == wordCase) {
                        suffix = "en";
                    }
                    else if ("genetive" == wordCase || "genetiv" == wordCase) {
                        suffix = "en";
                    }
                } else if ("das" == gender) {
                    if ("nominative" == wordCase || "nominativ" == wordCase) {
                        suffix = "e";
                    } else if ("accusative" == wordCase || "akkusativ" == wordCase) {
                        suffix = "e";
                    } else if ("dative" == wordCase || "dativ" == wordCase) {
                        suffix = "en";
                    } else if ("genetive" == wordCase || "genetiv" == wordCase) {
                        suffix = "en";
                    }
                } else if ("die" == gender && true == plural) {
                    if ("nominative" == wordCase || "nominativ" == wordCase) {
                        suffix = "en";
                    } else if ("accusative" == wordCase || "akkusativ" == wordCase) {
                        suffix = "en";
                    } else if ("dative" == wordCase || "dativ" == wordCase) {
                        suffix = "en";
                    } else if ("genetive" == wordCase || "genetiv" == wordCase) {
                        suffix = "en";
                    }
                }
                string output = input[2] + suffix;
                return output;
            } else if (1 == language) {
                if (false == plural) {
                    return input[2];
                } else if (true == plural) {
                    return input[3];
                }
            }
            return "REDACTED";
        }

        string get_the_conjugation(string &gender, string wordCase, bool plural, int language) {
            if (language == 0) {
                string theConjugation = "der";
                if ("der" == gender) {
                    if ("nominative" == wordCase || "nominativ" == wordCase) {
                        theConjugation = "der";
                    } else if ("accusative" == wordCase || "akkusativ" == wordCase) {
                        theConjugation = "den";
                    } else if ("dative" == wordCase || "dativ" == wordCase) {
                        theConjugation = "dem";
                    }
                    else if ("genetive" == wordCase || "genetiv" == wordCase) {
                        theConjugation = "des";
                    }
                } else if ("die" == gender && false == plural) {
                    if ("nominative" == wordCase || "nominativ" == wordCase) {
                        theConjugation = "die";
                    } else if ("accusative" == wordCase || "akkusativ" == wordCase) {
                        theConjugation = "die";
                    } else if ("dative" == wordCase || "dativ" == wordCase) {
                        theConjugation = "der";
                    }
                    else if ("genetive" == wordCase || "genetiv" == wordCase) {
                        theConjugation = "der";
                    }
                }
                else if ("das" == gender) {
                    if ("nominative" == wordCase || "nominativ" == wordCase) {
                        theConjugation = "das";
                    } else if ("accusative" == wordCase || "akkusativ" == wordCase) {
                        theConjugation = "das";
                    } else if ("dative" == wordCase || "dativ" == wordCase) {
                        theConjugation = "dem";
                    }
                    else if ("genetive" == wordCase || "genetiv" == wordCase) {
                        theConjugation = "des";
                    }
                } else if ("die" == gender && true == plural) {
                    if ("nominative" == wordCase || "nominativ" == wordCase) {
                        theConjugation = "die";
                    } else if ("accusative" == wordCase || "akkusativ" == wordCase) {
                        theConjugation = "die";
                    } else if ("dative" == wordCase || "dativ" == wordCase) {
                        theConjugation = "den";
                    }
                    else if ("genetive" == wordCase || "genetiv" == wordCase) {
                        theConjugation = "der";
                    }
                }
                return theConjugation;
            } else if (language == 1) {
                return "the";
            } else {
                return "";
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
            int inputSize = input.size();
            for(int i = 0; i < inputSize; ++i) {
                string formattedOutput = input[i];
                if (0 == i) {
                    formattedOutput[0] = toupper(formattedOutput[0]);
                } else if ((inputSize - 1) == i) {
                    formattedOutput += punctuation;
                }
                cleanSentence.push_back(formattedOutput);
            }
            return cleanSentence;
        }

        vector<string> get_match (vector<string> &inValue, vector<vector<string>> &searchRange, int searchCol) {
            vector<string> output;
            int loopRange = searchRange.size();
            for(int i = 0; i < loopRange; ++i) {
                if (searchRange[i][searchCol] == inValue[searchCol]) {
                    return searchRange[i];
                }
            }
            return output;
        }

    public:
    
        sentence(language germanImport, language englishImport) {
            gNouns = germanImport.nouns;
            gVerbs = germanImport.verbs;
            gAdjectives = germanImport.adjectives;
            gPrepositions = germanImport.prepositions;
            
            eNouns = englishImport.nouns;
            eVerbs = englishImport.verbs;
            eAdjectives = englishImport.adjectives;
            ePrepositions = englishImport.prepositions;        
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
            if (0 == language) {
                sentenceList = germanSentenceList;
            } else if (1 == language) {
                sentenceList = englishSentenceList;
            } 

            vector<string> cleanSentenceList = sentence_case(sentenceList, ".");
            int cleanSentenceListSize = cleanSentenceList.size();
            for(int i = 0; i < cleanSentenceListSize; ++i) {
                cout << cleanSentenceList[i] << " ";
            }
            cout << endl;
        }
};