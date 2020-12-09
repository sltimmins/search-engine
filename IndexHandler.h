//
// Created by Sammy Timmins on 11/19/20.
//

#ifndef SEARCH_ENGINE_INDEXHANDLER_H
#define SEARCH_ENGINE_INDEXHANDLER_H

#include <vector>
#include <string>
#include <map>
#include "Index.h"
#include "DSTree.h"
#include "Word.h"
#include "porter2_stemmer.h"

void wordSearch(DSTree<Word>& wordIndex, std::string& search, map<string, int>& foundTitles);
void authorSearch(DSHashTable<std::string, Title>& authorIndex, std::string& search, map<string, int>& foundTitles);


#endif //SEARCH_ENGINE_INDEXHANDLER_H
