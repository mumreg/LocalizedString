//
//  Utils.cpp
//  Dilemma
//
//  Created by Mikhail Perekhodtsev on 02.04.13.
//
//

#include "Utils.h"
#include <string>
#include "cocos2d.h"
#include "GameConfig.h"

using namespace std;
using namespace cocos2d;

unsigned char* readFile(string fileName)
{
    unsigned long fileSize = 0;
    return CCFileUtils::sharedFileUtils()->getFileData(fileName.c_str(), "r", &fileSize);
}

void setLanguage()
{
    std::string lang = string("en");

    int langNum = (int)CCApplication::sharedApplication()->getCurrentLanguage();

    const char *langSuffix[] = {LANG_SUFFIX};
    const int supportedLangs[] = {SUPPORTED_LANGS};

    if (supportedLangs[langNum] != 0) {
        lang = string(langSuffix[langNum]);
    }

    CCUserDefault::sharedUserDefault()->setStringForKey("lang", lang);
    CCUserDefault::sharedUserDefault()->flush();
}