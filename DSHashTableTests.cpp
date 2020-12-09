//
// Created by Sammy Timmins on 11/15/20.
//

/**
 * All made by Sam Timmins
 */
#include <string>
#include "catch.hpp"
#include "DSHashTable.h"

TEST_CASE("DSHashTable Tests with primitive data types")
{
    DSHashTable<int, int> integers;
    DSHashTable<int, char> intAndChar;
    DSHashTable<char, int> charAndInt;

    for(int i = 1; i <= 10; i++)
    {
        std::pair<int, int> insert(i, i);
        integers.insert(insert);
    }

    int x = 11;
    for(int i = 100001; i <= 100010; i++)
    {
        std::pair<int, int> insert(i, x);
        integers.insert(insert);
        x++;
    }

    char loop = 'a';
    for(int i = 1; i <= 10; i++)
    {
        std::pair<int, char> insert(i, loop);
        intAndChar.insert(insert);
        loop++;
    }

    for(int i = 100001; i <= 100010; i++)
    {
        std::pair<int, char> insert(i, loop);
        intAndChar.insert(insert);
        loop++;
    }

    x = 1;
    for(char i = 'a'; i <= 'j'; i++)
    {
        std::pair<char, int> insert(i, x);
        charAndInt.insert(insert);
        x++;
    }
    integers.insert(20, 25);
    SECTION("insert() and get() with primitives")
    {
        REQUIRE((integers.get(1) == 1));
        REQUIRE((integers.get(2) == 2));
        REQUIRE((integers.get(3) == 3));
        REQUIRE((integers.get(4) == 4));
        REQUIRE((integers.get(5) == 5));
        REQUIRE((integers.get(6) == 6));
        REQUIRE((integers.get(7) == 7));
        REQUIRE((integers.get(8) == 8));
        REQUIRE((integers.get(9) == 9));
        REQUIRE((integers.get(10) == 10));
        REQUIRE((integers.get(100001) == 11));
        REQUIRE((integers.get(100002) == 12));
        REQUIRE((integers.get(100003) == 13));
        REQUIRE((integers.get(100004) == 14));
        REQUIRE((integers.get(100005) == 15));
        REQUIRE((integers.get(100006) == 16));
        REQUIRE((integers.get(100007) == 17));
        REQUIRE((integers.get(100008) == 18));
        REQUIRE((integers.get(100009) == 19));
        REQUIRE((integers.get(100010) == 20));
        REQUIRE((integers.get(20) == 25));

        REQUIRE((intAndChar.get(1) == 'a'));
        REQUIRE((intAndChar.get(2) == 'b'));
        REQUIRE((intAndChar.get(3) == 'c'));
        REQUIRE((intAndChar.get(4) == 'd'));
        REQUIRE((intAndChar.get(5) == 'e'));
        REQUIRE((intAndChar.get(6) == 'f'));
        REQUIRE((intAndChar.get(7) == 'g'));
        REQUIRE((intAndChar.get(8) == 'h'));
        REQUIRE((intAndChar.get(9) == 'i'));
        REQUIRE((intAndChar.get(10) == 'j'));
        REQUIRE((intAndChar.get(100001) == 'k'));
        REQUIRE((intAndChar.get(100002) == 'l'));
        REQUIRE((intAndChar.get(100003) == 'm'));
        REQUIRE((intAndChar.get(100004) == 'n'));
        REQUIRE((intAndChar.get(100005) == 'o'));
        REQUIRE((intAndChar.get(100006) == 'p'));
        REQUIRE((intAndChar.get(100007) == 'q'));
        REQUIRE((intAndChar.get(100008) == 'r'));
        REQUIRE((intAndChar.get(100009) == 's'));
        REQUIRE((intAndChar.get(100010) == 't'));

        REQUIRE((charAndInt.get('a') == 1));
        REQUIRE((charAndInt.get('b') == 2));
        REQUIRE((charAndInt.get('c') == 3));
        REQUIRE((charAndInt.get('d') == 4));
        REQUIRE((charAndInt.get('e') == 5));
        REQUIRE((charAndInt.get('f') == 6));
        REQUIRE((charAndInt.get('g') == 7));
        REQUIRE((charAndInt.get('h') == 8));
        REQUIRE((charAndInt.get('i') == 9));
        REQUIRE((charAndInt.get('j') == 10));

        integers.get(1) = 2;
        intAndChar.get(1) = 'b';
        charAndInt.get('a') = 2;

        REQUIRE((integers.get(1) == 2));
        REQUIRE((intAndChar.get(1) == 'b'));
        REQUIRE((charAndInt.get('a') == 2));
    }

    SECTION("Overloaded [] operator")
    {
        REQUIRE((integers[1] == 1));
        REQUIRE((integers[2] == 2));
        REQUIRE((integers[3] == 3));
        REQUIRE((integers[4] == 4));
        REQUIRE((integers[5] == 5));
        REQUIRE((integers[6] == 6));
        REQUIRE((integers[7] == 7));
        REQUIRE((integers[8] == 8));
        REQUIRE((integers[9] == 9));
        REQUIRE((integers[10] == 10));
        REQUIRE((integers[100001] == 11));
        REQUIRE((integers[100002] == 12));
        REQUIRE((integers[100003] == 13));
        REQUIRE((integers[100004] == 14));
        REQUIRE((integers[100005] == 15));
        REQUIRE((integers[100006] == 16));
        REQUIRE((integers[100007] == 17));
        REQUIRE((integers[100008] == 18));
        REQUIRE((integers[100009] == 19));
        REQUIRE((integers[100010] == 20));

        REQUIRE((intAndChar[1] == 'a'));
        REQUIRE((intAndChar[2] == 'b'));
        REQUIRE((intAndChar[3] == 'c'));
        REQUIRE((intAndChar[4] == 'd'));
        REQUIRE((intAndChar[5] == 'e'));
        REQUIRE((intAndChar[6] == 'f'));
        REQUIRE((intAndChar[7] == 'g'));
        REQUIRE((intAndChar[8] == 'h'));
        REQUIRE((intAndChar[9] == 'i'));
        REQUIRE((intAndChar[10] == 'j'));
        REQUIRE((intAndChar[100001] == 'k'));
        REQUIRE((intAndChar[100002] == 'l'));
        REQUIRE((intAndChar[100003] == 'm'));
        REQUIRE((intAndChar[100004] == 'n'));
        REQUIRE((intAndChar[100005] == 'o'));
        REQUIRE((intAndChar[100006] == 'p'));
        REQUIRE((intAndChar[100007] == 'q'));
        REQUIRE((intAndChar[100008] == 'r'));
        REQUIRE((intAndChar[100009] == 's'));
        REQUIRE((intAndChar[100010] == 't'));

        REQUIRE((charAndInt['a'] == 1));
        REQUIRE((charAndInt['b'] == 2));
        REQUIRE((charAndInt['c'] == 3));
        REQUIRE((charAndInt['d'] == 4));
        REQUIRE((charAndInt['e'] == 5));
        REQUIRE((charAndInt['f'] == 6));
        REQUIRE((charAndInt['g'] == 7));
        REQUIRE((charAndInt['h'] == 8));
        REQUIRE((charAndInt['i'] == 9));
        REQUIRE((charAndInt['j'] == 10));

        integers[1] = 2;
        intAndChar[1] = 'b';
        charAndInt['a'] = 2;

        REQUIRE((integers[1] == 2));
        REQUIRE((intAndChar[1] == 'b'));
        REQUIRE((charAndInt['a'] == 2));
    }

    SECTION("find() with primitives")
    {
        REQUIRE((integers.find(1, 1)));
        REQUIRE(!(integers.find(11, 1)));
        REQUIRE(!(integers.find(1, 2)));

        REQUIRE((intAndChar.find(1, 'a')));
        REQUIRE(!(intAndChar.find(11, 'a')));
        REQUIRE(!(intAndChar.find(1, 'b')));

        REQUIRE((charAndInt.find('a', 1)));
        REQUIRE(!(charAndInt.find('z', 1)));
        REQUIRE(!(charAndInt.find('a', 2)));
    }

    SECTION("remove() with primitives")
    {
        std::pair<int, int> removeIntegers(1,1);
        integers.remove(removeIntegers);
        REQUIRE(!(integers.find(1,1)));
        REQUIRE((integers.getCount() == 20));

        std::pair<int, char> removeIntAndChar(1, 'a');
        intAndChar.remove(removeIntAndChar);
        REQUIRE(!(intAndChar.find(1, 'a')));
        REQUIRE((intAndChar.getCount() == 19));

        std::pair<char, int> removeCharAndInt('a', 1);
        charAndInt.remove(removeCharAndInt);
        REQUIRE(!(charAndInt.find('a', 1)));
        REQUIRE((charAndInt.getCount() == 9));
    }

    SECTION("getSize() with primitives")
    {
        REQUIRE((integers.getSize() == 50000));
        REQUIRE((intAndChar.getSize() == 50000));
        REQUIRE((charAndInt.getSize() == 50000));
    }

    SECTION("getCount() with primitives")
    {
        REQUIRE((integers.getCount() == 21));
        REQUIRE((intAndChar.getCount() == 20));
        REQUIRE((charAndInt.getCount() == 10));
    }

    SECTION("Copy constructor with primitives")
    {
        DSHashTable<int, int> integersCopy(integers);
        DSHashTable<int, char> intAndCharCopy(intAndChar);
        DSHashTable<char, int> charAndIntCopy(charAndInt);

        REQUIRE((integers.find(1, 1)));
        REQUIRE(!(integers.find(11, 1)));
        REQUIRE(!(integers.find(1, 2)));

        REQUIRE((intAndChar.find(1, 'a')));
        REQUIRE(!(intAndChar.find(11, 'a')));
        REQUIRE(!(intAndChar.find(1, 'b')));

        REQUIRE((charAndInt.find('a', 1)));
        REQUIRE(!(charAndInt.find('z', 1)));
        REQUIRE(!(charAndInt.find('a', 2)));
    }

    SECTION("Overloaded assignment operator with primitives")
    {
        DSHashTable<int, int> integersCopy;
        DSHashTable<int, char> intAndCharCopy;
        DSHashTable<char, int> charAndIntCopy;

        integersCopy = integers;
        intAndCharCopy = intAndChar;
        charAndIntCopy = charAndInt;

        REQUIRE((integers.find(1, 1)));
        REQUIRE(!(integers.find(11, 1)));
        REQUIRE(!(integers.find(1, 2)));

        REQUIRE((intAndChar.find(1, 'a')));
        REQUIRE(!(intAndChar.find(11, 'a')));
        REQUIRE(!(intAndChar.find(1, 'b')));

        REQUIRE((charAndInt.find('a', 1)));
        REQUIRE(!(charAndInt.find('z', 1)));
        REQUIRE(!(charAndInt.find('a', 2)));
    }

    SECTION("testing resize() function")
    {
        REQUIRE((integers.getHash(100001) == 1));
        for(int i = 100011; i < 200000; i++)
        {
            std::pair<int, int> insert(i, i);
            integers.insert(insert);
        }
        REQUIRE((integers.getSize() == 200000));
        REQUIRE((integers.getHash(100001) == 100001));
        REQUIRE((integers.getCount() == 100010));
    }
}

TEST_CASE("DSHashTable with objects")
{
    DSHashTable<std::string, std::string> strings;
    std::pair<std::string, std::string> insert("what is", "up");
    strings.insert(insert);
    std::pair<std::string, std::string> insert2("", "");
    strings.insert(insert2);
    strings.insert("hello", "there");
    strings.insert("hey", "there");
    strings.insert("please", "work");

    SECTION("insert() and get() with objects")
    {
        REQUIRE((strings.get("hello") == "there"));
        REQUIRE((strings.get("hey") == "there"));
        REQUIRE((strings.get("please") == "work"));
        REQUIRE((strings.get("what is") == "up"));
        REQUIRE((strings.get("") == ""));
    }

    SECTION("Overloaded [] operator with objects")
    {
        REQUIRE((strings["hello"] == "there"));
        REQUIRE((strings["hey"] == "there"));
        REQUIRE((strings["please"] == "work"));
        REQUIRE((strings["what is"] == "up"));
        REQUIRE((strings[""] == ""));
    }

    SECTION("find() with objects")
    {
        REQUIRE(strings.find("hello"));
        REQUIRE(strings.find("hey"));
        REQUIRE(strings.find("please"));
        REQUIRE(strings.find("what is"));
        REQUIRE(strings.find(""));
        REQUIRE(strings.find("hello", "there"));
        REQUIRE(strings.find("hey", "there"));
        REQUIRE(strings.find("what is", "up"));
        REQUIRE(strings.find("please", "work"));
        REQUIRE(strings.find("", ""));
        REQUIRE(!strings.find("hello", "work"));
        REQUIRE(!strings.find("", "there"));
    }

    SECTION("remove() with objects")
    {
        std::pair<std::string, std::string> remove("hello", "there");
        strings.remove(remove);
        REQUIRE(!strings.find("hello", "there"));
        REQUIRE((strings.getCount() == 4));

        remove.first = "";
        remove.second = "";
        strings.remove(remove);
        REQUIRE(!strings.find("", ""));
        REQUIRE((strings.getCount() == 3));
    }

    SECTION("getSize() with objects")
    {
        REQUIRE((strings.getSize() == 50000));
    }

    SECTION("getCount() with objects")
    {
        REQUIRE((strings.getCount() == 5));
    }

    SECTION("Copy constructor with objects")
    {
        DSHashTable<std::string, std::string> stringsCopy(strings);

        REQUIRE(stringsCopy.find("hello"));
        REQUIRE(stringsCopy.find("hey"));
        REQUIRE(stringsCopy.find("please"));
        REQUIRE(stringsCopy.find("what is"));
        REQUIRE(stringsCopy.find(""));
        REQUIRE(stringsCopy.find("hello", "there"));
        REQUIRE(stringsCopy.find("hey", "there"));
        REQUIRE(stringsCopy.find("what is", "up"));
        REQUIRE(stringsCopy.find("please", "work"));
        REQUIRE(stringsCopy.find("", ""));
        REQUIRE(!stringsCopy.find("hello", "work"));
        REQUIRE(!stringsCopy.find("", "there"));
    }

    SECTION("Overloaded assignment operator with objects")
    {
        DSHashTable<std::string, std::string> stringsCopy;
        stringsCopy = strings;

        REQUIRE(stringsCopy.find("hello"));
        REQUIRE(stringsCopy.find("hey"));
        REQUIRE(stringsCopy.find("please"));
        REQUIRE(stringsCopy.find("what is"));
        REQUIRE(stringsCopy.find(""));
        REQUIRE(stringsCopy.find("hello", "there"));
        REQUIRE(stringsCopy.find("hey", "there"));
        REQUIRE(stringsCopy.find("what is", "up"));
        REQUIRE(stringsCopy.find("please", "work"));
        REQUIRE(stringsCopy.find("", ""));
        REQUIRE(!stringsCopy.find("hello", "work"));
        REQUIRE(!stringsCopy.find("", "there"));
    }
}