#include "header.h"
#include "language.h"

#ifndef ROSETTASTONE_H
#define ROSETTASTONE_H

//stores all of the languages in a neat wrapper. Allows returning a requested language based on the string ID.
class rosettaStone {
private:
    std::vector<language*> langList;

public:
    void add_language(language& newLang);

    language get_language(QString request);

    void remove_language(QString request);

    rosettaStone(language& starterLang);

    rosettaStone(language& langA, language& langB);
};


#endif // ROSETTA_STONE_H
