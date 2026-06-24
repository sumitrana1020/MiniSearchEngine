#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class SearchEngine {
private:
    unordered_map<string, unordered_map<string, int>> index;
    vector<string> searchHistory;

public:
    void indexFile(const string& filename) {
        ifstream file(filename);

        if (!file.is_open()) {
            cout << "Cannot open file: " << filename << endl;
            return;
        }

        string word;

        while (file >> word) {

            for (char &c : word) {
                c = tolower(c);
                if (ispunct(c))
                    c = ' ';
            }

            stringstream ss(word);
            string cleanedWord;

            while (ss >> cleanedWord) {
                index[cleanedWord][filename]++;
            }
        }

        file.close();
    }

    void search(const string& keyword) {

        string key = keyword;

        for (char &c : key)
            c = tolower(c);

        searchHistory.push_back(key);

        if (index.find(key) == index.end()) {
            cout << "\nNo documents found.\n";
            return;
        }

        vector<pair<string, int>> results;

        for (auto &doc : index[key]) {
            results.push_back({doc.first, doc.second});
        }

        sort(results.begin(), results.end(),
             [](auto &a, auto &b) {
                 return a.second > b.second;
             });

        cout << "\nSearch Results for \"" << key << "\"\n";
        cout << "----------------------------------\n";

        for (auto &result : results) {
            cout << result.first
                 << "  (Occurrences: "
                 << result.second << ")\n";
        }
    }

    void showHistory() {
        cout << "\nSearch History\n";
        cout << "--------------\n";

        for (string word : searchHistory) {
            cout << word << endl;
        }
    }
};

int main() {

    SearchEngine engine;

    vector<string> files = {
        "docs/cpp.txt",
        "docs/dsa.txt",
        "docs/cloud.txt"
    };

    for (string file : files) {
        engine.indexFile(file);
    }

    int choice;

    do {

        cout << "\n===== MINI SEARCH ENGINE =====\n";
        cout << "1. Search Word\n";
        cout << "2. View Search History\n";
        cout << "3. Exit\n";
        cout << "Enter Choice: ";

        cin >> choice;

        cin.ignore();

        switch(choice) {

        case 1: {
            string keyword;

            cout << "Enter keyword: ";
            getline(cin, keyword);

            engine.search(keyword);
            break;
        }

        case 2:
            engine.showHistory();
            break;

        case 3:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

    } while(choice != 3);

    return 0;
}