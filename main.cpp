//
// Created by Sammy Timmins on 11/14/20.
//
#define CATCH_CONFIG_RUNNER

#include <iostream>
#include "catch.hpp"
#include "Runner.h"

int runCatchTests(int argc, char* const argv[])
{
    return Catch::Session().run(argc, argv);
}

/**
 * Each file header will specify who created the file, although some files both team members worked on
 * If a file was worked on by both teammates, then the specific function will have their initials in the comment above it
 * Otherwise, the creator of the file will be specified on the top
 *
 * Happy Searching! :)
 */

int main(int argc, char** argv)
{
    if(argc == 3)
    {
        string search = argv[1];
        string path = argv[2];
        runSearchEngine(search, path);
    }
    else if(argc == 1)
    {
        //runs the actual search engine
        runSearchEngine();
    }
    else if(strcmp(argv[1], "-test") == 0)
    {
        // runs catch tests
        return runCatchTests(1, argv);
    }

    return 0;
}

