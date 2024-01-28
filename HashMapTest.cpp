#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "HashMap.hpp"
#include "SolutionHashMap.hpp"

TEST_CASE("HashMap PUT operation", "[HashMap]") {
    HashMap<std::string, int64_t> myMap;
    
    SECTION("Inserting a new key-value pair") {
        myMap.put("foo", 42);
        REQUIRE(myMap.get("foo") == 42);
    }

    SECTION("Collision handling") {
        myMap.put("foo", 42);
        myMap.put("bar", 17);
        REQUIRE(myMap.get("foo") == 42);
        REQUIRE(myMap.get("bar") == 17);
    }
}

TEST_CASE("HashMap GET operation", "[HashMap]") {
    HashMap<std::string, int64_t> myMap;
    myMap.put("foo", 42);

    SECTION("Getting the value for an existing key") {
        REQUIRE(myMap.get("foo") == 42);
    }

    SECTION("Getting the value for a non-existing key") {
        REQUIRE(myMap.get("bar") == LONG_MIN);
    }
}

TEST_CASE("HashMap DEL operation", "[HashMap]") {
    HashMap<std::string, int64_t> myMap;
    myMap.put("foo", 42);

    SECTION("Deleting an existing key") {
        myMap.del("foo");
        REQUIRE(myMap.get("foo") == LONG_MIN);
    }

    SECTION("Deleting a non-existing key") {
        myMap.del("bar");
        REQUIRE(myMap.get("bar") == LONG_MIN);
    }
}

TEST_CASE("HashMap operations", "[HashMap]") {

    SECTION("Test 2") {
        Test test;
        test.test2();
    }

    SECTION("Test 3") {
        Test test;
        test.test3();
    }

    SECTION("Test 4") {
        Test test;
        test.test4();
    }

    SECTION("Test 5") {
        Test test;
        test.test5();
    }

    SECTION("Test 6") {
        Test test;
        test.test6();
    }
}