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
    struct TrieNode {
    TrieNode* child[26];
        bool endWord;
        TrieNode() {
            endWord = false;

            for(int i = 0; i < 26; i++)
                child[i] = nullptr;
        }
    };
    TrieNode* root = new TrieNode();

public:
    void insertTrie(string word) {
        TrieNode* curr = root;
        for(char c : word) {

            if(!isalpha(c))
                continue;

            c = tolower(c);

            int idx = c - 'a';

            if(curr->child[idx] == nullptr)
                curr->child[idx] = new TrieNode();

            curr = curr->child[idx];
        }

        curr->endWord = true;
    }

    void collectWords(TrieNode* node,string current,vector<string>& result) {
        if(node == nullptr)
            return;

        if(node->endWord)
            result.push_back(current);

        for(int i = 0; i < 26; i++) {
            if(node->child[i]) {

                collectWords(
                    node->child[i],
                    current + char('a' + i),
                    result);
            }
        }
    }

    void suggest(string prefix) {
        for(char &c : prefix)
            c = tolower(c);

        TrieNode* curr = root;

        for(char c : prefix) {

            if(!isalpha(c))
                continue;

            int idx = c - 'a';

            if(curr->child[idx] == nullptr) {

                cout << "\nNo suggestions found.\n";
                return;
            }
            curr = curr->child[idx];
        }
        vector<string> result;
        collectWords(curr, prefix, result);

        cout << "\nSuggestions:\n";

        if(result.empty()) {
            cout << "No suggestions found.\n";
            return;
        }
        for(string word : result)
            cout << word << endl;
    }

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
                insertTrie(cleanedWord);
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
        "docs/cloud.txt",
        "docs/os.txt",
        "docs/dbms.txt",
        "docs/networking.txt"
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
        cout << "6. Autocomplete\n";
        cout << "7. Exit\n";

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

        case 6: {
            string prefix;

            cout << "Enter prefix: ";
            getline(cin, prefix);

            engine.suggest(prefix);

            break;
        }

        case 7:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

        } while(choice != 7);

    return 0;
}