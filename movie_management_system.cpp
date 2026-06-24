#include <iostream>
#include <fstream>

using namespace std;

int max1(int a, int b) {
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}

//handling signs and spaces
int sTi(char* str) {
    int res = 0;
    int s = 1;
    int i = 0;
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        i++;
    if (str[i] == '-') {
        s = -1;
        i++;
    }
    else if (str[i] == '+') {
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return s * res;
}

// converts n hnadles integer and fraction
float sTf(char* str) {
    float res = 0;
    float frac = 0;
    int s = 1;
    int i = 0;
    bool decFound = false;
    float divisor = 10;
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        i++;
    if (str[i] == '-') {
        s = -1;
        i++;
    }
    else if (str[i] == '+') {
        i++;
    }
    while ((str[i] >= '0' && str[i] <= '9') || str[i] == '.') {
        if (str[i] == '.') {
            decFound = true;
            i++;
            continue;
        }
        if (!decFound) {
            res = res * 10.0 + (str[i] - '0');
        }
        else {
            frac += (str[i] - '0') / divisor;
            divisor *= 10;
        }
        i++;
    }

    return s * (res + frac);
}

//boolean array for visited arrays in graph
void setboolvalue(bool* ptr, bool val, int count) {
    for (int i = 0; i < count; i++) {
        ptr[i] = val;
    }
}

bool isSpace(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f');
}

void toLower(char* str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
    }
}
// comparison by converting each character to lowercase then gives diff between mismatched while equal ignored
int strcmpIgnoreCase(char* s1, char* s2) {
    while (*s1 && *s2) {
        char c1 = *s1;
        char c2 = *s2;
        if (c1 >= 'A' && c1 <= 'Z')
            c1 = c1 + 32;
        if (c2 >= 'A' && c2 <= 'Z')
            c2 = c2 + 32;

        if (c1 != c2)
            return c1 - c2;
        s1++;
        s2++;
    }
    char c1 = *s1;
    char c2 = *s2;
    if (c1 >= 'A' && c1 <= 'Z')
        c1 = c1 + 32;
    if (c2 >= 'A' && c2 <= 'Z')
        c2 = c2 + 32;
    return c1 - c2;
}

// removeing space and ta for clean output
void cleanTitle(char* title) {
    int len = strlen(title);
    while (len > 0 && isSpace(title[len - 1])) {
        title[--len] = '\0';
    }
    while (len >= 2) {
        if (title[len - 2] == -62 && title[len - 1] == -96) {
            len -= 2;
            title[len] = '\0';
        }
        else {
            break;
        }
    }
}

//splting a string \o character for parsing for separated vals 
class Split {
private:
    char* str;
    char sep;
    int cur;

public:
    Split(char* s, char sepp) : str(s), sep(sepp), cur(0) {}

    char* nextToken() {
        if (str == NULL || str[cur] == '\0')
            return NULL;

        while (str[cur] == sep)
            cur++;
        if (str[cur] == '\0')
            return NULL;
        int start = cur;
        while (str[cur] != '\0' && str[cur] != sep) {
            cur++;
        }

        if (str[cur] == sep) {
            str[cur] = '\0';
            cur++;
        }
        return &str[start];
    }
};

//for storing int in linked list used in adjacency lists
struct INode {
    int data;
    INode* next;
    INode(int d) : data(d), next(NULL) {}
};

//for storing strings in linked list used in genres and actors
struct StrNode {
    char* data;
    StrNode* next;

    StrNode(char* d) {
        if (d) {
            int len = strlen(d);
            data = new char[len + 1];
            strcpy_s(data, len + 1, d);
        }
        else {
            data = new char[1];
            data[0] = '\0';
        }
        next = NULL;
    }

    ~StrNode() {
        delete[] data;
    }
};

// int linked list for graph adjacency list to track movie connections
class intLinkedList {
public:
    INode* head;
    intLinkedList() : head(NULL) {}

    // insert at head
    void insert(int d) {
        INode* NN = new INode(d);
        NN->next = head;
        head = NN;
    }

    bool contains(int d) {
        INode* temp = head;
        while (temp) {
            if (temp->data == d)
                return true;
            temp = temp->next;
        }
        return false;
    }

    ~intLinkedList() {
        while (head) {
            INode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

//sting ll used for genres and actors associated with movies
class strLinkedList {
public:
    StrNode* head;
    strLinkedList() : head(NULL) {}

    void insert(char* d) {
        StrNode* NN = new StrNode(d);
        NN->next = head;
        head = NN;
    }
    bool contains(char* d) {
        StrNode* temp = head;
        while (temp) {
            if (strcmp(temp->data, d) == 0)
                return true;
            temp = temp->next;
        }
        return false;
    }

    void print() {
        StrNode* temp = head;
        while (temp) {
            cout << temp->data;
            if (temp->next) cout << ", ";
            temp = temp->next;
        }
    }

    ~strLinkedList() {
        while (head) {
            StrNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

//allkey attributes n ptrs for avl 
class MovieNode {
public:
    char title[256];
    char director[100];
    int year;
    float rating;
    int duration;
    strLinkedList* genres;
    strLinkedList* actors;
    MovieNode* left;
    MovieNode* right;
    int height;
    int id;

    MovieNode(char* t, char* dir, int y, float r, int dur) {
        strncpy_s(title, 256, t, 255);
        title[255] = '\0';
        strncpy_s(director, 100, dir, 99);
        director[99] = '\0';
        year = y;
        rating = r;
        duration = dur;
        genres = new strLinkedList();
        actors = new strLinkedList();
        left = NULL;
        right = NULL;
        height = 1;
        id = -1;
    }

    ~MovieNode() {
        delete genres;
        delete actors;
    }

    // adds a genre to this movies genre list
    void addGenre(char* g) {
        genres->insert(g);
    }

    // adds an actor to this movies actor list
    void addActor(char* a) {
        actors->insert(a);
    }

    void display() {
        cout << endl;
        cout << "Title: " << title << endl;
        cout << "Director: " << director << endl;
        cout << "Year: " << year << endl;
        cout << "Rating: " << rating << endl;
        cout << "Duration: " << duration << " min" << endl;
        cout << "genres: ";
        genres->print();
        cout << endl;
        cout << "Actors: ";
        actors->print();
        cout << endl;
    }
};

// stores pointers to movie nodes
struct MovieListNode {
    MovieNode* data;
    MovieListNode* next;
    MovieListNode(MovieNode* d) : data(d), next(NULL) {}
};

//used to group movies by actor or genre
class MovieLinkedList {
public:
    MovieListNode* head;

    MovieLinkedList() : head(NULL) {}

    ~MovieLinkedList() {
        while (head) {
            MovieListNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insert(MovieNode* d) {
        MovieListNode* newNode = new MovieListNode(d);
        newNode->next = head;
        head = newNode;
    }

    //checks if a specific movie exists 
    bool contains(MovieNode* d) {
        MovieListNode* temp = head;
        while (temp) {
            if (temp->data == d)
                return true;
            temp = temp->next;
        }
        return false;
    }
};

//represents an actor with their name and movies they appeared 
class ActorNode {
public:
    char name[100];
    MovieLinkedList* movies;
    ActorNode* next;

    ActorNode(char* n) {
        strncpy_s(name, 100, n, 99);
        name[99] = '\0';
        movies = new MovieLinkedList();
        next = NULL;
    }

    //adds a movie to this actorss info
    void addMovie(MovieNode* m) {
        movies->insert(m);
    }
};

//genre with its name and list of related movies
class GenreNode {
public:
    char name[50];
    MovieLinkedList* movies;
    GenreNode* next;

    GenreNode(char* n) {
        strncpy_s(name, 50, n, 49);
        name[49] = '\0';
        movies = new MovieLinkedList();
        next = NULL;
    }

    void addMovie(MovieNode* m) {
        movies->insert(m);
    }

    ~GenreNode() {
        delete movies;
    }

};

//lookup and insertion using separate chaining for collision solution
class ActorHashTable {
private:
    int s;
    ActorNode** table;

    //hash value for an actor name using polynomial rolling hash function
    int hash(char* key) {
        int h = 0;
        char* p = key;
        while (*p) {
            h = h * 31 + *p;
            p++;
        }
        if (h < 0) h = -h;
        return h % s;
    }

public:
    ActorHashTable() {
        s = 2000;
        table = new ActorNode * [s];
        for (int i = 0; i < s; i++)
            table[i] = NULL;
    }

    ~ActorHashTable() {
        for (int i = 0; i < s; i++) {
            ActorNode* curr = table[i];
            while (curr) {
                ActorNode* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
        delete[] table;
    }

    //finds an existing actor or creates a new actor node if not found
    ActorNode* findOrInsert(char* name) {
        if (!name || strlen(name) == 0)
            return NULL;
        int index = hash(name);
        ActorNode* curr = table[index];
        while (curr) {
            if (strcmp(curr->name, name) == 0)
                return curr;
            curr = curr->next;
        }
        ActorNode* newActor = new ActorNode(name);
        newActor->next = table[index];
        table[index] = newActor;
        return newActor;
    }

    //searches n comparres all hash table buckets
    ActorNode* find(char* name) {
        if (!name) return NULL;

        for (int i = 0; i < s; i++) {
            ActorNode* curr = table[i];
            while (curr) {
                if (strcmpIgnoreCase(curr->name, name) == 0)
                    return curr;
                curr = curr->next;
            }
        }
        return NULL;
    }

    ActorNode** getTable() {
        return table;
    }

    int getSize() {
        return s;
    }
};

//lookup and insertion using separate chaining for collision resolution
class GenreHashTable {
private:
    int s;
    GenreNode** table;

    //polynomial hash function
    int hash(char* key) {
        int h = 0;
        char* p = key;
        while (*p) {
            h = h * 31 + *p;
            p++;
        }
        if (h < 0) h = -h;
        return h % s;
    }

public:
    GenreHashTable() {
        s = 500;
        table = new GenreNode * [s];
        for (int i = 0; i < s; i++)
            table[i] = NULL;
    }

    ~GenreHashTable() {
        for (int i = 0; i < s; i++) {
            GenreNode* curr = table[i];
            while (curr) {
                GenreNode* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
        delete[] table;
    }

    // finds an existing genre or creates a new genre node if not found
    GenreNode* findOrInsert(char* name) {
        if (!name || strlen(name) == 0)
            return NULL;
        int index = hash(name);
        GenreNode* curr = table[index];
        while (curr) {
            if (strcmp(curr->name, name) == 0)
                return curr;
            curr = curr->next;
        }
        GenreNode* newGenre = new GenreNode(name);
        newGenre->next = table[index];
        table[index] = newGenre;
        return newGenre;
    }

    // searches n comparres all hash table buckets
    GenreNode* find(char* name) {
        if (!name)
            return NULL;

        for (int i = 0; i < s; i++) {
            GenreNode* curr = table[i];
            while (curr) {
                if (strcmpIgnoreCase(curr->name, name) == 0)
                    return curr;
                curr = curr->next;
            }
        }
        return NULL;
    }

    GenreNode** getTable() {
        return table;
    }

    int getSize() {
        return s;
    }
};

//recently viewed movies 
class Stack {
private:
    MovieNode** data;
    int top;
    int capacity;

public:
    Stack(int size) : capacity(size), top(-1) {
        data = new MovieNode * [capacity];
    }

    void push(MovieNode* movie) {
        if (top < capacity - 1) {
            data[++top] = movie;
        }
    }

    MovieNode* pop() {
        if (top >= 0) {
            return data[top--];
        }
        return NULL;
    }

    bool isEmpty() {
        return top == -1;
    }
    void display() {
        if (isEmpty()) {
            cout << "No recently viewed movies" << endl;
            return;
        }
        cout << "\nRecently Viewed Movies" << endl;
        for (int i = top; i >= 0; i--) {
            cout << (top - i + 1) << ". " << data[i]->title << " (" << data[i]->year << ")" << endl;
        }
    }

    ~Stack() {
        delete[] data;
    }
};

//used for bfs in graph
class Queue {
public:
    int* data;
    int front;
    int rear;
    int capacity;

public:
    Queue(int size) {
        capacity = size + 1;
        data = new int[capacity];
        front = 0;
        rear = 0;
    }

    void enqueue(int val) {
        if ((rear + 1) % capacity == front)
            return;
        data[rear] = val;
        rear = (rear + 1) % capacity;
    }

    int dequeue() {
        if (front == rear)
            return -1;
        int val = data[front];
        front = (front + 1) % capacity;
        return val;
    }

    bool isEmpty() {
        return front == rear;
    }

    ~Queue() {
        delete[] data;
    }

};

//bst for storing movies sorted by title
class AVLTree {
private:
    MovieNode* root;

    int getHeight(MovieNode* node) {
        if (node)
            return node->height;
        return 0;
    }

    int getBalance(MovieNode* node) {
        if (node)
            return getHeight(node->left) - getHeight(node->right);
        return 0;
    }

    // performs right rotation to rebalance tree when left subtree is too heavy
    MovieNode* rightRotate(MovieNode* y) {
        MovieNode* x = y->left;
        MovieNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max1(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max1(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }

    // performs left rotation to rebalance tree when right subtree is too heavy
    MovieNode* leftRotate(MovieNode* x) {
        MovieNode* y = x->right;
        MovieNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max1(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max1(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }

    // recursively inserts a new movie node and rebalances the tree using rotations as needed
    MovieNode* insertRec(MovieNode* node, MovieNode* newNode) {
        if (!node) return newNode;
        if (strcmp(newNode->title, node->title) < 0)
            node->left = insertRec(node->left, newNode);
        else if (strcmp(newNode->title, node->title) > 0)
            node->right = insertRec(node->right, newNode);
        else return node;

        node->height = 1 + max1(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if (balance > 1 && strcmp(newNode->title, node->left->title) < 0)
            return rightRotate(node);
        if (balance < -1 && strcmp(newNode->title, node->right->title) > 0)
            return leftRotate(node);
        if (balance > 1 && strcmp(newNode->title, node->left->title) > 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && strcmp(newNode->title, node->right->title) < 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    // recursively searches for a movie by title using sensitive comparison
    MovieNode* searchRec(MovieNode* node, char* title) {
        if (!node)
            return NULL;

        int cmp = strcmpIgnoreCase(title, node->title);

        if (cmp == 0)
            return node;
        if (cmp < 0)
            return searchRec(node->left, title);
        return searchRec(node->right, title);
    }

    //inorder traversal to populate a linked list with all movies in sorted order
    void inorder(MovieLinkedList* list, MovieNode* node) {
        if (node) {
            inorder(list, node->left);
            list->insert(node);
            inorder(list, node->right);
        }
    }

    // recursively searches and displays all movies released in a specific year
    void searchByYearRec(MovieNode* node, int y, bool& found) {
        if (node) {
            searchByYearRec(node->left, y, found);
            if (node->year == y) {
                node->display();
                found = true;
            }
            searchByYearRec(node->right, y, found);
        }
    }

    // recursively searches and displays all movies with ratings within a specified range
    void searchByRatingRec(MovieNode* node, float minR, float maxR, bool& found) {
        if (node) {
            searchByRatingRec(node->left, minR, maxR, found);
            if (node->rating >= minR && node->rating <= maxR) {
                node->display();
                found = true;
            }
            searchByRatingRec(node->right, minR, maxR, found);
        }
    }

    // recursively deletes all nodes in the tree using postorder traversal
    void delrec(MovieNode* node) {
        if (node) {
            delrec(node->left);
            delrec(node->right);
            delete node;
        }
    }

public:
    AVLTree() : root(NULL) {}

    ~AVLTree() {
        delrec(root);
    }

    void insert(MovieNode* newNode) {
        root = insertRec(root, newNode);
    }

    MovieNode* search(char* title) {
        return searchRec(root, title);
    }

    // returns a linked list containing all movies in sorted order
    MovieLinkedList* getallM() {
        MovieLinkedList* list = new MovieLinkedList();
        inorder(list, root);
        return list;
    }

    // displays all movies from a specific year
    void searchByYear(int y) {
        cout << "Movies in year " << y << ":" << endl;
        bool found = false;
        searchByYearRec(root, y, found);
        if (!found) {
            cout << "No movies found for year " << y << endl;
        }
    }
    // displays all movies within a rating range
    void searchByRating(float minR, float maxR) {
        cout << "Movies with rating " << minR << " to " << maxR << ":" << endl;
        bool found = false;
        searchByRatingRec(root, minR, maxR, found);
        if (!found) {
            cout << "No movies found with rating between " << minR << " and " << maxR << endl;
        }
    }
};

// undirected graph representing connections between movies of shared actors and genres
class Graph {
private:
    int numV;
    intLinkedList** adjList;
    bool** adjMatrix;

    // performs bfs starting from a movie to find and display recommended movies up to a limit
    void bfsRecommend(int startId, MovieNode** movies, int limit) {
        if (startId < 0 || startId >= numV || limit <= 0)
            return;

        bool* visited = new bool[numV];
        for (int i = 0; i < numV; i++)
            visited[i] = false;

        Queue q(numV);
        q.enqueue(startId);
        visited[startId] = true;

        int count = 0;
        int level = 0;
        int maxlevel = 3;

        while (!q.isEmpty() && count < limit && level <= maxlevel) {
            int levelSize;
            if (q.rear >= q.front) {
                levelSize = q.rear - q.front;
            }
            else {
                levelSize = q.rear + q.capacity - q.front;
            }

            for (int i = 0; i < levelSize && count < limit; i++) {
                int curr = q.dequeue();

                if (curr != startId) {
                    movies[curr]->display();
                    count++;
                }

                INode* temp = adjList[curr]->head;
                while (temp) {
                    int n = temp->data;
                    if (!visited[n]) {
                        visited[n] = true;
                        q.enqueue(n);
                    }
                    temp = temp->next;
                }
            }
            level++;
        }

        delete[] visited;
    }

public:
    Graph(int n) : numV(n) {
        adjList = new intLinkedList * [n];
        adjMatrix = new bool* [n];
        for (int i = 0; i < n; i++) {
            adjList[i] = new intLinkedList();
            adjMatrix[i] = new bool[n];
            setboolvalue(adjMatrix[i], false, n);
        }
    }

    ~Graph() {
        for (int i = 0; i < numV; i++) {
            delete adjList[i];
            delete[] adjMatrix[i];
        }
        delete[] adjList;
        delete[] adjMatrix;
    }

    // add an undirected edge between two movies if they share actors or genres
    void addEdge(int u, int v) {
        if (u < 0 || u >= numV || v < 0 || v >= numV || u == v)
            return;

        if (!adjMatrix[u][v]) {
            adjList[u]->insert(v);
            adjMatrix[u][v] = true;
        }
        if (!adjMatrix[v][u]) {
            adjList[v]->insert(u);
            adjMatrix[v][u] = true;
        }
    }

    // recommended movies based on connections to the starting movie using bfs
    void recommend(int startId, MovieNode** movies, int limit = 10) {
        if (startId < 0 || startId >= numV) {
            cout << "Invalid movie ID." << endl;
            return;
        }

        bfsRecommend(startId, movies, limit);
    }

    // finds the shortest path between two movies using bfa and returns parent arr
    int* shortestPath(int start, int end) {
        if (start < 0 || start >= numV || end < 0 || end >= numV)
            return NULL;
        int* par = new int[numV];
        for (int i = 0; i < numV; i++)
            par[i] = -1;
        bool* visited = new bool[numV];
        for (int i = 0; i < numV; i++)
            visited[i] = false;

        Queue q(numV);
        q.enqueue(start);
        visited[start] = true;
        bool found = false;

        while (!q.isEmpty()) {
            int curr = q.dequeue();
            if (curr == end) {
                found = true;
                break;
            }
            INode* temp = adjList[curr]->head;
            while (temp) {
                int adj = temp->data;
                if (!visited[adj]) {
                    visited[adj] = true;
                    par[adj] = curr;
                    q.enqueue(adj);
                }
                temp = temp->next;
            }
        }
        delete[] visited;
        if (!found) {
            delete[] par;
            return NULL;
        }
        return par;
    }

    // reconstructs and gives the shortest path between two movies using the parent arr from bfs
    void printPath(int* par, int start, int end, MovieNode** movies) {
        if (!par) {
            cout << "No connection found." << endl;
            return;
        }
        cout << "Shortest connection path: ";

        int* path = new int[numV];
        int plen = 0;
        int curr = end;

        while (curr != -1) {
            path[plen++] = curr;
            if (curr == start)
                break;
            curr = par[curr];
        }

        for (int i = plen - 1; i >= 0; i--) {
            cout << movies[path[i]]->title;
            if (i > 0)
                cout << " -> ";
        }
        cout << endl;

        delete[] path;
    }
};

// parses csv line handling quoted fields and comma separators to extract individual cols
void parseCSV(char* line, char** cols, int maxcol) {
    int colidx = 0;
    char* p = line;
    bool inQ = false;
    char buff[5045];
    int bidx = 0;

    while (*p && colidx < maxcol) {
        if (*p == '"') {
            inQ = !inQ;
        }
        else if (*p == ',' && !inQ) {
            buff[bidx] = '\0';
            cols[colidx] = new char[bidx + 1];
            strcpy_s(cols[colidx], bidx + 1, buff);
            colidx++;
            bidx = 0;
        }
        else {
            buff[bidx++] = *p;
        }
        p++;
    }
    if (colidx < maxcol) {
        buff[bidx] = '\0';
        int len = strlen(buff);
        if (len > 0 && buff[len - 1] == '\r')
            buff[len - 1] = '\0';
        cols[colidx] = new char[strlen(buff) + 1];
        strcpy_s(cols[colidx], strlen(buff) + 1, buff);
        colidx++;
    }
}

// manages all program
class MoviesDataManager {
private:
    AVLTree* movieTree;
    ActorHashTable* actorHash;
    GenreHashTable* genreHash;
    Graph* movieGraph;
    MovieNode** moviesArray;
    Stack* recentlyViewed;
    int numMovies;

    // builds a graph connecting movies that share actors or genres for recommendation system
    void buildGraph() {
        MovieLinkedList* allM = movieTree->getallM();
        numMovies = 0;
        MovieListNode* temp = allM->head;
        while (temp) {
            numMovies++;
            temp = temp->next;
        }
        if (numMovies == 0) {
            delete allM;
            return;
        }
        moviesArray = new MovieNode * [numMovies];
        temp = allM->head;
        int i = 0;
        while (temp) {
            temp->data->id = i;
            moviesArray[i++] = temp->data;
            temp = temp->next;
        }
        delete allM;

        movieGraph = new Graph(numMovies);

        ActorNode** actorTable = actorHash->getTable();
        for (int j = 0; j < actorHash->getSize(); j++) {
            ActorNode* act = actorTable[j];
            while (act) {
                MovieListNode* m1 = act->movies->head;
                while (m1) {
                    MovieListNode* m2 = m1->next;
                    while (m2) {
                        movieGraph->addEdge(m1->data->id, m2->data->id);
                        m2 = m2->next;
                    }
                    m1 = m1->next;
                }
                act = act->next;
            }
        }

        GenreNode** genreTable = genreHash->getTable();
        for (int j = 0; j < genreHash->getSize(); j++) {
            GenreNode* gen = genreTable[j];
            while (gen) {
                MovieListNode* m1 = gen->movies->head;
                while (m1) {
                    MovieListNode* m2 = m1->next;
                    while (m2) {
                        movieGraph->addEdge(m1->data->id, m2->data->id);
                        m2 = m2->next;
                    }
                    m1 = m1->next;
                }
                gen = gen->next;
            }
        }
    }

public:
    MoviesDataManager() {
        movieTree = new AVLTree();
        actorHash = new ActorHashTable();
        genreHash = new GenreHashTable();
        movieGraph = NULL;
        moviesArray = NULL;
        recentlyViewed = new Stack(10);
        numMovies = 0;
    }

    ~MoviesDataManager() {
        delete movieTree;
        delete actorHash;
        delete genreHash;
        if (movieGraph)
            delete movieGraph;
        if (moviesArray)
            delete[] moviesArray;
        delete recentlyViewed;
    }

    // loads movie data from csv file, parsing all rows n creates movie obj n graph
    void loadDataset(const char* filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Cannot open file: " << filename << endl;
            return;
        }
        char line[8192];
        file.getline(line, 8192);

        int count = 0;
        while (file.getline(line, 8192)) {
            char* cols[28] = { NULL };
            parseCSV(line, cols, 28);

            if (!cols[11] || !cols[1]) {
                for (int k = 0; k < 28; k++)
                    if (cols[k])
                        delete[] cols[k];
                continue;
            }

            char title[256];
            strcpy_s(title, 256, cols[11]);
            cleanTitle(title);
            int tLen = strlen(title);
            while (tLen > 0 && isSpace(title[tLen - 1]))
                title[--tLen] = '\0';

            char director[100];
            strcpy_s(director, 100, cols[1]);

            int year;
            if (cols[23]) {
                year = sTi(cols[23]);
            }
            else {
                year = 0;
            }

            float rating;
            if (cols[25]) {
                rating = sTf(cols[25]);
            }
            else {
                rating = 0;
            }

            int duration;
            if (cols[3]) {
                duration = sTi(cols[3]);
            }
            else {
                duration = 0;
            }
            MovieNode* movie = new MovieNode(title, director, year, rating, duration);

            if (cols[9]) {
                char gen[512];
                strcpy_s(gen, 512, cols[9]);
                Split tokenizer(gen, '|');
                char* g = tokenizer.nextToken();
                while (g) {
                    movie->addGenre(g);
                    GenreNode* gn = genreHash->findOrInsert(g);
                    if (gn) gn->addMovie(movie);
                    g = tokenizer.nextToken();
                }
            }

            int actIdx[] = { 10, 6, 14 };
            for (int i = 0; i < 3; i++) {
                int idx = actIdx[i];
                if (cols[idx] && strlen(cols[idx]) > 0) {
                    movie->addActor(cols[idx]);
                    ActorNode* an = actorHash->findOrInsert(cols[idx]);
                    if (an)
                        an->addMovie(movie);
                }
            }

            movieTree->insert(movie);
            count++;

            for (int k = 0; k < 28; k++)
                if (cols[k])
                    delete[] cols[k];
        }
        cout << "Loaded " << count << " movies." << endl;
        buildGraph();
    }

    // search adds it to recently viewed stack
    void searchByTitle(char* title) {
        MovieNode* m = movieTree->search(title);
        if (m) {
            m->display();
            recentlyViewed->push(m);
        }
        else {
            cout << "Movie '" << title << "' not found." << endl;
        }
    }

    //all movies featuring specific actor
    void searchByActor(char* name) {
        ActorNode* act = actorHash->find(name);
        if (act) {
            cout << "Movies by " << name << ":" << endl;
            MovieListNode* temp = act->movies->head;
            while (temp) {
                cout << "- " << temp->data->title << " (" << temp->data->year << ")" << endl;
                temp = temp->next;
            }
        }
        else cout << "Actor '" << name << "' not found." << endl;
    }

    //all movies belonging to specific genre
    void searchByGenre(char* name) {
        GenreNode* gen = genreHash->find(name);
        if (gen) {
            cout << "Movies in genre " << name << ":" << endl;
            MovieListNode* temp = gen->movies->head;
            while (temp) {
                cout << "- " << temp->data->title << endl;
                temp = temp->next;
            }
        }
        else cout << "Genre '" << name << "' not found." << endl;
    }

    //all movies released in specific year
    void searchByYear(int y) {
        cout << "Movies in year " << y << ":" << endl;
        movieTree->searchByYear(y);
    }

    //all movies with ratings within range
    void searchByRating(float minR, float maxR) {
        cout << "Movies with rating " << minR << " to " << maxR << ":" << endl;
        movieTree->searchByRating(minR, maxR);
    }

    // recommends movies similar to the given title based on shared actors and genres
    void recommend(char* title, int limit = 5) {
        MovieNode* m = movieTree->search(title);
        if (!m) {
            cout << "Movie not found." << endl;
            return;
        }
        cout << "\n Recommendations for '" << title << "' " << endl;
        if (movieGraph)
            movieGraph->recommend(m->id, moviesArray, limit);
    }

    // finds and displays the shortest connection path between two movies through shared actors or genres
    void shortestPath(char* title1, char* title2) {
        MovieNode* m1 = movieTree->search(title1);
        MovieNode* m2 = movieTree->search(title2);
        if (!m1 || !m2) {
            cout << "One or both movies not found." << endl;
            return;
        }
        if (movieGraph) {
            int* par = movieGraph->shortestPath(m1->id, m2->id);
            movieGraph->printPath(par, m1->id, m2->id, moviesArray);
            if (par)
                delete[] par;
        }
    }
    void showRecentlyViewed() {
        recentlyViewed->display();
    }

    //it creates a hash table to store all co-actors of a specific actor
    void showCoActors(char* aName) {
        ActorNode* act = actorHash->find(aName);
        if (!act) {
            cout << "Actor '" << aName << "' not found." << endl;
            return;
        }
        ActorHashTable tempCo;
        MovieListNode* mNode = act->movies->head;

        while (mNode) {
            StrNode* mAct = mNode->data->actors->head;
            while (mAct) {
                if (strcmpIgnoreCase(mAct->data, aName) != 0) {
                    tempCo.findOrInsert(mAct->data);
                }
                mAct = mAct->next;
            }
            mNode = mNode->next;
        }
        cout << "Co-actors of " << aName << ":" << endl;
        bool found = false;
        ActorNode** tempT = tempCo.getTable();
        int tableSize = tempCo.getSize();

        for (int i = 0; i < tableSize; i++) {
            ActorNode* curr = tempT[i];
            while (curr) {
                cout << "- " << curr->name << endl;
                found = true;
                curr = curr->next;
            }
        }

        if (!found) {
            cout << "No co-actors found." << endl;
        }
    }

    //analyzes director filmography with case insensitive search
    void analyzeDirector(char* dirName) {
        cout << "\nDirector Analysis: " << dirName << endl;

        MovieLinkedList* allM = movieTree->getallM();
        MovieListNode* temp = allM->head;

        int c = 0;
        float tRate = 0;
        int minY = 9999, maxY = 0;
        float avgD = 0;

        while (temp) {
            char lowD[100];
            strcpy_s(lowD, 100, temp->data->director);
            toLower(lowD);

            char lowS[100];
            strcpy_s(lowS, 100, dirName);
            toLower(lowS);

            if (strstr(lowD, lowS)) {
                c++;
                tRate += temp->data->rating;
                avgD += temp->data->duration;

                if (temp->data->year < minY) minY = temp->data->year;
                if (temp->data->year > maxY) maxY = temp->data->year;

                cout << c << ". " << temp->data->title
                    << " (" << temp->data->year << ") "
                    << "Rating: " << temp->data->rating << endl;
            }
            temp = temp->next;
        }

        if (c > 0) {
            cout << "\nStatistics:" << endl;
            cout << "Total films: " << c << endl;
            cout << "Career span: " << minY << "-" << maxY
                << " (" << (maxY - minY) << " years)" << endl;
            cout << "Average rating: " << (tRate / c) << endl;
            cout << "Average duration: " << (avgD / c) << " minutes" << endl;
        }
        else {
            cout << "Director not found." << endl;
        }
        delete allM;
    }
};

int main() {
    MoviesDataManager manager;
    manager.loadDataset("movie_metadata.csv");

    int choice;
    char buf[256];
    char buf2[256];

    while (true) {
        cout << "\nMovies Data Manager" << endl;
        cout << "1. Search by title" << endl;
        cout << "2. Search by actor" << endl;
        cout << "3. Search by genre" << endl;
        cout << "4. Search by year" << endl;
        cout << "5. Search by rating range" << endl;
        cout << "6. Recommend movies" << endl;
        cout << "7. Shortest connection path" << endl;
        cout << "8. Show recently viewed" << endl;
        cout << "9. Show co-actors" << endl;
        cout << "10. Analyze director filmography" << endl;
        cout << "11. Exit" << endl;
        cout << "Choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            while (cin.get() != '\n');
            continue;
        }
        while (cin.get() != '\n');

        if (choice == 11)
            break;

        switch (choice) {
        case 1:
            cout << "Enter Title: ";
            cin.getline(buf, 256);
            manager.searchByTitle(buf);
            break;
        case 2:
            cout << "Enter Actor: ";
            cin.getline(buf, 256);
            manager.searchByActor(buf);
            break;
        case 3:
            cout << "Enter Genre: ";
            cin.getline(buf, 256);
            manager.searchByGenre(buf);
            break;
        case 4:
            int y; cout << "Enter Year: ";
            cin >> y;
            manager.searchByYear(y);
            break;
        case 5:
            float minR, maxR;
            cout << "Min rating: ";
            cin >> minR;
            cout << "Max rating: ";
            cin >> maxR;
            manager.searchByRating(minR, maxR);
            break;
        case 6:
            cout << "Enter Movie Title: ";
            cin.getline(buf, 256);
            manager.recommend(buf);
            break;
        case 7:
            cout << "Enter Start Movie: ";
            cin.getline(buf, 256);
            cout << "Enter End Movie: ";
            cin.getline(buf2, 256);
            manager.shortestPath(buf, buf2);
            break;
        case 8:
            manager.showRecentlyViewed();
            break;
        case 9:
            cout << "Enter Actor Name for co-actors: ";
            cin.getline(buf, 256);
            manager.showCoActors(buf);
            break;
        case 10:
            cout << "Enter Director Name: ";
            cin.getline(buf, 256);
            manager.analyzeDirector(buf);
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    }
    return 0;
}
