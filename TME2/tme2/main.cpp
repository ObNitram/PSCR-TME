#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <unordered_map>

#include "src/HashMap.hpp"

using namespace std;
using namespace std::chrono;


/// O(n) version
void addWorld(vector<std::pair<string, size_t>> &mots_lus, const string &word)
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

/// O(1) version
void addWorld(map<string, size_t> &mots_lus, const string &word)
{
    auto it = mots_lus.find(word);
    if (it != mots_lus.end()) { it->second++; }
    else { mots_lus[word] = 1; }
}

/// O(log n) version
void addWorld(unordered_map<string, size_t> &mots_lus, const string &word)
{
    auto it = mots_lus.find(word);
    if (it != mots_lus.end()) { it->second++; }
    else { mots_lus[word] = 1; }
}

/// O(1) version
void addWorld(HashMap<string, size_t> &mots_lus, const string &word)
{
    auto it = mots_lus.get(word);
    if (it != 0) { mots_lus.put(word, it + 1); }
    else { mots_lus.put(word, 1); }
}

int main()
{
    ifstream input = ifstream("/tmp/WarAndPeace.txt");

    auto start = steady_clock::now();
    cout << "Parsing War and Peace" << endl;

    size_t nombre_lu = 0;
    size_t nombre_de_questions = 0;
    vector<std::pair<string, size_t>> mots_lus;
    map<string, size_t> mots_lus_map;
    unordered_map<string, size_t> mots_lus_unordered_map;
    HashMap<string, size_t> mots_lus_hashmap;

    // prochain mot lu
    string word;
    // une regex qui reconnait les caractères anormaux. (négation des lettres)
    regex re(R"([^a-zA-Z])");

    while (input >> word)
    {
        if (word.find('?') != string::npos) nombre_de_questions++;

        // élimine la ponctuation et les caractères spéciaux
        word = regex_replace(word, re, "");
        // passe en lowercase
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        // on ajoute le mot à la liste des mots lus
        //addWorld(mots_lus, word);
        addWorld(mots_lus_map, word);
        addWorld(mots_lus_unordered_map, word);
        addWorld(mots_lus_hashmap, word);

        // word est maintenant "tout propre"
        if (nombre_lu % 100 == 0)
            //cout << nombre_lu << ": " << word << endl;

            nombre_lu++;
    }
    input.close();

    cout << "Finished Parsing War and Peace" << endl;

    auto end = steady_clock::now();
    cout << "Parsing took "
        << duration_cast<milliseconds>(end - start).count()
        << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;
    cout << "Found a total of " << nombre_de_questions << " questions." << endl;
    cout << "Found a total of " << mots_lus.size() << " unique words." << endl;
    cout << "Found a total of " << mots_lus_map.size() << " unique words (map)." << endl;
    cout << "Found a total of " << mots_lus_unordered_map.size() << " unique words (unordered_map)." << endl;
    cout << "Found a total of " << mots_lus_hashmap.getSize() << " unique words (hashmap)." << endl;

    return 0;
}