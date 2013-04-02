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

using namespace std;
using namespace cocos2d;

unsigned char* readFile(string fileName)
{
    unsigned long fileSize = 0;
    return CCFileUtils::sharedFileUtils()->getFileData(fileName.c_str(), "r", &fileSize);
}