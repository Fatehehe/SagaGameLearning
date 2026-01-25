#pragma once
#include <stdio.h>
#include <memory>
#include <map>
#include <unordered_map>
#include <unordered_set>

#define LOG(M, ...) printf(M "\n", ##__VA_ARGS__)

template<typename T>
using unique = std::unique_ptr<T>;

template<typename T>
using shared = std::shared_ptr<T>;

template<typename T> 
using weak = std::weak_ptr<T>;

template<typename T>
using List = std::vector<T>;

template<typename Key, typename Value, typename Pr = std::less<Key>>
using Map = std::map<Key, Value, Pr>;

template<typename Key, typename Value, typename Hasher = std::hash<Key>>
using Dictionary = std::unordered_map<Key, Value, Hasher>;

