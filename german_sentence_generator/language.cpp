#include "language.h"

/****************************************
 * Set Values
 * **************************************/
void language::set_id(QString input) {
    id = input;
}

void language::set_pronoun_list(std::vector<QString> input) {
    pronouns = input;
}

void language::set_the_forms(std::vector<std::vector<QString>> input) {
    theForms = input;
}

void language::set_word_endings(std::vector<std::vector<QString>> input) {
    genderedWordEndings = input;
}

void language::set_noun_list(std::vector<std::vector<QString>> input) {
    nouns = input;
}

void language::set_verb_list(std::vector<std::vector<QString>> input) {
    verbs = input;
}

void language::set_adjective_list(std::vector<std::vector<QString>> input) {
    adjectives = input;
}

void language::set_preposition_list(std::vector<std::vector<QString>> input) {
    prepositions = input;
}

void language::set_subject_noun(std::vector<QString> input) {
    sNoun = input;
}

void language::set_subject_adjective(std::vector<QString> input) {
    sAdjective = input;
}

void language::set_verb(std::vector<QString> input) {
    verb = input;
}

void language::set_preposition(std::vector<QString> input) {
    preposition = input;
}

void language::set_predicate_noun(std::vector<QString> input) {
    pNoun = input;
}

void language::set_predicate_adjective(std::vector<QString> input) {
    pAdjective = input;
}

QString language::get_id() {
    return id;
}

std::vector<QString> language::get_subject_noun() {
    return sNoun;
}

std::vector<QString> language::get_subject_adjective() {
    return sAdjective;
}

std::vector<QString> language::get_verb() {
    return verb;
}

std::vector<QString> language::get_preposition() {
    return preposition;
}

std::vector<QString> language::get_predicate_noun() {
    return pNoun;
}

std::vector<QString> language::get_predicate_adjective() {
    return pAdjective;
}

/****************************************
 * Retrieve word lists
 * **************************************/

std::vector<std::vector<QString>> language::get_noun_list() {
    return nouns;
}

std::vector<std::vector<QString>> language::get_verb_list() {
    return verbs;
}

std::vector<std::vector<QString>> language::get_adjective_list() {
    return adjectives;
}

std::vector<std::vector<QString>> language::get_preposition_list() {
    return prepositions;
}

std::vector<QString> language::get_pronoun_list() {
    return pronouns;
}

std::vector<std::vector<QString>> language::get_the_forms() {
    return theForms;
}

std::vector<std::vector<QString>> language::get_word_endings() {
    return genderedWordEndings;
}

QString language::wordConjugation(QString wordGender, std::vector<std::vector<QString>> conjugationTable, QString conjugation) {
    QString output = "";
    if (conjugationTable.size()) {
        if (conjugationTable[0].size()) {
            int tableWidth = int(conjugationTable[0].size());
            int genderPos = 0;

            //get gender column (masculine, feminine, neutral, plural)
            for(int i = 0; i < tableWidth; ++i) {
                if (wordGender == conjugationTable[u_long(0)][u_long(i)]) {
                    genderPos = i;
                    break;
                }
            }

            int row = 0;

            //grab conjugated table entry
            if ("nominative" == conjugation) {
                row = 1;
            } else if ("accusative" == conjugation) {
                row = 2;
            } else if ("dative" == conjugation) {
                row = 3;
            } else if ("genetive" == conjugation) {
                row = 4;
            }

            if (row < int(conjugationTable.size()) && genderPos < int(conjugationTable[u_long(row)].size())) {
                output += conjugationTable[u_long(row)][u_long(genderPos)];
            }
        }
    }
    return output;
}

QString language::get_word_the(std::vector<QString>& noun, QString conjugation) {
    QString output = wordConjugation(noun[5], theForms, conjugation);
    if (output != "") {
        return output;
    } else {
        return "the";
    }
}

QString language::get_adj_form(std::vector<QString>& noun, std::vector<QString>& adj, QString conjugation) {
    QString output = adj[2];
    output += wordConjugation(noun[5], genderedWordEndings, conjugation);
    return output;
}

//return any word that doesn't need special conjugation. These are only nouns and prepositions
QString language::get_word(std::vector<QString>& word) {
    if (word[1] == "noun") {
        return word[3];
    } else if ("preposition" == word[1]) {
        return word[2];
    } else {
        return "";
    }
}

QString language::get_verb_form (std::vector<QString>& noun, std::vector<QString>& verb) {
    //TODO: add pronoun support. As-is, this is super simple though.
    //TODO: add seperable verb support.
    return verb[6];
}

void language::build_sentence_list() {
    sentenceList.clear();
    sentenceList.push_back(get_word_the(sNoun, "nominative"));
    sentenceList.push_back(get_adj_form(sNoun, sAdjective, "nominative"));
    sentenceList.push_back(get_word(sNoun));
    sentenceList.push_back(get_verb_form(sNoun, verb));
    sentenceList.push_back(get_word(preposition));
    sentenceList.push_back(get_word_the(pNoun, preposition[3]));
    sentenceList.push_back(get_adj_form(pNoun, pAdjective, preposition[3]));
    sentenceList.push_back(get_word(pNoun));
}
