//
// Created by Sammy Timmins on 11/16/20.
//

#ifndef SEARCH_ENGINE_RUNNER_H
#define SEARCH_ENGINE_RUNNER_H

#include "DSHashTable.h"
#include "DSTree.h"
#include "Word.h"
#include "Title.h"
#include "Index.h"
#include "IndexHandler.h"
#include "QueryHandler.h"

void runSearchEngine();
void runSearchEngine(std::string& wordToFind, std::string& directoryPath);


#endif //SEARCH_ENGINE_RUNNER_H
