#include "header.h"

#ifndef LANGUAGE_H
#define LANGUAGE_H

class language
{
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

public:
    std::vector<QString> sentenceList;

    /****************************************
     * Set Values
     * **************************************/
    void set_id(QString input);

    void set_pronoun_list(std::vector<QString> input);

    void set_the_forms(std::vector<std::vector<QString>> input);

    void set_word_endings(std::vector<std::vector<QString>> input);

    void set_noun_list(std::vector<std::vector<QString>> input);

    void set_verb_list(std::vector<std::vector<QString>> input);

    void set_adjective_list(std::vector<std::vector<QString>> input);

    void set_preposition_list(std::vector<std::vector<QString>> input);

    void set_subject_noun(std::vector<QString> input);

    void set_subject_adjective(std::vector<QString> input);

    void set_verb(std::vector<QString> input);

    void set_preposition(std::vector<QString> input);

    void set_predicate_noun(std::vector<QString> input);

    void set_predicate_adjective(std::vector<QString> input);

    /****************************************
     * Retrieve sentence building blocks
     * **************************************/
    QString get_id();

    std::vector<QString> get_subject_noun();

    std::vector<QString> get_subject_adjective();

    std::vector<QString> get_verb();

    std::vector<QString> get_preposition();

    std::vector<QString> get_predicate_noun();

    std::vector<QString> get_predicate_adjective();

    /****************************************
     * Retrieve word lists
     * **************************************/

    std::vector<std::vector<QString>> get_noun_list();

    std::vector<std::vector<QString>> get_verb_list();

    std::vector<std::vector<QString>> get_adjective_list();

    std::vector<std::vector<QString>> get_preposition_list();

    std::vector<QString> get_pronoun_list();

    std::vector<std::vector<QString>> get_the_forms();

    std::vector<std::vector<QString>> get_word_endings();

    QString wordConjugation(QString wordGender, std::vector<std::vector<QString>> conjugationTable, QString conjugation);

    QString get_word_the(std::vector<QString>& noun, QString conjugation);

    QString get_adj_form(std::vector<QString>& noun, std::vector<QString>& adj, QString conjugation);

    //return any word that doesn't need special conjugation. These are only nouns and prepositions
    QString get_word(std::vector<QString>& word);

    QString get_verb_form (std::vector<QString>& noun, std::vector<QString>& verb);

    void build_sentence_list();
};

#endif // LANGUAGE_H
