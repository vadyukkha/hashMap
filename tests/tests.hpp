#pragma once
#ifndef TESTS_TESTS_HPP
#define TESTS_TESTS_HPP

#include "../include/HashMap.hpp"

// Class for testing the HashMap
class Test {
 private:
    // Check if two strings are valid by comparing character frequencies
    bool isValid(std::string s, std::string t) {
        if (s.length() != t.length())
            return false;

        HashMap<std::string, int64_t> ls;
        HashMap<std::string, int64_t> lt;

        for (size_t i = 0; i < s.length(); i++) {
            std::string tempChar(1, s[i]);
            std::string tempCharT(1, t[i]);
            ls.put(tempChar, 0);
            lt.put(tempCharT, 0);
        }

        for (size_t i = 0; i < s.length(); i++) {
            std::string tempChar(1, s[i]);
            ls[tempChar]++;
        }

        for (size_t i = 0; i < t.length(); i++) {
            std::string tempCharT(1, t[i]);
            lt[tempCharT]++;
        }

        return ls.isEqual(lt);
    }

 public:
    void test1() {
        std::cout << "Test 1 start" << std::endl;

        HashMap<std::string, int64_t> table;

        table.put("foo", 12);
        table.put("foo", 15);
        table.put("bar", 15);

        table.dump();

        table.del("bar");

        table.dump();

        table.put("bar", 78);

        table.dump();

        table.put("el0", 15);
        table.put("el1", 15);
        table.put("el2", 15);
        table.put("el3", 15);

        table.dump();

        table.put("el5", 15);

        table.dump();

        table.put("el4", 15);
        table.put("el6", 15);
        table.put("el7", 15);

        table.del("el0");
        table.del("el1");
        table.del("el2");
        table.del("el3");
        table.del("el4");
        table.del("el6");
        table.del("el7");

        table.put("new_new", 15);

        table.get("bar");

        table.dump();
        std::cout << "Test 1 end." << std::endl;
    }

    void test2() {
        std::cout << "Test 2:\n" << std::endl;
        std::string str1 = "555", str2 = "555";

        std::cout << "First string: " << str1 << std::endl;
        std::cout << "Second string: " << str2 << std::endl;

        std::cout << "Result: ";
        if (isValid(str1, str2)) {
            std::cout << "Correct" << std::endl;
        } else {
            std::cout << "Uncorrect" << std::endl;
        }
    }

    void test3() {
        std::cout << "Test 3:\n" << std::endl;
        HashMap<std::string, int64_t> table;
        HashMap<std::string, int64_t> table2;

        table["foo"] = 12;
        int64_t val = table["foo"];
        std::cout << "(table1)key foo : val = " << val << std::endl;
        table["foo"]++;
        table["foo"]+=1;
        table["foo"]--;
        std::cout << "(table1)key foo : val = " << table["foo"] << std::endl;

        table2["foo"] = 12;
        table2["foo"]++;
        table2["foo"]+=1;
        std::cout << "(table2)key foo : val = " << table2["foo"] << std::endl;

        std::string printEquals = (table == table2) ? "Equals" : "No equals";
        std::cout << "(table1)==(table2)? " << printEquals << std::endl;

        std::cout << "(table1)foo + (table2)foo = " << table["foo"] + table2["foo"] << std::endl;
    }

    void test4() {
        std::cout << "Test 4:\n" << std::endl;
        HashMap<std::string, std::string> table;
        table["dog"] = "WOW";
        table["cat"] = "MEOW";
        std::cout << "key: sheep - value: " << table.get("sheep") << std::endl;
        std::cout << "key: 1234 - value: " << table.get("1234") << std::endl;
    }
};

#endif  // TESTS_TESTS_HPP
