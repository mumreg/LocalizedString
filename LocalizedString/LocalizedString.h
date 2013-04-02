//
//  LocalizedString.h
//  Dilemma
//
//  Created by Mikhail Perekhodtsev on 02.04.13.
//
//

#ifndef __Dilemma__LocalizedString__
#define __Dilemma__LocalizedString__

#include <iostream>
#include <string>
#include <vector>
#include "rapidxml.hpp"
#include "LText.h"

#define LOCALIZATION_FILE_PREFFIX   "Localization"

class LocalizedString {
public:
    static LocalizedString *sharedInstance();
    const char *getLocalizedString(const char *key);
private:
    unsigned char *buffer;
    
    void parse();
    void SaveAttrToText(char *name, char *value, LText *text);
    
    void operator=(LocalizedString const&);
    LocalizedString(LocalizedString const&);
    LocalizedString();
    
    rapidxml::xml_document<> *doc;
    std::vector<LText *> strings;
};

#define GetLocalizedString(key)    LocalizedString::sharedInstance()->getLocalizedString(key)

#endif /* defined(__Dilemma__LocalizedString__) */
