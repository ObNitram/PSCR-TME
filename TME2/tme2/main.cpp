#include "HashTable.hpp"

#include <chrono>
#include <forward_list>
#include <fstream>
#include <iostream>
#include <regex>
#include <unordered_map>

using namespace std::chrono;

/// O(n) version
void addWorld(std::vector<std::pair<std::string, size_t>> &mots_lus, const std::string &word)
{
    for (auto &[mot, count] : mots_lus)
    {
        if (mot == word)
        {
            count++;
            return;
        }
    }

    mots_lus.emplace_back(word, 1);
}

/// O(n) version
void addWorld(pscr::Vector<std::pair<std::string, size_t>> &mots_lus, const std::string &word)
{
    for (auto &[mot, count] : mots_lus)
    {
        if (mot == word)
        {
            count++;
            return;
        }
    }

    mots_lus.push_back({word, 1});
}

/// O(log n) version
void addWorld(std::map<std::string, size_t> &mots_lus, const std::string &word)
{
    auto it = mots_lus.find(word);
    if (it != mots_lus.end())
    {
        it->second++;
    }
    else
    {
        mots_lus[word] = 1;
    }
}

/// O(1) version
void addWorld(std::unordered_map<std::string, size_t> &mots_lus, const std::string &word)
{
    auto it = mots_lus.find(word);
    if (it != mots_lus.end())
    {
        it->second++;
    }
    else
    {
        mots_lus[word] = 1;
    }
}

/// O(1) version
void addWorld(pscr::HashTable<std::string, size_t> &mots_lus, const std::string &word)
{
    auto it = mots_lus.get(word);
    if (it == nullptr)
    {
        mots_lus.put(word, 1);
    }
    else
    {
        mots_lus.put(word, (*it)++);
    }
}

int main()
{
    std::ifstream input = std::ifstream("/tmp/WarAndPeace.txt");

    auto start = steady_clock::now();
    std::cout << "Parsing War and Peace" << std::endl;

    size_t nombre_lu = 0;
    size_t nombre_de_questions = 0;

    std::vector<std::pair<std::string, size_t>> mots_lus;
    pscr::Vector<std::pair<std::string, size_t>> mots_lus_vector;

    std::map<std::string, size_t> mots_lus_map;

    std::unordered_map<std::string, size_t> mots_lus_unordered_map;
    pscr::HashTable<std::string, size_t> mots_lus_hashTable;

    // prochain mot lu
    std::string word;
    // une regex qui reconnait les caractères anormaux. (négation des lettres)
    std::regex re(R"([^a-zA-Z])");

    while (input >> word)
    {
        if (word.find('?') != std::string::npos) nombre_de_questions++;

        // élimine la ponctuation et les caractères spéciaux
        word = regex_replace(word, re, "");

        // passe en lowercase
        std::ranges::transform(word, word.begin(), ::tolower);

        // on ajoute le mot à la liste des mots lus
        // addWorld(mots_lus, word);
        // addWorld(mots_lus_vector, word);

        // addWorld(mots_lus_map, word);

        addWorld(mots_lus_unordered_map, word);
        addWorld(mots_lus_hashTable, word);

        // word est maintenant "tout propre"
        if (nombre_lu % 100 == 0)
            // cout << nombre_lu << ": " << word << endl;
            nombre_lu++;
    }
    input.close();

    std::cout << "Finished Parsing War and Peace" << std::endl;

    auto end = steady_clock::now();
    std::cout << "Parsing took " << duration_cast<milliseconds>(end - start).count() << "ms.\n";

    std::cout << "Found a total of " << nombre_lu << " words." << std::endl;
    std::cout << "Found a total of " << nombre_de_questions << " questions." << std::endl;
    std::cout << "Found a total of " << mots_lus.size() << " unique words." << std::endl;
    std::cout << "Found a total of " << mots_lus_vector.size() << " unique words (vector)." << std::endl;
    std::cout << "Found a total of " << mots_lus_map.size() << " unique words (map)." << std::endl;
    std::cout << "Found a total of " << mots_lus_unordered_map.size() << " unique words (unordered_map)." << std::endl;
    std::cout << "Found a total of " << mots_lus_hashTable.size() << " unique words (HashTable)." << std::endl;

    std::map<size_t, std::vector<std::string>> mots_index_unordered_map;

    for (const auto &[fst, snd] : mots_lus_unordered_map)
    {
        mots_index_unordered_map[snd].push_back(fst);
    }

    for (const auto &[fst, snd] : mots_index_unordered_map)
    {
        std::cout << "Found " << snd.size() << " words that appear " << fst << " times." << std::endl;
    }



    return 0;
}