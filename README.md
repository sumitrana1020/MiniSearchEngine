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