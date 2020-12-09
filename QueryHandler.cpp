//
// Created by Sammy Timmins on 11/22/20.
//

//The thingy: /Users/kevinleong/Documents/cs2341_data/
//The thingy but practice: /Users/kevinleong/Documents/ds_03/

#include "QueryHandler.h"

using namespace std;

/**
 * Creates a query that passes in the wordIndex, authorIndex, and searchResults
 */
void query(DSTree<Word> wordIndex, DSHashTable<string, Title> authorIndex, map<string,int> & searchResults)
{
    //creates metaData
    set<Metadata> metadata;
    string path;            //stores path to the folder
    bool queryRun = true;
    int numArticles = 0;    //basic statistics used in options
    int averageWords = 0;

    /**
     * Infinite loop keeps the selection going until 0 is pressed (Created by Sam)
     */
    cout << "Welcome to the COVID-19 Research Database Search Engine" << endl;
    while(queryRun)
    {
        string selectionString;
        int selection;
        cout << "Please select one of the following options:\n" //gui selection interface
             << "1. Boolean Query\n"
             << "2. Get total number of articles indexed\n"
             << "3. Get average number of words per indexed article\n"
             << "4. Get the total number of words in all indexed articles\n"
             << "5. Total number of unique authors\n"
             << "6. 50 most frequent words in indexed articles\n"
             << "7. Clear index\n"
             << "8. Parse corpus and populate index OR open a persistence file\n"
             << "9. Save the currently open index to a persistence file.\n"
             << "0. Exit\n"
             << "Selection: ";

        /**
         * Gets the input from the user
         */
        while(true) //handles incorrect inputs
        {
            try
            {
                getline(cin, selectionString);
                selection = stoi(selectionString);
                break;
            }
            catch(invalid_argument)
            {
                cin.clear();
                cout << "Invalid selection please try again.\nSelect a number 0 - 9: ";
            }
        }

        checkInput(selection, 0, 9);

        switch(selection) //calls correct function based on input
        {
            case 1:
            {
                string searchQuery, query; //gets boolean search query input
                stringstream ss;
                cout << "Please enter your boolean search query. Options are AND, OR, AUTHOR, NOT, and a single word" << endl;
                getline(cin, searchQuery);
                string toPrintQuery = searchQuery;
                toLower(searchQuery);

                /*
                 * Appends a null for each search result (used for boolean searches)
                 */
                searchQuery += " /0";

                /**
                 * Logic for AND, OR, NOT, and AUTHOR was created by Kevin
                 */
                ss << searchQuery;
                while(getline(ss, searchQuery, ' ')) //loops through the entire input
                {
                    /** AND */
                    if(searchQuery == "and") //if its an AND request
                    {
                        getline(ss, query, ' '); //gets the next word
                        while(query != "not" && query != "author") //loops in and until another boolean request is received
                        {
                            if(query == "/0"){
                                break;
                            }

                            map<string, int> foundTitles;
                            wordSearch(wordIndex, query, foundTitles);
                            if(foundTitles.size() == 0)
                            {
                                searchResults.clear();
                                break;
                            }
                            if(!searchResults.empty()) //if the search results already has results in it
                            {
                                /**
                                 * compare two maps and remove items not in both
                                 */
                                map<string, int> tempMap;
                                auto it = searchResults.begin();

                                while(it != searchResults.end()){
                                    if(foundTitles.count(it->first) != 0)
                                    {
                                        //searchResults.erase(it);
                                        tempMap.insert(pair<string, int>(it->first, it->second + foundTitles[it->first]));
                                    }
                                    it++;
                                }
                                searchResults.clear();
                                searchResults = tempMap;
                            }
                            else
                            {
                                searchResults = foundTitles;
                            }
                            getline(ss, query, ' ');
                            toLower(query);
                        }
                        if(query == "not")
                        {
                            map<string, int> foundTitles;
                            getline(ss, query, ' ');
                            wordSearch(wordIndex, query, foundTitles);
                            /**
                             * remove all elements in foundTitles from searchResults map
                             */

                            notCompare(searchResults, foundTitles);
                        }
                        else if(query == "author")
                        {
                            map<string, int> foundTitles;
                            getline(ss, query, ' ');
                            authorSearch(authorIndex, query, foundTitles);
                            /**
                             * compare two MAPS remove items not in both
                             */
                            authorCompare(searchResults, foundTitles);
                        }
                        break;
                    }

                    /** OR */
                    else if(searchQuery == "or") //if OR query
                    {
                        getline(ss, query, ' ');

                        while(query != "not" && query != "author") //loops until a NOT or AUTHOR query
                        {
                            if(query == "/0"){
                                break;
                            }

                            /** Inserts it all into searchResults */
                            toLower(query);
                            wordSearch(wordIndex, query, searchResults);

                            getline(ss, query, ' ');
                            toLower(query);
                        }
                        if(query == "not")
                        {
                            map<string, int> foundTitles;
                            getline(ss, query, ' ');
                            wordSearch(wordIndex, query, foundTitles);
                            /**
                             * remove all elements in foundTitles from searchResults map
                             */

                            notCompare(searchResults, foundTitles);
                        }
                        else if(query == "author")
                        {
                            map<string, int> foundTitles;
                            getline(ss, query, ' ');
                            authorSearch(authorIndex, query, foundTitles);
                            /**
                             * compare two MAPPY MAPS and remove items not in both
                             */

                            authorCompare(searchResults, foundTitles);
                        }
                        break;
                    }

                    /** AUTHOR */
                    else if(searchQuery == "author")
                    {
                        map<string, int> foundTitles;
                        getline(ss, query, ' ');
                        authorSearch(authorIndex, query, foundTitles);

                        if(!searchResults.empty())
                        {
                            /**
                             * compare two MAPS remove items not in both
                             */
                            authorCompare(searchResults, foundTitles);
                        }
                        else
                        {
                            searchResults = foundTitles;
                        }
                        break;
                    }
                    else
                    {
                        map<string, int> foundTitles;
                        query = searchQuery;
                        wordSearch(wordIndex, query, foundTitles);
                        while(query != "not" && query != "author")
                        {
                            if(query == "/0")
                            {
                                break;
                            }

                            searchResults = foundTitles;

                            getline(ss, query, ' ');
                            toLower(query);
                        }
                        if(query == "not")
                        {
                            foundTitles.clear();
                            getline(ss, query, ' ');
                            wordSearch(wordIndex, query, foundTitles);
                            /**
                             * remove all elements in foundTitles from searchResults map
                             */

                            notCompare(searchResults, foundTitles);
                        }
                        else if(query == "author")
                        {
                            foundTitles.clear();
                            getline(ss, query, ' ');
                            authorSearch(authorIndex, query, foundTitles);
                            /**
                             * compare two MAPS remove items not in both
                             */
                            authorCompare(searchResults, foundTitles);
                        }
                    }
                    break;
                }

                vector<pair<int,string>> sortedSearchResults;
                sortSearchResults(searchResults, sortedSearchResults);

                /** prints search results */
                if(searchResults.size() > 0)
                {
                    cout << "\nHere are " << searchResults.size() << " articles in which contain the query \"" << toPrintQuery << "\" appear the most: \n";
                    printSearchResults(sortedSearchResults, metadata, 15, path);
                }
                else
                {
                    cout << "\nNo results for this query\n" << endl;
                }

                /*
                 * clears search results in preparation for next query
                 */
                searchResults.clear();
                sortedSearchResults.clear();
                break;
            }

            /**
             * Returns the amount of articles indexed (S.T.)
             */
            case 2:
            {
                cout << "\nThere are " << numArticles << " articles indexed.\n" << endl;
                break;
            }

            /**
             * Returns the average words per article (S.T.)
             */
            case 3:
            {
                cout << "\nThere are an average of " << averageWords << " words per article.\n" << endl;
                break;
            }

            /**
             * Returns the amount of WORDS in the index (S.T.)
             */
            case 4:
            {
                cout << "\nThere are a total of " << wordIndex.getNumNodes() << " unique words in the index.\n" << endl;
                break;
            }

            /**
             * Returns the amount of AUTHORS in the index (S.T.)
             */
            case 5:
            {
                cout << "\nThere are a total of " << authorIndex.getCount() << " unique authors in the index.\n" << endl;
                break;
            }


            case 6:
            {
                /**
                 * return 50 most common words (K.L.)
                 */
                vector<pair<int,string>> sortedCommonWords;
                getFiftyCommon(wordIndex, sortedCommonWords);

                break;
            }

            /**
             * Clears the index (K.L.)
             * Individual clear functions were made by KL and SL (respectively)
             */
            case 7:
            {
                cout << "\nClearing indexes...\n" << endl;

                wordIndex.clear();
                authorIndex.clear();

                cout << "\nIndexes have been cleared!\n" << endl;
                break;
            }

            /**
             * For parsing or opening a persistence file (S.T.)
             */
            case 8:
            {
                int eightSelection = 0;
                cout << "\nWould you like to parse a directory or open a persistence file?\n"
                     << "1. Parse\n2. Persistence File\n"
                     << "Selection: ";

                while(true) //handles incorrect inputs
                {
                    try
                    {
                        getline(cin, selectionString);
                        eightSelection = stoi(selectionString);
                        break;
                    }
                    catch(invalid_argument)
                    {
                        cin.clear();
                        cout << "\nInvalid selection please try again.\nSelect a number 1 - 2: ";
                    }
                }

                checkInput(eightSelection, 1, 2);

                switch(eightSelection)
                {
                    case 1:
                    {
                        cout << "Please give the absolute path to the directory you would like to parse:" << endl;
                        getline(cin, path);
                        cout << "\nBuilding your index...\n" << endl;
                        numArticles = buildIndexes(authorIndex, wordIndex, path, averageWords);
                        break;
                    }
                    case 2:
                    {
                        cout << "\nOpening the index..." << endl;
                        rapidjson::Document doc;
                        string persistencePath = "../persistence.json";
                        doc.Parse(getFile(persistencePath).c_str());

                        path = doc["path"].GetString();
                        numArticles = stoi(doc["numArticles"].GetString());
                        averageWords = stoi(doc["averageWords"].GetString());

                        for(int i = 0; i < doc["words"].Size(); i++)
                        {
                            Word word;
                            word.setWord(doc["words"][i]["string"].GetString());
                            word.setTotalFreq(stoi(doc["words"][i]["total frequency"].GetString()));
                            for(int j = 0; j < doc["words"][i]["ids"].Size(); j++)
                            {
                                word.addPaperID(doc["words"][i]["ids"][j]["id"].GetString());
                            }
                            wordIndex.insert(word);
                        }

                        for(int i = 0; i < doc["authors"].Size(); i++)
                        {
                            string name = doc["authors"][i]["name"].GetString();
                            Title titles;
                            for(int j = 0; j < doc["authors"][i]["ids"].Size(); j++)
                            {
                                titles.addTitle(doc["authors"][i]["ids"][j]["id"].GetString());
                            }
                            authorIndex.insert(name, titles);
                        }

                        cout << "\nIndex opened!\n" << endl;
                    }
                    break;
                }
                buildMetadata(metadata);
                break;
            }

            case 9:
            {
                cout << "\nSaving your index..." << endl;
                ofstream persistence("../persistence.json");
                persistence.clear();

                persistence << "{\n" << "\t\"path\": \"" << path << "\",\n"
                            << "\t\"numArticles\": \"" << numArticles << "\",\n"
                            << "\t\"averageWords\": \"" << averageWords << "\",\n";
                persistence << "\t\"words\": [" << endl;

                wordIndex.preOrderTraversal(persistence);

                persistence << "\t]," << endl;

                persistence << "\t\"authors\": [" << endl;

                authorIndex.outputJSON(persistence);

                persistence << "\t]\n}" << endl;

                persistence.close();

                cout << "\nIndex saved!\n" << endl;

                break;
            }

            case 0:
            {
                cout << "Thank you for using our COVID-19 database search engine!" << endl;
                queryRun = false;
                break;
            }
        }
    }
}

/**
 *
 * Creates by Kevin Leong
 */
void getFiftyCommon(DSTree<Word> &wordIndex,vector<pair<int, string>> &sortedCommonWords){
    cout << "\nThe 50 most frequent words are..." << endl;
    vector<Word> wordVector;
    wordIndex.toVector(wordVector);

    for(int i = 0; i < wordVector.size(); ++i){
        pair<int,string> newPair(wordVector.at(i).getTotalFreq(), wordVector.at(i).getWord());
        sortedCommonWords.push_back(newPair);
    }

    sort(sortedCommonWords.rbegin(), sortedCommonWords.rend());

    for(int i = 0; i < 49; ++i){
        cout << i + 1 << ") \"" << sortedCommonWords.at(i).second << "\" appears " << sortedCommonWords.at(i).first << " times." << endl;
    }
    cout << 50 << ") \"" << sortedCommonWords.at(49).second << "\" appears " << sortedCommonWords.at(49).first << " times.\n" << endl;
}

/**
 * Sorts the search results map into a vector (S.T.)
 * @param searchResults
 * @param sortedSearchResults
 */
void sortSearchResults(map<string, int> &searchResults, vector<pair<int,string>> &sortedSearchResults){
    auto it = searchResults.begin();

    while(it != searchResults.end())
    {
        sortedSearchResults.push_back(pair<int, string>(it->second, it->first));
        it++;
    }

    sort(sortedSearchResults.rbegin(), sortedSearchResults.rend());
}

/**
 * Prints the search results vector of pairs and its respective metadatas (S.T.)
 * @param searchResults
 * @param metadata
 * @param number
 * @param path
 */
void printSearchResults(vector<pair<int, string>> &searchResults, set<Metadata> &metadata, int number, string path) {
    int lessThanNumber = 0;
    for(int i = 0; i < searchResults.size(); i++)
    {
        if(lessThanNumber == number)
        {
            break;
        }
        else
        {
            Metadata toFind(searchResults[i].second);
            auto it = metadata.find(toFind);

            cout << "\n" << i + 1 << ". Title: " << it->getTitle() << "\n\t"
                 << "Authors: " << it->getAuthors() << "\n\t"
                 << "Publication Date: " << it->getPublishDate() << "\n\t"
                 << "Journal: " << it->getJournal()  <<  endl;
            lessThanNumber++;
        }
    }

    cout << "\nFound " << searchResults.size() << " files!\n" << endl;

    /**
     * For the selection of file preview (K.L.)
     */
    string articlePrev, selectionString;
    int choiceNum;
    int amtChoice = searchResults.size();
    if(searchResults.size() > 15){
        amtChoice = 15;
    }else;

    while(true){
        if(searchResults.size() == 0){
            break;
        }
        cout << "Please select a file to preview (1 - " << amtChoice << ") \n";
        cout << "Select 0 to EXIT" << endl;
        cout << "Selection: ";

        while(true) //handles incorrect inputs
        {
            try
            {
                getline(cin, selectionString);
                choiceNum = stoi(selectionString);
                break;
            }
            catch(invalid_argument)
            {
                cin.clear();
                cout << "Invalid selection please try again.\nSelect a number 0 - " << amtChoice << ": ";
            }
        }

        checkInput(choiceNum, 0, amtChoice);

        if(choiceNum == 0){
            break;
        }
        else {
            Metadata toFind(searchResults[choiceNum - 1].second);
            auto it = metadata.find(toFind);
            cout << it->getTitle()
                << "\n\tby: " << it->getAuthors() << ". \n";
            cout << "\tPublished in " << it->getJournal() << " on " << it->getPublishDate() << ". \n";
            cout << "Here is a 500 word excerpt: " << endl;
            printArticleExcerpt(path, it->getId());
        }

        break;
    }
    cout << endl;
}

/**
 * Prints the excerpt of selected article (K.L.)
 * @param path
 * @param specPath
 */
void printArticleExcerpt(const string& path, const string& specPath) {
    string filePath;
    filePath = path + "/" + specPath + ".json";

    rapidjson::Document doc;
    doc.Parse(getFile(filePath).c_str());

    int totalWords = 0;
    int charWrapCount = 0;
    int charWrapAmt = 120;

    if(doc.IsObject()) //checks that the document begins with an object
    {
        if (doc.HasMember("abstract"))
        {
            cout << "[ABSTRACT]: \n";
            cout << "\"";
            for (int i = 0; i < doc["abstract"].Size(); i++) {
                if (totalWords >= 500) {
                    break;
                }

                stringstream ss;
                string body = doc["abstract"][i]["text"].GetString();
                ss << body;

                string excerptWord;

                while (getline(ss, excerptWord, ' ')) {
                    if (totalWords >= 500) {
                        break;
                    }
                    charWrapCount += excerptWord.length();

                    if (charWrapCount >= charWrapAmt) {
                        cout << "\n";
                        charWrapCount = 0;
                    }
                    cout << excerptWord << " ";
                    totalWords++;
                }
                ss.clear();
            }
            if(totalWords < 500){
                cout << "\" \n";
                charWrapCount = 0;
            }
        }
        if (doc.HasMember("body_text") && totalWords < 500)
        {
            cout << "[BODY]: \n";
            cout << "\"";
            for (int i = 0; i < doc["body_text"].Size(); i++) {
                if (totalWords >= 500) {
                    break;
                }

                stringstream ss;
                string body = doc["body_text"][i]["text"].GetString();
                ss << body;

                string excerptWord;

                while (getline(ss, excerptWord, ' ')) {
                    if (totalWords >= 500) {
                        break;
                    }
                    charWrapCount += excerptWord.length();

                    if (charWrapCount >= charWrapAmt) {
                        cout << "\n";
                        charWrapCount = 0;
                    }
                    cout << excerptWord << " ";
                    totalWords++;
                }
                ss.clear();
            }
        }
    }
    cout << "... \"" << endl;
}

/**
 * Checks the input (S.T.)
 */
int checkInput(int &input, int low, int high)
{
    if(input < low || input > high) //makes sure input is in the correct range
    {
        cin.clear();
        cout << "\nInvalid selection please try again.\nSelect a number " << low
             << " - " << high << ": ";

        string selectionString;
        while(true)
        {
            try
            {
                getline(cin, selectionString);
                input = stoi(selectionString);
                break;
            }
            catch(invalid_argument)
            {
                cin.clear();
                cout << "\nInvalid selection please try again.\nSelect a number " << low
                     << " - " << high << " : ";
            }
        }
        checkInput(input, low, high);
    }
    else if(input >= low && input <= high)
    {
        return input;
    }
}

/**
 * Used for the author comparison (K.L.)
 * @param searchResults
 * @param foundTitles
 */
void authorCompare(map<string, int> &searchResults, map<string, int> &foundTitles)
{
    map<string, int> tempMap;
    auto it = searchResults.begin();
    if(foundTitles.size() != 0)
    {
        while(it != searchResults.end()){
            if(foundTitles.count(it->first) != 0){
                tempMap.insert(pair<string, int>(it->first, it->second));
            }
            it++;
        }
    }

    searchResults.clear();
    searchResults = tempMap;
}

/**
 * Used for NOT compare (K.L.)
 * @param searchResults
 * @param foundTitles
 */
void notCompare(map<string, int> &searchResults, map<string, int> &foundTitles)
{
    map<string, int> tempMap;
    auto it = foundTitles.begin();

    while(it != foundTitles.end()){
        if(searchResults.count(it->first) != 0){
            searchResults.erase(it->first);
        }
        it++;
    }
}
