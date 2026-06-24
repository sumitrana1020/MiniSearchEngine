# Mini Search Engine

A C++ based document search engine that indexes text files and retrieves relevant documents based on user queries.

## Features

- Document indexing
- Keyword search
- Frequency-based ranking
- Search history tracking
- File handling using C++

## Technologies Used

- C++
- STL
- File Handling
- Unordered Maps
- Vectors

## Project Structure

MiniSearchEngine/
│
├── main.cpp
├── Docs/
│   ├── cpp.txt
│   ├── dsa.txt
│   └── cloud.txt

## How to Run

Compile:

g++ main.cpp -o searchengine

Run:

./searchengine

## Example Query

Search: cloud

Result:

cloud.txt (Occurrences: 3)
## Future Enhancements

- Support multi-word search queries.
- Implement Trie-based autocomplete suggestions.
- Add TF-IDF ranking for more relevant search results.
- Develop a graphical/web-based user interface.
- Enable indexing of PDF and DOCX documents.
- Store search history in files for persistent tracking.
- Improve search performance for large document collections.