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
    std::vector<std::vector<QString>> nouns;
    std::vector<std::vector<QString>> verbs;
    std::vector<std::vector<QString>> adjectives;
    std::vector<std::vector<QString>> prepositions;
};
#endif // HEADER_H
