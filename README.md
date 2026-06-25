# Mini Search Engine

A C++ based document search engine that indexes text files and retrieves relevant documents using an inverted index. The project supports multi-word searching, result ranking, document analytics, persistent search history, and Trie-based autocomplete suggestions.

## Features

* Document indexing from text files
* Single-word and multi-word search
* Frequency-based ranking of search results
* Search history tracking
* Persistent search history using `history.txt`
* Search statistics and analytics
* Indexed document listing
* Top keyword analysis for documents
* Trie-based autocomplete suggestions
* File handling using C++

## Technologies Used

* C++
* STL
* File Handling
* Unordered Maps
* Vectors
* Trie Data Structure
* String Processing

## Project Structure

MiniSearchEngine/
│
├── main.cpp
├── history.txt
├── README.md
├── docs/
│   ├── cpp.txt
│   ├── dsa.txt
│   └── cloud.txt

## How to Run

Compile:

g++ main.cpp -o searchengine

Run:

./searchengine

## Menu Options

1. Search Word
2. View Search History
3. View Statistics
4. Show Indexed Documents
5. Analyze Document
6. Autocomplete
7. Exit

## Example Query

Search:

cloud computing

Result:

docs/cloud.txt (Score: 5)

## Learning Outcomes

This project demonstrates:

* Inverted Index implementation
* Trie Data Structure
* File Handling in C++
* Search Engine Fundamentals
* Text Processing and Tokenization
* Frequency-based Ranking
* Use of STL Containers
* Object-Oriented Programming Concepts

## Future Enhancements

* Real-time autocomplete suggestions in a GUI/web interface
* TF-IDF ranking for improved search relevance
* PDF and DOCX document indexing
* Database integration for large-scale document storage
* Advanced filtering and sorting options
* Web-based frontend with search dashboard
* Support for larger document collections
