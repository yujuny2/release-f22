/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream wordsFile(filename);
    std::vector<std::string> words;
    string word;
    if (wordsFile.is_open()) {
        /* Reads a line from `wordsFile` into `word` until the file ends. */
        while (getline(wordsFile, word)) {
            words.push_back(word);
        }
    }

    for (unsigned i = 0; i < words.size(); i++) {
        std::vector<std::string> anagrams;
        for (unsigned j = 0; j < words.size(); j++) {
            if (i == j) continue;
            if (isAnagram(words[i], words[j])) anagrams.push_back(words[j]);
        }
        dict[words[i]] = anagrams;
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for (unsigned i = 0; i < words.size(); i++) {
        std::vector<std::string> anagrams;
        anagrams.push_back(words[i]);
        for (unsigned j = 0; j < words.size(); j++) {
            if (i == j) continue;
            if (isAnagram(words[i], words[j])) anagrams.push_back(words[j]);
        }
        if (anagrams.size() != 1) dict[words[i]] = anagrams;
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    for (std::pair<std::string, std::vector<std::string>> key_val : dict) {
        if (key_val.first == word) return key_val.second;
    }
    return vector<string>();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    std::vector<std::vector<std::string>> ret;
    for (std::pair<std::string, std::vector<std::string>> key_val : dict) {
        ret.push_back(key_val.second);
    }
    return ret;
}

bool AnagramDict::isAnagram(std::string word1, std::string word2) {
    if (word1.size() != word2.size()) return false;

    std::sort(word1.begin(), word1.end());
    std::sort(word2.begin(), word2.end());
    return word1 == word2;
}