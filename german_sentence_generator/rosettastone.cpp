#include "rosettastone.h"

void rosettaStone::add_language(language& newLang) {
    language* langPtr = nullptr;
    *langPtr = newLang;
    langList.push_back(langPtr);
}

language rosettaStone::get_language(QString request) {
    int langCount = int(langList.size());
    language output;
    output.set_id("");
    for(int i = 0; i < langCount; ++i) {
        if (request == langList[u_long(i)]->get_id()) {
            output = *langList[u_long(i)];
        }
    }
    return output;
}

void rosettaStone::remove_language(QString request) {
    int langCount = int(langList.size());
    for(int i = 0; i < langCount; ++i) {
        if (request == langList[u_long(i)]->get_id()) {
            langList.erase(langList.begin() + i);
        }
    }
}

rosettaStone::rosettaStone(language& starterLang) {
    language* langPtr = nullptr;
    langPtr = &starterLang;
    langList.push_back(langPtr);
}

rosettaStone::rosettaStone(language& langA, language& langB) {
    language* langPtr = nullptr;
    langPtr = &langA;
    langList.push_back(langPtr);

    langPtr = &langB;
    langList.push_back(langPtr);
}
