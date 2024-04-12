// Copyright 2024 by Contributors
#include "../include/HashMap.hpp"

template <typename key_type, typename value_type>
Node<key_type, value_type>::Node(const key_type& key, value_type value)
    : key_(key), value_(value), state_(true) {}

template <typename key_type, typename value_type>
Node<key_type, value_type>::Node() 
    : key_(key_type()), value_(value_type()), state_(true) {}

template <typename key_type, typename value_type>
void Node<key_type, value_type>::updateValue(const key_type& newKey, value_type newValue) {
    key_ = newKey;
    value_ = newValue;
    state_ = true;
}

template <typename key_type, typename value_type>
bool Node<key_type, value_type>::empty() const {
    return !state_;
}

template <typename key_type, typename value_type>
std::ostream& operator<<(std::ostream& os, const Node<key_type, value_type>& node) {
    os << "Key: " << node.key << ", Value: " << node.value;
    return os;
}

template <typename key_type, typename value_type>
size_t HashMap<key_type, value_type>::hashGenerate(const std::string& string, size_t tableSize, size_t key) const {
    size_t hashResult = 0;
    for (char token : string) {
        hashResult = (key * hashResult + token) % tableSize;
    }
    hashResult = (hashResult * 2 + 1) % tableSize;
    return hashResult % tableSize;
}

template <typename key_type, typename value_type>
size_t HashMap<key_type, value_type>::hashGenerate(const int64_t& integer, size_t tableSize, size_t key) const {
    size_t hashResult = 0;
    for (char token : std::to_string(integer)) {
        hashResult = (key * hashResult + token) % tableSize;
    }
    hashResult = (hashResult * 2 + 1) % tableSize;
    return hashResult % tableSize;
}

template <typename key_type, typename value_type>
size_t HashMap<key_type, value_type>::hash1(const key_type& key) const {
    return hashGenerate(key, arr_.size(), arr_.size() - 1);
}

template <typename key_type, typename value_type>
size_t HashMap<key_type, value_type>::hash2(const key_type& key) const {
    return hashGenerate(key, arr_.size(), arr_.size() + 1);
}

template <typename key_type, typename value_type>
size_t HashMap<key_type, value_type>::findEmptyIndex(const key_type& key) const {
    size_t h1 = hash1(key);
    size_t h2 = hash2(key);
    size_t i = 0;

    while (arr_[h1] != nullptr && i < arr_.size()) {
        if (!arr_[h1]->state_) {
            return h1;
        }
        h1 = (h1 + h2) % arr_.size();
        ++i;
    }

    return h1;
}

template <typename key_type, typename value_type>
size_t HashMap<key_type, value_type>::findIndex(const key_type& key) const {
    size_t h1 = hash1(key);
    size_t h2 = hash2(key);
    size_t i = 0;

    while (arr_[h1] != nullptr && i < arr_.size()) {
        if (arr_[h1]->key_ == key && arr_[h1]->state_) {
            return h1;
        }
        h1 = (h1 + h2) % arr_.size();
        ++i;
    }
    return h1;
}

template <typename key_type, typename value_type>
void HashMap<key_type, value_type>::_add(const key_type& key, value_type value) {
    size_t h1 = hash1(key);
    size_t h2 = hash2(key);

    size_t i = 0;

    bool foundFirstDeleted = false;
    size_t firstDeleted = 0;

    while (arr_[h1] != nullptr && i < arr_.size()) {
        if (arr_[h1]->key_ == key && arr_[h1]->state_) {
            return;
        }

        if (!arr_[h1]->state_ && foundFirstDeleted == false) {
            firstDeleted = h1;
            foundFirstDeleted = true;
        }

        h1 = (h1 + h2) % arr_.size();
        ++i;
    }

    if (foundFirstDeleted == false) {
        arr_[h1] = new Node<key_type, value_type>(key, value);
        sizeAllNonNullptr_++;
    } else {
        arr_[firstDeleted] = new Node<key_type, value_type>(key, value);
    }

    size_++;
}

template <typename key_type, typename value_type>
void HashMap<key_type, value_type>::resize() {
    sizeAllNonNullptr_ = 0;
    size_ = 0;
    std::vector<Node<key_type, value_type>*> oldArr = arr_;

    arr_.clear();
    arr_.resize(oldArr.size() * 2, nullptr);

    for (size_t i = 0; i < oldArr.size(); ++i) {
        if (oldArr[i] != nullptr) {
            if (oldArr[i]->state_) {
                _add(oldArr[i]->key_, oldArr[i]->value_);
                delete oldArr[i];
            }
        }
    }
}

template <typename key_type, typename value_type>
void HashMap<key_type, value_type>::rehash() {
    sizeAllNonNullptr_ = 0;
    size_ = 0;

    std::vector<Node<key_type, value_type>*> oldArr = arr_;

    arr_.clear();
    arr_.resize(oldArr.size(), nullptr);

    for (size_t i = 0; i < oldArr.size(); ++i) {
        if (oldArr[i] != nullptr) {
            if (oldArr[i]->state_) {
                _add(oldArr[i]->key_, oldArr[i]->value_);
                delete oldArr[i];
            }
        }
    }
}

template <typename key_type, typename value_type>
HashMap<key_type, value_type>::HashMap()
    : rehashSize_(0.75), size_(0), sizeAllNonNullptr_(0), arr_(8, nullptr) {
    setDefaultKey();
    setDefaultValue();
}

template <typename key_type, typename value_type>
void HashMap<key_type, value_type>::setDefaultValue() {
    if constexpr (std::is_same<value_type, std::string>::value) {
        defualtValue_ = '\0';
    } else if constexpr (std::is_same<value_type, int>::value) {
        defualtValue_ = std::numeric_limits<int>::min();
    } else if constexpr (std::is_same<value_type, int64_t>::value) {
        defualtValue_ = std::numeric_limits<int64_t>::min();
    }
}

template <typename key_type, typename value_type>
void HashMap<key_type, value_type>::setDefaultKey() {
    if constexpr (std::is_same<key_type, std::string>::value) {
        defualtKey_ = "nullptr";
    } else if constexpr (std::is_same<key_type, int>::value) {
        defualtKey_ = std::numeric_limits<int>::min();
    } else if constexpr (std::is_same<key_type, int64_t>::value) {
        defualtKey_ = std::numeric_limits<int64_t>::min();
    }
}

template <typename key_type, typename value_type>
value_type& HashMap<key_type, value_type>::operator[](const key_type& key) {
    size_t index = findIndex(key);
    if (arr_[index] == nullptr) {
        arr_[index] = new Node<key_type, value_type>(key, defualtValue_);
        sizeAllNonNullptr_++;
        size_++;
    }
    return arr_[index]->value_;
}

template <typename key_type, typename value_type>
bool HashMap<key_type, value_type>::operator==(const HashMap& hashMap) const {
    return isEqual(hashMap);
}

template <typename key_type, typename value_type>
bool HashMap<key_type, value_type>::operator!=(const HashMap& hashMap) const {
    return !isEqual(hashMap);
}

template <typename key_type, typename value_type>
std::ostream& operator<<(std::ostream& os, const HashMap<key_type, value_type>& hashMap) {
    for (size_t i = 0; i < hashMap.arr_.size(); ++i) {
        os << "Index " << i << ": ";
        if (hashMap.arr_[i] == nullptr || hashMap.arr_[i]->empty()) {
            os << "nullptr" << std::endl;
        } else {
            os << *hashMap.arr_[i] << std::endl;
        }
    }
    return os;
}

template <typename key_type, typename value_type>
void HashMap<key_type, value_type>::put(const key_type& key, value_type value) {
    if (size_ + 1 > rehashSize_ * arr_.size()) {
        resize();
    } else if (sizeAllNonNullptr_ > 2 * size_) {
        rehash();
    }
    _add(key, value);
}

template <typename key_type, typename value_type>
void HashMap<key_type, value_type>::del(const key_type& key) {
    size_t h1 = hash1(key);
    size_t h2 = hash2(key);
    size_t i = 0;

    while (arr_[h1] != nullptr && i < arr_.size()) {
        if (arr_[h1]->key_ == key && arr_[h1]->state_) {
            delete arr_[h1];
            arr_[h1]->state_ = false;
            size_--;
        }

        h1 = (h1 + h2) % arr_.size();
        ++i;
    }
}

template <typename key_type, typename value_type>
value_type HashMap<key_type, value_type>::get(const key_type& key) const {
    size_t index = findIndex(key);
    return (arr_[index] == nullptr) ? defualtValue_ : arr_[index]->value_;
}

template <typename key_type, typename value_type>
bool HashMap<key_type, value_type>::isEqual(const HashMap<key_type, value_type>& other) const {
    for (size_t i = 0; i < arr_.size(); ++i) {
        if (arr_[i] == nullptr) {
            continue;
        }
        if (other.arr_[i] == nullptr)
            return false;
        if (arr_[i]->key_ != other.arr_[i]->key_ || arr_[i]->value_ != other.arr_[i]->value_) {
            return false;
        }
    }
    return true;
}

template <typename key_type, typename value_type>
HashMap<key_type, value_type>::~HashMap() {
    for (Node<key_type, value_type>* node : arr_) {
        if (node != nullptr) {
            if (node->state_) {
                delete node;
                size_--;
                sizeAllNonNullptr_--;
            }
        }
    }
}

template <typename key_type, typename value_type>
void HashMap<key_type, value_type>::dump() const {
    std::cout << "------------" << std::endl;
    for (size_t i = 0; i < arr_.size(); ++i) {
        std::cout << "Index " << i << ": ";
        if (arr_[i] == nullptr || arr_[i]->empty()) {
            std::cout << "nullptr" << std::endl;
        } else {
            std::cout << "Active Node" << std::endl;
            std::cout << "    Key: " << arr_[i]->key_ << std::endl;
            std::cout << "    Value: " << arr_[i]->value_ << std::endl;
        }
    }
}
