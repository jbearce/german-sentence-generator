#ifndef HEADER_H
#define HEADER_H
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <random>
#include <string>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <time.h>
#include <vector>
struct language {
private:
    QString id;
    std::vector<std::vector<QString>> nouns;
    std::vector<std::vector<QString>> verbs;
    std::vector<std::vector<QString>> adjectives;
    std::vector<std::vector<QString>> prepositions;
    std::vector<std::vector<QString>> genderedWordEndings;
    std::vector<std::vector<QString>> theForms;
    std::vector<QString> pronouns;
    std::vector<QString> sNoun; //expected: 0:{word_id}, 1:{word_type}, 2:{word_the_form}, 3:{base_word}, 4:{plural}, 5:{word_gender}
    std::vector<QString> sAdjective;
    std::vector<QString> verb;
    std::vector<QString> preposition;
    std::vector<QString> pNoun;
    std::vector<QString> pAdjective;
    std::vector<QString> constructedSentence;

public:
    std::vector<QString> sentenceList;

    /****************************************
     * Set Values
     * **************************************/
    void set_id(QString input) {
        id = input;
    }

    void set_pronoun_list(std::vector<QString> input) {
        pronouns = input;
    }

    void set_the_forms(std::vector<std::vector<QString>> input) {
        theForms = input;
    }

    void set_word_endings(std::vector<std::vector<QString>> input) {
        genderedWordEndings = input;
    }

    void set_noun_list(std::vector<std::vector<QString>> input) {
        nouns = input;
    }

    void set_verb_list(std::vector<std::vector<QString>> input) {
        verbs = input;
    }

    void set_adjective_list(std::vector<std::vector<QString>> input) {
        adjectives = input;
    }

    void set_preposition_list(std::vector<std::vector<QString>> input) {
        prepositions = input;
    }

    void set_subject_noun(std::vector<QString> input) {
        sNoun = input;
    }

    void set_subject_adjective(std::vector<QString> input) {
        sAdjective = input;
    }

    void set_verb(std::vector<QString> input) {
        verb = input;
    }

    void set_preposition(std::vector<QString> input) {
        preposition = input;
    }

    void set_predicate_noun(std::vector<QString> input) {
        pNoun = input;
    }

    void set_predicate_adjective(std::vector<QString> input) {
        pAdjective = input;
    }

    /****************************************
     * Retrieve sentence building blocks
     * **************************************/
    QString get_id() {
        return id;
    }

    std::vector<QString> get_subject_noun() {
        return sNoun;
    }

    std::vector<QString> get_subject_adjective() {
        return sAdjective;
    }

    std::vector<QString> get_verb() {
        return verb;
    }

    std::vector<QString> get_preposition() {
        return preposition;
    }

    std::vector<QString> get_predicate_noun() {
        return pNoun;
    }

    std::vector<QString> get_predicate_adjective() {
        return pAdjective;
    }

    /****************************************
     * Retrieve word lists
     * **************************************/

    std::vector<std::vector<QString>> get_noun_list() {
        return nouns;
    }

    std::vector<std::vector<QString>> get_verb_list() {
        return verbs;
    }

    std::vector<std::vector<QString>> get_adjective_list() {
        return adjectives;
    }

    std::vector<std::vector<QString>> get_preposition_list() {
        return prepositions;
    }

    std::vector<QString> get_pronoun_list() {
        return pronouns;
    }

    std::vector<std::vector<QString>> get_the_forms() {
        return theForms;
    }

    std::vector<std::vector<QString>> get_word_endings() {
        return genderedWordEndings;
    }
};
#endif // HEADER_H
