// Copyright 2024 by Contributors
#pragma once
#ifndef INCLUDE_HASHMAP_HPP
#define INCLUDE_HASHMAP_HPP

#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <string>

template <typename key_type, typename value_type>
class Node {
 public:
    key_type key_;
    value_type value_;
    bool state_;

    // Constructor
    Node(const key_type& key, value_type value);
    // Default constructor
    Node();

    void updateValue(const key_type& newKey, value_type newValue);
    bool empty() const;
    
    // Operator overloading
    friend std::ostream& operator<<(std::ostream& os, const Node<key_type, value_type>& node);
};

template <typename key_type, typename value_type>
class HashMap {
 private:
    double rehashSize_;
    size_t size_;
    size_t sizeAllNonNullptr_;
    key_type defualtKey_;
    value_type defualtValue_;
    std::vector<Node<key_type, value_type>*> arr_;

    // Hash function for generating indices based on a string key
    size_t hashGenerate(const std::string& string, size_t tableSize, size_t key) const;

    // Hash function for generating indices based on an integer key
    size_t hashGenerate(const int64_t& integer, size_t tableSize, size_t key) const;

    // First hash function using the current table size
    size_t hash1(const key_type& key) const;

    // Second hash function using the current table size
    size_t hash2(const key_type& key) const;

    // Find an empty index for the given key using double hashing
    size_t findEmptyIndex(const key_type& key) const;

    // Get a index to put in the hash map
    size_t findIndex(const key_type& key) const;

    void _add(const key_type& key, value_type value);

    // Resize the hash table when it becomes too full
    void resize();

    // Rehash the full hash table
    void rehash();

 public:
    // Constructor, set default values
    HashMap();

    // Set default value for constructor
    void setDefaultValue();

    // Set default key for constructor
    void setDefaultKey();

    // Operator overloading
    value_type& operator[](const key_type& key);

    // Comparison operator
    bool operator==(const HashMap& hashMap) const;

    // Comparison operator
    bool operator!=(const HashMap& hashMap) const;

    // Operator output
    friend std::ostream& operator<<(std::ostream& os, const HashMap<key_type, value_type>& hashMap);

    // Insert a key-value pair into the hash table
    void put(const key_type& key, value_type value);

    // Delete a key from the hash table
    void del(const key_type& key);

    // Get the value associated with a key from the hash table
    value_type get(const key_type& key) const;

    // Check if the current hash table is equal to another hash table
    bool isEqual(const HashMap<key_type, value_type>& other) const;

    // Additional function
    void dump() const;

    // Destructor to free memory when the hash table is destroyed
    ~HashMap();
};

#include "../src/HashMap.cpp"

#endif  // INCLUDE_HASHMAP_HPP
