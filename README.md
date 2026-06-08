# Movie Data Management & Recommendation System

A robust, console-based C++ application designed to parse, store, search, and analyze large datasets of movie metadata. This project features a custom-built recommendation engine and is implemented entirely from scratch without the use of the C++ Standard Template Library (STL), showcasing low-level memory management and custom data structure design.

## Features

- **Fast Data Ingestion:** Custom CSV parsing logic that handles quoted fields, commas, and edge cases to load data efficiently.
- **Advanced Search Capabilities:** Search movies by exact title, actor, genre, release year, or a specific user rating range.
- **Graph-Based Recommendation Engine:** Recommends similar movies using Breadth-First Search (BFS) based on shared actors and genres.
- **Six Degrees of Separation:** Finds the shortest connection path between any two movies using graph traversal.
- **Analytics & History:** Tracks recently viewed movies, discovers co-actor networks, and provides statistical analysis of a director's filmography.

## Data Structures Implemented

To achieve high performance and demonstrate algorithmic proficiency, all data structures were built from scratch:

### Core Data Structures

**AVL Tree**
- Used as the primary storage mechanism for `MovieNode` objects, sorted by title
- Ensures O(log n) time complexity for title-based searches and insertions

**Undirected Graph**
- Represents the complex web of movie relationships
- Adjacency List: Tracks edges between movies that share genres or actors
- Adjacency Matrix: Prevents duplicate edge creation during the graph-building phase

**Hash Tables (Separate Chaining)**
- `ActorHashTable`: Maps actor names to a linked list of movies they star in. Uses a polynomial rolling hash function
- `GenreHashTable`: Maps genres to their corresponding movies

**Singly Linked Lists**
- Extensively used for internal tracking without pre-allocating large arrays
- `intLinkedList`: Stores adjacent vertices in the graph
- `strLinkedList`: Stores variable-length lists of genres and actors per movie
- `MovieLinkedList`: Groups movies within Hash Table nodes (e.g., all movies for "Action")

**Queue (Circular Array)**
- Facilitates Breadth-First Search (BFS) for the recommendation engine and shortest path algorithms

**Stack (Array-based)**
- Maintains the user's "Recently Viewed" movie history (LIFO architecture)

## Installation & Setup

### Prerequisites

- A C++ compiler (e.g., GCC, MSVC, Clang)
- A CSV dataset named `movie_metadata.csv` placed in the root directory alongside the executable

### Compilation

Compile the source code using any standard C++ compiler. For example, using g++:

```bash
g++ -o MovieManager main.cpp
```

### Execution

Run the compiled executable from your terminal:

```bash
./MovieManager
```

## Usage & Menu Options

Upon launching the application, the dataset will load, the internal graph will be constructed, and you will be presented with the main menu:

1. **Search by title** - Retrieve detailed stats (rating, duration, cast, genres) using an exact string match
2. **Search by actor** - List all stored movies featuring a specific actor
3. **Search by genre** - View a complete list of movies tagged with a specific genre
4. **Search by year** - Find all movies released in a given year
5. **Search by rating range** - Filter movies by providing a minimum and maximum rating (e.g., 8.0 to 10.0)
6. **Recommend movies** - Input a movie title to receive a BFS-generated list of similar films based on shared cast and genres
7. **Shortest connection path** - Enter two movie titles to trace the shortest path connecting them through shared metadata
8. **Show recently viewed** - View your local search history for the current session
9. **Show co-actors** - Input an actor's name to generate a dynamic list of every other actor they have worked with in the dataset
10. **Analyze director filmography** - Input a director's name to see their career span, average film rating, and total films
11. **Exit** - Safely terminate the program and free all allocated memory

## Technical Highlights

### Custom String Manipulation
Since `<string>` was not used, the project relies on custom C-string functions including `strcmpIgnoreCase`, custom `Split` class for tokenization, and `toLower` to handle robust text comparisons and CSV splitting.

### Memory Management
Heavy use of dynamic memory allocation via pointers (`new` and `delete`). Every data structure includes a comprehensive destructor to ensure zero memory leaks upon application exit.

### Collision Handling
Hash tables resolve collisions efficiently using separate chaining via linked lists.

## Project Details

- **Language:** C++ (No STL)
- **Data Format:** CSV
- **Time Complexity:** O(log n) for searches, O(n) for graph traversal
- **Architecture:** Custom data structures, graph-based algorithms

## Credits

Special thanks to:
- **Miss Kainat Iqbal**
- **Sir Abdl Wahab**

This project was developed as part of the Data Structures course assignment, demonstrating proficiency in algorithm design, memory management, and low-level C++ programming.
