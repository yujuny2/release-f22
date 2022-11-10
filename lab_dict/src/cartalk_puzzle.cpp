/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iostream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */

    // get the list of words and put them in a vector
    ifstream wordsFile(word_list_fname);
    std::vector<std::string> words;
    string word;
    if (wordsFile.is_open()) {
        /* Reads a line from `wordsFile` into `word` until the file ends. */
        while (getline(wordsFile, word)) {
            words.push_back(word);
            // cout << word << endl;
        }
    }

    for (unsigned i = 0; i < words.size(); i++) {
        std::string word = words[i];

        if (word.size() < 3) continue;

        std::string first_removed = word.substr(1);
        std::string second_removed = word.substr(0, 1) + word.substr(2);

        if (d.homophones(word, first_removed) && d.homophones(word, second_removed)) {
            ret.push_back(std::make_tuple(word, first_removed, second_removed));
            std::cout << word << " " << first_removed << " " << second_removed << " " << std::endl;
        }
    }
    return ret;
}
