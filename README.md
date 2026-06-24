# Movie Data Management & Recommendation System

A robust, console-based C++ application for parsing, storing, searching, and analyzing large datasets of movie metadata. Features a custom-built recommendation engine implemented entirely from scratch — no STL — demonstrating low-level memory management and custom data structure design.

---

## Dataset

Download the dataset from Kaggle:  
**[Movie Metadata CSV](https://www.kaggle.com/datasets/karrrimba/movie-metadatacsv)**

Place the downloaded file named `movie_metadata.csv` in the **same directory** as the compiled executable before running the program.

---

## Features

- **Fast Data Ingestion** — Custom CSV parser handles quoted fields, embedded commas, and edge cases to load data efficiently
- **Advanced Search** — Search by exact title, actor, genre, release year, or user rating range
- **Graph-Based Recommendation Engine** — Recommends similar movies using BFS over shared actors and genres
- **Six Degrees of Separation** — Finds the shortest connection path between any two movies via graph traversal
- **Analytics & History** — Tracks recently viewed movies, discovers co-actor networks, and provides statistical analysis of a director's filmography

---

## Data Structures

All data structures were implemented from scratch to demonstrate algorithmic proficiency.

### AVL Tree
- Primary storage for `MovieNode` objects, sorted by title
- Guarantees O(log n) insertion and title-based search

### Undirected Graph
- Models the web of movie relationships
- **Adjacency List** — tracks edges between movies sharing genres or actors
- **Adjacency Matrix** — prevents duplicate edges during graph construction

### Hash Tables (Separate Chaining)
- `ActorHashTable` — maps actor names to linked lists of their movies using a polynomial rolling hash
- `GenreHashTable` — maps genre labels to their corresponding movie lists

### Singly Linked Lists
- `intLinkedList` — stores adjacent vertex indices in the graph
- `strLinkedList` — stores variable-length genre and actor lists per movie
- `MovieLinkedList` — groups movies within hash table buckets (e.g., all "Action" movies)

### Queue (Circular Array)
- Drives BFS for the recommendation engine and shortest-path algorithm

### Stack (Array-Based)
- LIFO structure maintaining the user's "Recently Viewed" history for the current session

---

## Installation & Setup

### Prerequisites

- A C++ compiler — GCC, MSVC, or Clang
- `movie_metadata.csv` placed in the root directory alongside the executable

### Compilation

```bash
g++ -o MovieManager main.cpp
```

### Execution

```bash
./MovieManager
```

---

## Menu Options

On launch, the dataset loads, the graph is constructed, and the main menu appears:

| # | Option | Description |
|---|--------|-------------|
| 1 | Search by title | Retrieve rating, duration, cast, and genres via exact string match |
| 2 | Search by actor | List all movies featuring a given actor |
| 3 | Search by genre | View all movies tagged with a specific genre |
| 4 | Search by year | Find all movies from a given release year |
| 5 | Search by rating range | Filter movies by a min–max rating (e.g., 8.0 to 10.0) |
| 6 | Recommend movies | BFS-generated recommendations based on shared cast and genres |
| 7 | Shortest connection path | Trace the shortest link between two movies through shared metadata |
| 8 | Show recently viewed | Display your search history for the current session |
| 9 | Show co-actors | List every actor a given actor has worked with in the dataset |
| 10 | Analyze director filmography | Career span, average rating, and total films for a director |
| 11 | Exit | Terminate the program and free all allocated memory |

---

## Technical Highlights

### Custom String Handling
Without `<string>`, all text operations use custom C-string utilities: `strcmpIgnoreCase` for case-insensitive comparison, a custom `Split` class for CSV tokenization, and `toLower` for normalization.

### Memory Management
All dynamic allocation uses raw `new` and `delete`. Every data structure includes a destructor ensuring zero memory leaks on exit.

### Collision Resolution
Hash table collisions are resolved through separate chaining via linked lists.

---

## Complexity

| Operation | Complexity |
|-----------|------------|
| Title search / insertion | O(log n) — AVL Tree |
| Actor / genre lookup | O(1) avg — Hash Table |
| BFS recommendation / shortest path | O(V + E) — Graph traversal |

---

## Project Info

- **Language:** C++ (No STL)
- **Input Format:** CSV
- **Course:** Data Structures

## Authors

- Imtishal Haq
- Harram Javed

## Acknowledgements

- Miss Kainat Iqbal  
- Sir Abdul Wahab
