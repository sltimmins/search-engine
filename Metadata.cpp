//
// Created by Sammy Timmins on 11/30/20.
//

#include "Metadata.h"

Metadata::Metadata(string &id, string &title, string &publishDate, string &authors, string &journal)
{
    this->id = id;
    this->title = title;
    this->publishDate = publishDate;
    this->authors = authors;
    this->journal = journal;
}

Metadata::Metadata(string &id)
{
    this->id = id;
}

Metadata::Metadata(const Metadata &copy)
{
    id = copy.id;
    title = copy.title;
    publishDate = copy.publishDate;
    authors = copy.authors;
    journal = copy.journal;
}

Metadata &Metadata::operator=(const Metadata &copy)
{
    id = copy.id;
    title = copy.title;
    publishDate = copy.publishDate;
    authors = copy.authors;
    journal = copy.journal;

    return *this;
}

bool Metadata::operator==(const Metadata &compare)
{
    return id == compare.id;
}

bool Metadata::operator<(const Metadata &compare) const
{
    return id < compare.id;
}

void Metadata::setId(string &id)
{
    this->id = id;
}

void Metadata::setTitle(string &title)
{
    this->title = title;
}

void Metadata::setPublishDate(string &publishDate)
{
    this->publishDate = publishDate;
}

void Metadata::setAuthors(string &authors)
{
    this->authors = authors;
}

void Metadata::setJournal(string &journal)
{
    this->journal = journal;
}

string Metadata::getId() const
{
    return id;
}

string Metadata::getTitle() const
{
    return title;
}

string Metadata::getPublishDate() const
{
    return publishDate;
}

string Metadata::getAuthors() const
{
    return authors;
}

string Metadata::getJournal() const
{
    return journal;
}
