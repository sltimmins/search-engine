//
// Created by Sammy Timmins on 11/19/20.
//

#include "Index.h"
#include <ctype.h>

void removeTrainingPunct();

using namespace std;
using namespace rapidjson;
/**
 * Creates the filler words set (K.L.)
 */
void makeFillerSet(set<string> &fillerSet)
{
    string fillerWord;
    ifstream fin;
    fin.open("../stopwords.txt");

    while(getline(fin, fillerWord)){
        fillerSet.insert(fillerWord);
    }
}

/**
 * Removes the trailing Punctuation (K.L)
 */
void removeTrailingPunct(string& word) {
    for(int i = word.length() - 1; i > 0; i--)
    {
        if(!isalpha(word[i]) && !isdigit(word[i])){
            word.erase(i, 1);
        } else {
            break;
        }
    }
}

/**
 * Removes the leading Punctuation (K.L)
 */
void removeLeadingPunct(string& word) {

    while(!isalpha(word[0])){
        if(word.length() == 0){
            break;
        }
        word.erase(0,1);
    }
}

/**
 * Removes the in-between Punctuation (K.L)
 */
void punctDestroyer(string& word) {
    for(int i = 0; i < word.length(); ++i){
        if(!isascii(word[i])){
            word.erase(i,1);
            i--;
        }
        if(word[i] == '"'){
            word.erase(i, 1);
            i--;
        }
        if(word[i] == '\?'){
            word.erase(i, 1);
            i--;
        }
        if(word[i] == '\\'){
            word.erase(i, 1);
            i--;
        }
    }
}

/**
 * Goes through each word and transform the word to lowercase (S.T.)
 * @param word
 */
void toLower(string& word)
{
    transform(word.begin(), word.end(), word.begin(), ::tolower);
}

/**
 * loops through the document directory
 * parses each JSON file as it loops
 * populates both author and word indexes
 */

int buildIndexes(DSHashTable<string, Title> &authorIndex, DSTree<Word> &wordIndex, string &path, int &average)
{
    string filePath, paperID;
    DIR *directoryPath;
    struct dirent *dirp;
    int totalWords = 0;

    directoryPath = opendir(path.c_str());

    if(directoryPath == nullptr)
    {
        cout << "Error opening file" << endl;
        exit(0);
    }

    int numArticles = 0;

    while((dirp = readdir(directoryPath))) //loops through the directory of files
    {
        numArticles++;
        filePath = path + "/" + dirp->d_name;

        Document doc;
        doc.Parse(getFile(filePath).c_str()); //parses json file into tree

        if(doc.IsObject()) //checks that the document begins with an object
        {
            if(doc.HasMember("paper_id")) //checks that the file has an ID
            {
                paperID = doc["paper_id"].GetString();
            }
            if(doc["metadata"].HasMember("authors")) //checks that the file has metadata member
            {
                for(int i = 0; i < doc["metadata"]["authors"].Size(); i++) //loops through the authors json array
                {
                    string author = doc["metadata"]["authors"][i]["last"].GetString(); //sets author name to last name from json
                    toLower(author);
                    if(!authorIndex.find(author)) //if the author is not already in the table, adds author to table and adds id to title vector
                    {
                        Title title;
                        title.addTitle(paperID);
                        pair<string , Title> pair(author, title);
                        authorIndex.insert(pair);
                    }
                    else //if the author is already in the table then add the paper ID to the ID vector
                    {
                        authorIndex[author].addTitle(paperID);
                    }
                }
            }

            /**
             * Creates a set of filler words (K.L.)
             */
            set<string> fillerSet;
            makeFillerSet(fillerSet);

            /**
             * adding words from title (S.T.)
             */
            if(doc["metadata"].HasMember("title"))
            {
                stringstream ss;

                string title = doc["metadata"]["title"].GetString();
                ss << title;
                string singleWord;
                while(getline(ss, singleWord, ' '))
                {
                    if((fillerSet.count(singleWord) == 0))
                    {
                        removeLeadingPunct(singleWord);
                        removeTrailingPunct(singleWord);
                        if(singleWord.length() == 0){
                            break;
                        }

                        punctDestroyer(singleWord);

                        Porter2Stemmer::stem(singleWord); //stemmer from: https://bitbucket.org/smassung/porter2_stemmer/src/master/

                        toLower(singleWord);

                        if(wordIndex.find(singleWord))
                        {
                            wordIndex.get(singleWord).getTitleList()[paperID]++;
                        }
                        else
                        {
                            wordIndex.insert(singleWord);
                            wordIndex.get(singleWord).addPaperID(paperID);
                            wordIndex.get(singleWord).getTitleList()[paperID]++;
                        }

                        /** adds one to totalFreq of Word */
                        wordIndex.get(singleWord).iterTotalFreq();
                    }
                }
            }

            /**
             * Adding words from abstract (K.L.)
             */
            if(doc.HasMember("abstract"))
            {
                for(int i = 0; i < doc["abstract"].Size(); i++)
                {
                    stringstream ss;
                    string abstract = doc["abstract"][i]["text"].GetString();
                    ss << abstract;

                    string singleWord;
                    while(getline(ss, singleWord, ' ')){
                        totalWords++;
                        if((fillerSet.count(singleWord) == 0))
                        {
                            removeLeadingPunct(singleWord);
                            removeTrailingPunct(singleWord);
                            if(singleWord.length() == 0){
                                break;
                            }
                            punctDestroyer(singleWord);

                            Porter2Stemmer::stem(singleWord); //stemmer from: https://bitbucket.org/smassung/porter2_stemmer/src/master/

                            toLower(singleWord);

                            if(wordIndex.find(singleWord))
                            {
                                wordIndex.get(singleWord).getTitleList()[paperID]++;
                            }
                            else
                            {
                                wordIndex.insert(singleWord);
                                wordIndex.get(singleWord).addPaperID(paperID);
                                wordIndex.get(singleWord).getTitleList()[paperID]++;
                            }

                            /** adds one to totalFreq of Word */
                            wordIndex.get(singleWord).iterTotalFreq();

                        }
                    }
                }
            }
            /**
             * Adding words from body text (K.L.)
             */
            if(doc.HasMember("body_text"))
            {
                for(int i = 0; i < doc["body_text"].Size(); i++)
                {
                    stringstream ss;
                    string body = doc["body_text"][i]["text"].GetString();
                    ss << body;

                    string singleWord;
                    while(getline(ss, singleWord, ' ')){
                        totalWords++;

                        /**
                         * for body text excerpt
                         */
                        int btWordCount = 0;
                        string excerptBody;
                        if(btWordCount < 300){
                            excerptBody += singleWord;
                        }

                        if((fillerSet.count(singleWord) == 0)){

                            removeLeadingPunct(singleWord);
                            removeTrailingPunct(singleWord);
                            if(singleWord.length() == 0){
                                break;
                            }
                            punctDestroyer(singleWord);

                            Porter2Stemmer::stem(singleWord); //stemmer from: https://bitbucket.org/smassung/porter2_stemmer/src/master/

                            toLower(singleWord);

                            if(wordIndex.find(singleWord)){
                                wordIndex.get(singleWord).getTitleList()[paperID]++;
                            } else {
                                wordIndex.insert(singleWord);
                                wordIndex.get(singleWord).addPaperID(paperID);
                                wordIndex.get(singleWord).getTitleList()[paperID]++;
                            }

                            /** adds one to totalFreq of Word */
                            wordIndex.get(singleWord).iterTotalFreq();
                        }
                    }
                }
            }
        }
    }
    cout << "\nIndexes built!\n" << endl;
    average = totalWords / numArticles;
    return numArticles;
}

/**
 * Creates metadata for docs (S.T.)
 * @param metadata
 */
void buildMetadata(set<Metadata> &metadata)
{
    rapidcsv::Document doc("../metadata-cs2341.csv");

    vector<string> ids = doc.GetColumn<string>("sha");
    vector<string> titles = doc.GetColumn<string>("title");
    vector<string> publishDates = doc.GetColumn<string>("publish_time");
    vector<string> authors = doc.GetColumn<string>("authors");
    vector<string> journals = doc.GetColumn<string>("journal");

    for(int i = 0; i < ids.size(); i++)
    {
        Metadata data(ids[i], titles[i], publishDates[i], authors[i], journals[i]);

        metadata.insert(data);
    }
}

/**
 * gets and returns the file path for each file in the directory (S.T.)
 */
string getFile(string &filePath)
{
    ifstream file;
    file.open(filePath.c_str());

    string json, line;
    while(getline(file, line))
    {
        json += line;
    }
    file.close();
    return json;
}