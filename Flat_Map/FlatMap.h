#pragma once
#include <string>
#include <iostream>

template<typename Key, typename Value>
class FlatMap {


public:

    typedef struct pair {
        Key key;
        Value value;
    };

    pair** map;
    size_t sizez;

    FlatMap() {
        map = NULL;
        sizez = 0;
    }

    FlatMap(const FlatMap& other_map) {
        sizez = other_map.sizez();
        if (other_map.map == NULL) {
            map = NULL;
        }
        else {
            size_t len = sizez;
            map = new (pair* [len]);
            for (size_t i = 0; i < len; ++i) {
                map[i] = new (pair);
                map[i]->key = other_map.map[i]->key;
                map[i]->value = other_map.map[i]->value;
            }
        }
    }

    ~FlatMap() {
        if (map != NULL) {
            std::size_t len = sizez;
            for (std::size_t i = 0; i < len; ++i)
                delete map[i];
            delete[] map;
        }
    }

    FlatMap& operator=(const FlatMap& other_map) {
        if (this == &other_map)
            return *this;
        sizez = other_map.sizez;
        if (sizez) {
            map = new (pair* [sizez]);
            for (int i = 0; i < sizez; i++) {
                map[i] = new (pair);
                map[i]->key = other_map[i]->key;
                map[i]->value = other_map[i]->value;
            }
        }
        else {
            map = NULL;
        }
        return *this;
    }

    std::size_t size() const {
        return sizez;
    }

    Value& operator[](const Key& key) {
        if (map == NULL) {
            sizez = 1;
            map = new (pair* [1]);
            map[0] = new (pair);
            map[0]->key = key;
            return map[0]->value;
        }
        else {
            if (this->contains(key)) {
                size_t index = binarys_search(map, key);
                return map[index]->value;
            }
            size_t index = binarys_search(map, key);
            pair** value = new (pair* [sizez + 1]);
            for (size_t i = 0; i < index; i++) {
                value[i] = new (pair);
                value[i]->key = map[i]->key;
                value[i]->value = map[i]->value;
                delete map[i];
            }
            value[index] = new (pair);
            value[index]->key = key;
            for (size_t i = index; i < sizez; i++) {
                value[i + 1] = new (pair);
                value[i + 1]->key = map[i]->key;
                value[i + 1]->value = map[i]->value;
                delete map[i];
            }
            delete[] map;
            map = value;
            sizez++;
            return map[index]->value;
        }

    }

    bool contains(const Key& key) {
        size_t index = binarys_search(map, key);
        if ((index < sizez) && (map[index]->key == key))
            return 1;
        else
            return 0;
    }
  
     std::size_t erase(const Key& key) {
        if (this->contains(key)) {
            size_t index = binarys_search(map, key);
            pair** other = new (pair* [sizez]);
            for (size_t i = 0; i < index; i++) {
                other[i] = new (pair);
                other[i]->key = map[i]->key;
                other[i]->value = map[i]->value;
                delete map[i];
            }
            delete map[index];
            for (size_t i = index; i < sizez - 1; i++) {
                other[i] = new (pair);
                other[i]->key = map[i + 1]->key;
                other[i]->value = map[i + 1]->value;
                delete map[i + 1];
            }
            delete[] map;
            map = other;
            sizez--;
            return 1;
        }
        else
            return 0;

    }


    void clear() {
        if (map != NULL) {
            std::size_t len = sizez;
            for (std::size_t i = 0; i < len; ++i)
                delete map[i];
            delete[] map;
        }
        map = NULL;
        sizez = 0;
    }

    class Iterator {
    public:
        explicit Iterator(pair** map, int size) : iterator_map(map), size(size) {
            index = 0;
            if (iterator_map == nullptr) {
                index = -1;
            }
        }

        ~Iterator() = default;

        bool operator==(const Iterator& b) {
            return (index == b.index);
        }

        bool operator!=(const Iterator& b) {
            return (index != b.index);
        }

        Iterator operator++() {
            if (iterator_map == nullptr)
                return *this;
            index++;
            if (index == size) {
                iterator_map == nullptr;
                index = -1;
                return *this;
            }
            return *this;
        }

        pair& operator*() {
            return *iterator_map[index];
        }


    private:
        pair** iterator_map;
        int index;
        int size;
    };

    Iterator begin() {
        return Iterator(map, sizez);
    }

    Iterator end() {
        return Iterator(nullptr, sizez);
    }

private:
    
    size_t binarys_search(pair** flat_map, const Key& key) {

        int len = sizez - 1;
        int start = 0;
        int finish = len;
        for (int index_medium = len / 2; ;) {
            if (start > finish) {
                return (size_t)start;
            }
            index_medium = start + (finish - start) / 2;
            if (flat_map[index_medium]->key == key) {
                return index_medium;
            }
            else
                if (flat_map[index_medium]->key < key) {
                    start = index_medium + 1;
                }
                else {
                    finish = index_medium - 1;
                }
        }
        return 0;
    }


};