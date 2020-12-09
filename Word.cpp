//
// Created by Kevin Leong on 11/15/20.
//

#include "Word.h"

Word::Word(string word) {
    this->word = word;
    this->totalFreq = 0;
}
Word::Word(char *word) {
    this->word = word;
    this->totalFreq = 0;
}
Word::Word(const Word &copy) {
    this->word = copy.word;
    this->titleList = copy.titleList;
    this->totalFreq = copy.totalFreq;
}

Word::~Word() = default;

bool Word::operator>(const Word &comp) const {
    return this->word > comp.word;
}
bool Word::operator<(const Word &comp) const {
    return this->word < comp.word;
}
bool Word::operator==(const Word &comp) const {
    return this->word == comp.word;
}

string Word::getWord(){
    return this->word;
}
map<string, int>& Word::getTitleList() {
    return this->titleList;
}

void Word::addPaperID(string paperID) {
    this->titleList[paperID];
    this->titleList.at(paperID) = 0;
}

int Word::getTotalFreq() {
    return this->totalFreq;
}

void Word::iterTotalFreq() {
    this->totalFreq++;
}

ostream &operator<<(ostream &os, const Word &word)
{
    os << "\t\t{\n\t\t\t\"string\": \"" << word.word << "\",\n"
       << "\t\t\t\"total frequency\": \"" << word.totalFreq <<"\",\n" //add comma after total frequency
       << "\t\t\t\"ids\": [\n";

    auto it = word.titleList.begin();
    while(it != prev(word.titleList.end()))
    {
        os << "\t\t\t\t{\n\t\t\t\t\t\"id\": \"" << it->first << "\"\n\t\t\t\t},\n";
        it++;
    }

    os << "\t\t\t\t{\n\t\t\t\t\t\"id\": \"" << it->first << "\"\n\t\t\t\t}\n";

    os << "\t\t\t]\n\t\t}";

    return os;
}

void Word::setWord(const string &word)
{
    this->word = word;
}

void Word::setTotalFreq(const int &totalFreq)
{
    this->totalFreq = totalFreq;
}


