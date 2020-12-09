//
// Created by Sammy Timmins on 11/19/20.
//

#include "IndexHandler.h"

/**
 * Performs a search in the wordIndex AVL Tree (S.T.)
 * @param wordIndex
 * @param search
 * @param foundTitles
 */
void wordSearch(DSTree<Word>& wordIndex, string& search, map<string, int>& foundTitles)
{
    Porter2Stemmer::stem(search);
    toLower(search);
    Word found, word(search);

    if(wordIndex.getNumNodes() > 0)
    {
        if(wordIndex.find(word))
        {
            found = wordIndex.get(word);

            map<string, int>::iterator it;
            int x = 0;
            for ( it = found.getTitleList().begin(); it != found.getTitleList().end(); it++)
            {
                foundTitles.insert (std::pair<string,int>(it->first,it->second));
                x++;
            }
        }
    }
    else
    {
        cout << "No index opened, please open an index to search." << endl;
    }

}

/**
 * Performs a search on the Author HashTable (S.T.)
 * @param authorIndex
 * @param search
 * @param foundTitles
 */
void authorSearch(DSHashTable<string, Title>& authorIndex, string& search, map<string, int>& foundTitles)
{
    toLower(search);
    Title found;

    if(authorIndex.find(search))
    {
        found = authorIndex.get(search);
        for(int i = 0; i < found.getTitles().size(); i++)
        {
            //foundTitles.insert(found.getTitleAt(i));
            foundTitles.insert(std::pair<string,int>(found.getTitles().at(i), i));
        }
    }
}