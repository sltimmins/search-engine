//
// Created by Sammy Timmins on 11/18/20.
//

/**
 * All made by Sam Timmins
 */
#ifndef SEARCH_ENGINE_TITLE_H
#define SEARCH_ENGINE_TITLE_H

#include <vector>
#include <string>
#include <iostream>

class Title
{
private:
    std::vector<std::string> titles;

public:
    Title() = default;
    ~Title() = default;
    Title(const Title &title);
    Title& operator=(const Title &title);
    friend std::ostream& operator<<(std::ostream&, const Title& title);
    std::string getTitleAt(int index);
    std::vector<std::string>& getTitles();
    void addTitle(std::string title);
    void printTitles();
};

#endif //SEARCH_ENGINE_TITLE_H
