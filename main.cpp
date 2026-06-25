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
    unordered_map<string,int> searchCount;
    vector<string> documentList;
    unordered_map<string,unordered_map<string,int>> documentWords;

public:
    void indexFile(const string& filename) {
        documentList.push_back(filename);
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
                documentWords[filename][cleanedWord]++;
            }
        }

        file.close();
    }

    void analyzeDocument(string filename) {

        if(documentWords.find(filename)
        == documentWords.end()) {

            cout << "Document not found\n";
            return;
        }

        vector<pair<string,int>> words;

        for(auto &x : documentWords[filename])
            words.push_back(x);

        sort(words.begin(),
            words.end(),
            [](auto &a, auto &b){

                return a.second > b.second;
            });

        cout << "\nTop Keywords in "
            << filename
            << "\n\n";

        int limit =
            min((int)words.size(), 5);

        for(int i=0;i<limit;i++) {

            cout << words[i].first
                << " -> "
                << words[i].second
                << endl;
        }
    }

    void showDocuments() {

        cout << "\n===== INDEXED DOCUMENTS =====\n";

        for(int i=0;i<documentList.size();i++) {

            cout << i+1 << ". "
                << documentList[i]
                << endl;
        }

        cout << "\nTotal Documents: "
            << documentList.size()
            << endl;
    }

    void showStats() {
        cout << "\n===== SEARCH STATISTICS =====\n";

        cout << "Total Searches: "
            << searchHistory.size()
            << "\n\n";

        vector<pair<string,int>> stats;

        for(auto &x : searchCount)
            stats.push_back(x);

        sort(stats.begin(), stats.end(),
            [](auto &a, auto &b){
                return a.second > b.second;
            });

        cout << "Most Searched Queries:\n";

        for(auto &x : stats)
            cout << x.first << " -> " << x.second << "\n";
    }

    void search(const string& query) {

        searchHistory.push_back(query);
        searchCount[query]++;

        ofstream historyFile("history.txt", ios::app);

        if(historyFile.is_open()) {
            historyFile << query << endl;
            historyFile.close();
        }

        unordered_map<string, int> documentScores;

        stringstream ss(query);
        string word;

        while (ss >> word) {

            for (char &c : word)
                c = tolower(c);

            if (index.find(word) != index.end()) {

                for (auto &doc : index[word]) {
                    documentScores[doc.first] += doc.second;
                }
            }
        }

        if (documentScores.empty()) {
            cout << "\nNo documents found.\n";
            return;
        }

        vector<pair<string,int>> results;

        for (auto &doc : documentScores) {
            results.push_back(doc);
        }

        sort(results.begin(), results.end(),
            [](const auto &a, const auto &b){
                return a.second > b.second;
            });

        cout << "\nSearch Results for \"" << query << "\"\n";
        cout << "----------------------------------\n";

        for (auto &result : results) {
            cout << result.first << " (Score: "<< result.second << ")\n";
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

        cout << "1. Search Word\n";
        cout << "2. View Search History\n";
        cout << "3. View Statistics\n";
        cout << "4. Show Indexed Documents\n";
        cout << "5. Analyze Document\n";
        cout << "6. Exit\n";

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
            engine.showStats();
            break;
        
        case 4:
        engine.showDocuments();
        break;

        case 5: {
            string filename;

            cout << "Enter document name: ";
            getline(cin, filename);

            engine.analyzeDocument(filename);
            break;
        }

        case 6:
            cout << "Exiting...\n";
            break;

            default:
                cout << "Invalid Choice!\n";
            }

        } while(choice != 6);

    return 0;
}