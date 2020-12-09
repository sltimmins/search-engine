//
// Created by Sammy Timmins on 11/30/20.
//

/**
 * All made by Sam Timmins
 */
#ifndef SEARCH_ENGINE_METADATA_H
#define SEARCH_ENGINE_METADATA_H

#include <string>

using namespace std;

class Metadata
{
private:
    string id;
    string title;
    string publishDate;
    string authors;
    string journal;

public:
    Metadata() = default;
    Metadata(string &id);
    Metadata(string &id, string &title, string &publishDate, string &authors, string &journal);
    ~Metadata() = default;
    Metadata(const Metadata &copy);
    Metadata& operator=(const Metadata &copy);
    bool operator==(const Metadata &compare);
    bool operator<(const Metadata &compare) const;
    void setId(string &id);
    void setTitle(string &title);
    void setPublishDate(string &publishDate);
    void setAuthors(string &authors);
    void setJournal(string &journal);
    string getId() const;
    string getTitle() const;
    string getPublishDate() const;
    string getAuthors() const;
    string getJournal() const;

};

#endif //SEARCH_ENGINE_METADATA_H
