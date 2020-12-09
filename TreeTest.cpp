//
// Created by Kevin Leong on 11/15/20.
//

/**
 * All tests made by Kevin Leong
 */

#include "catch.hpp"
#include "DSTree.h"
#include "Word.h"

TEST_CASE("Word Object"){
    Word word1("Word");
    Word word2("Bird");
    Word word3("Zerd");

    word1.addPaperID("123");
    word2.addPaperID("456");
    word3.addPaperID("789");

    SECTION("Copy Constructor & Assignment Op"){
        Word word4(word1);
        REQUIRE(word4 == word1);

        Word word5(word2);
        REQUIRE(word5 == word2);

        Word word6 = word5;
        REQUIRE(word6 == word2);
    }
    SECTION("Comparison Operators"){
        REQUIRE(word1 > word2);
        REQUIRE(word2 < word3);
        REQUIRE(word3 > word1);

        Word word4("A");
        Word word5("Aa");
        Word word6("a");
        Word word7("!A");

        REQUIRE(word4 < word5);
        REQUIRE(word4 < word6);
        REQUIRE(word4 < word5);
        REQUIRE(word6 > word7);
        REQUIRE(word7 < word5);
    }
    SECTION("Adding PaperID and Get Title List"){
        word1.addPaperID("555");
        REQUIRE(word1.getTitleList().size() == 2);
        REQUIRE(word1.getTitleList().at("123") == 0);
        word1.getTitleList()["555"]++;
        REQUIRE(word1.getTitleList().at("555") == 1);

        word2.addPaperID("ABC");
        REQUIRE(word2.getTitleList().size() == 2);
        REQUIRE(word2.getTitleList().at("456") == 0);
        word2.getTitleList()["ABC"] = 123;
        REQUIRE(word2.getTitleList().at("ABC") == 123);

        word3.addPaperID("!!!");
        REQUIRE(word3.getTitleList().size() == 2);
        REQUIRE(word3.getTitleList().at("789") == 0);
        word3.getTitleList()["!!!"] = 0;
        REQUIRE(word3.getTitleList().at("!!!") == 0);
    }
}

TEST_CASE("DSTree Test") {
    DSTree<int> intTree;
    intTree.insert(5);
    intTree.insert(7);
    intTree.insert(1);

    DSTree<Word> wordTree;
    Word word1("Cap");
    Word word2("Bap");
    Word word3("Aap");
    word1.addPaperID("111");
    word2.addPaperID("222");
    word3.addPaperID("333");
    word1.getTitleList()["111"]++;
    word2.getTitleList()["222"] = 10;
    word3.getTitleList()["333"] = 100;
    
    wordTree.insert(word1);
    wordTree.insert(word2);
    wordTree.insert(word3);

    SECTION("Insert") {
        REQUIRE(intTree.getNumNodes() == 3);
        intTree.insert(1);
        intTree.insert(7);
        intTree.insert(20);
        intTree.insert(6);
        intTree.insert(25);
        intTree.insert(19);
        REQUIRE(intTree.getNumNodes() == 9);



        REQUIRE(wordTree.getNumNodes() == 3);
        Word word4("Trees");
        Word word5("A");
        Word word6("Apple");
        wordTree.insert(word4);
        wordTree.insert(word5);
        wordTree.insert(word6);
        REQUIRE(wordTree.getNumNodes() == 6);
    }

    SECTION("Find") {
        REQUIRE(intTree.find(1) == true);
        REQUIRE(intTree.find(7) == true);
        REQUIRE(intTree.find(5) == true);

        REQUIRE(intTree.find(100) == false);

        REQUIRE(wordTree.find("Cap") == true);
        REQUIRE(wordTree.find("Bap") == true);
        REQUIRE(wordTree.find("Aap") == true);

        REQUIRE(wordTree.find("Kevin") == false);
        REQUIRE(wordTree.find("CAP") == false);
    }

    SECTION("Remove"){
        REQUIRE(intTree.find(1) == true);
        REQUIRE(intTree.getNumNodes() == 3);
        intTree.remove(1);
        REQUIRE(intTree.find(1) == false);
        REQUIRE(intTree.getNumNodes() == 2);

        REQUIRE(intTree.find(7) == true);
        REQUIRE(intTree.getNumNodes() == 2);
        intTree.remove(7);
        REQUIRE(intTree.find(7) == false);
        REQUIRE(intTree.getNumNodes() == 1);

        intTree.remove(100); //should skip
        REQUIRE(intTree.getNumNodes() == 1);

        REQUIRE(wordTree.find("Cap") == true);
        REQUIRE(wordTree.getNumNodes() == 3);
        wordTree.remove("Cap");
        REQUIRE(wordTree.find("Cap") == false);
        REQUIRE(wordTree.getNumNodes() == 2);

        REQUIRE(wordTree.find("Bap") == true);
        REQUIRE(wordTree.getNumNodes() == 2);
        wordTree.remove("Bap");
        REQUIRE(wordTree.find("Bap") == false);
        REQUIRE(wordTree.getNumNodes() == 1);
    }

    SECTION("Get") {
        REQUIRE(intTree.get(1) == 1);
        REQUIRE(intTree.get(5) == 5);
        REQUIRE(intTree.get(7) == 7);

        REQUIRE(wordTree.get("Cap").getWord() == "Cap");
        REQUIRE(wordTree.get("Bap").getWord() == "Bap");
        REQUIRE(wordTree.get("Aap").getWord() == "Aap");

        REQUIRE(wordTree.get("Cap").getTitleList()["111"] == 1);
        REQUIRE(wordTree.get("Bap").getTitleList()["222"] == 10);
        REQUIRE(wordTree.get("Aap").getTitleList()["333"] == 100);
    }

    SECTION("To Vector"){
        vector<int> intVector;
        intTree.toVector(intVector);

        REQUIRE(intVector.size() == wordTree.getNumNodes());
    }

    SECTION("Copy Constructor"){
        DSTree<int> newInt(intTree);
        REQUIRE(newInt.getNumNodes() == intTree.getNumNodes());
        REQUIRE(newInt.find(5) == true);
        REQUIRE(newInt.find(7) == true);
        REQUIRE(newInt.find(1) == true);
        REQUIRE(newInt.find(50) == false);

        DSTree<Word> newWord(wordTree);
        REQUIRE(newWord.getNumNodes() == wordTree.getNumNodes());
        REQUIRE(newWord.find("Cap") == true);
        REQUIRE(newWord.find("Bap") == true);
        REQUIRE(newWord.find("Aap") == true);
        REQUIRE(newWord.find("Jeffe") == false);
    }
    SECTION("Equals Operator"){

        DSTree<int> newInt = intTree;
        REQUIRE(newInt.getNumNodes() == intTree.getNumNodes());
        REQUIRE(newInt.find(5) == true);
        REQUIRE(newInt.find(7) == true);
        REQUIRE(newInt.find(1) == true);
        REQUIRE(newInt.find(50) == false);

        DSTree<Word> newWord(wordTree);
        REQUIRE(newWord.getNumNodes() == wordTree.getNumNodes());
        REQUIRE(newWord.find("Cap") == true);
        REQUIRE(newWord.find("Bap") == true);
        REQUIRE(newWord.find("Aap") == true);
        REQUIRE(newWord.find("Jeffe") == false);
    }
}
