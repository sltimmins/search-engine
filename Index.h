//
// Created by Sammy Timmins on 11/19/20.
//

#ifndef SEARCH_ENGINE_INDEX_H
#define SEARCH_ENGINE_INDEX_H

#include <string>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sstream>
#include <set>
#include <algorithm>

#include "porter2_stemmer.h"
#include "rapidjson/document.h"
#include "rapidcsv.h"
#include "Word.h"
#include "Title.h"
#include "DSTree.h"
#include "DSHashTable.h"
#include "Metadata.h"

int buildIndexes(DSHashTable<std::string, Title> &authorIndex, DSTree<Word> &wordIndex, string &path, int &average);
void buildMetadata(set<Metadata> &metadata);
void makeFillerSet(set<string> &fillerSet);
void removeTrailingPunct(string& word);
void toLower(string& word);
std::string getFile(std::string &filePath);

#endif //SEARCH_ENGINE_INDEX_H
