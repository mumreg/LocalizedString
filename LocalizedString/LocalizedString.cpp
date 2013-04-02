//
//  LocalizedString.cpp
//  Dilemma
//
//  Created by Mikhail Perekhodtsev on 02.04.13.
//
//

#include "LocalizedString.h"
#include "cocos2d.h"
#include "GameConfig.h"
#include "Utils.h"

using namespace std;
using namespace rapidxml;
using namespace cocos2d;

LocalizedString* LocalizedString::sharedInstance() {
    static LocalizedString *s_pInstance = NULL;
    
    if (s_pInstance == NULL) {
        s_pInstance = new LocalizedString();
    }
    
    return s_pInstance;
}

LocalizedString::LocalizedString() {
    string lang = string("en");
    
    int langNum = (int)CCApplication::sharedApplication()->getCurrentLanguage();
    
    const char *langSuffix[] = {LANG_SUFFIX};
    const int supportedLangs[] = {SUPPORTED_LANGS};
    
    if (supportedLangs[langNum] != 0) {
        lang = string(langSuffix[langNum]);
    }
    
    CCUserDefault::sharedUserDefault()->setStringForKey("lang", lang);
    
    string fileName = string(LOCALIZATION_FILE_PREFFIX) + string("_") + lang + string(".xml");
    
    buffer = readFile(fileName);
    if (buffer != NULL) {
        parse();
    }
}

void LocalizedString::parse()
{
    doc = new xml_document<>;
    doc->parse<parse_declaration_node | parse_no_data_nodes>((char *)buffer);
    
    xml_node<> *node = doc->first_node("Text");
    for (; node; node = node->next_sibling("Text")) {
        LText *text = new LText;
        
        xml_attribute<> *attr = node->first_attribute();
        
        for (; attr; attr = attr->next_attribute()) {
            SaveAttrToText(attr->name(), attr->value(), text);
        }
        strings.push_back(text);
    }
}

void LocalizedString::SaveAttrToText(char *name, char *value, LText *text)
{
    string name_ = string(name);
    string value_ = string(value);
    
    if (name_ == string("key"))
        text->key = value_;
    
    if (name_ == string("value"))
        text->value = value_;
}

const char * LocalizedString::getLocalizedString(const char *key) {
    string key_ = string(key);
    
    vector<LText *>::iterator it = strings.begin();
    for (; it != strings.end(); it++) {
        if ((*it)->key == key_) {
            return (*it)->value.c_str();
        }
    }
    
    return key_.c_str();
}