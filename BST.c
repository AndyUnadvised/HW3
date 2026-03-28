/* 
 * CSE 3318 - Homework 3 
 * Name: [Mason Morales, Abril Hernandez 
 * UTA ID: [1002210043, 1002] 
 */ 
 
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <stdbool.h> 
 
typedef struct Node { 
    int key; 
    struct Node *left; 
    struct Node *right; 
} Node; 
 


// Part 1: Data Generation 
void generateData(int num_files,int* sizes, const char** filename, const char** sfilenames);

// Part 2: Array Operations 
int* readDataToArray(const char* filename, int size); 
void sortArray(int* arr, int size);  
int linearSearch(int* arr, int size, int target); 
int binarySearch(int* arr, int size, int target); 
 
// Part 3: BST Operations 
Node* createNode(int key); 
Node* insertRecursive(Node* root, int key); 
Node* insertIterative(Node* root, int key); 
Node* searchBST(Node* root, int target); 
void freeTree(Node* root); 
 
// Utility Functions 
void selectRandomElements(int* sourceArray, int sourceSize, int* targetArray, int numElements); 
 


int main() 
{ 
    srand(time(NULL)); 
    clock_t start, end;
    int sizes[] = {30, 1000, 6000, 10000}; 
    const char* filenames[] = {"nodes30.txt", "nodes1000.txt", "nodes6000.txt", "nodes10000.txt"}; 
    const char* sfilenames[] = {"snodes30.txt", "snodes1000.txt", "snodes6000.txt", "snodes10000.txt"}; 
    int num_files = 4;

    
    generateData(num_files, sizes, filenames, sfilenames);

    // PART 2 & 3 Loop
    for (int i = 0; i < num_files; i++) {
        printf("=== Processing Dataset Size: %d ===\n", sizes[i]);

        // --- PART 2: Array Operations ---
        int* sortedArr = readDataToArray(sfilenames[i], sizes[i]);
        if (sortedArr == NULL) continue;
        int targets[10];
        //Select 10 random elements from the sorted array for searching
        selectRandomElements(sortedArr, sizes[i], targets, 10);

        // Linear Search Time
        start = clock();
        for(int j=0; j<10; j++) linearSearch(sortedArr, sizes[i], targets[j]);
        end = clock();
        printf("Linear Search (10 elements): %f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

        // Binary Search Time
        start = clock();
        for(int j=0; j<10; j++) binarySearch(sortedArr, sizes[i], targets[j]);
        end = clock();
        printf("Binary Search (10 elements): %f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

        // --- PART 3: BST Operations ---
        int* unsortedArr = readDataToArray(filenames[i], sizes[i]);
        Node* randomBST = NULL;
        Node* sortedBST = NULL;

        // Build Random BST
        start = clock();
        for(int j = 0; j < sizes[i]; j++) randomBST = insertIterative(randomBST, unsortedArr[j]);
        end = clock();
        printf("Tree Creation (Random): %f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

        // Build Sorted BST (Degenerate)
        start = clock();
        for(int j = 0; j < sizes[i]; j++) sortedBST = insertIterative(sortedBST, sortedArr[j]);
        end = clock();
        printf("Tree Creation (Sorted): %f sec\n", (double)(end - start) / CLOCKS_PER_SEC);
        
        // Search Trees
        start = clock();
        for(int j=0; j<10; j++) searchBST(randomBST, targets[j]);
        end = clock();
        printf("Random BST Search: %f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

        start = clock();
        for(int j=0; j<10; j++) searchBST(sortedBST, targets[j]);
        end = clock();
        printf("Sorted BST Search: %f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

        // New Random Insertions
        int newKeys[10];
        for(int j=0; j<10; j++) newKeys[j] = rand() % 20001;

        start = clock();
        for(int j=0; j<10; j++) {
            randomBST = insertIterative(randomBST, newKeys[j]);
            sortedBST = insertIterative(sortedBST, newKeys[j]);
        }
        end = clock();
        printf("Iterative Insertion Time (Both Trees): %f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

        int recKeys[10];
        for(int j=0; j<10; j++) recKeys[j] = rand() % 20001;

        start = clock();
        for(int j=0; j<10; j++) {
            randomBST = insertRecursive(randomBST, recKeys[j]);
            sortedBST = insertRecursive(sortedBST, recKeys[j]);
        }
        end = clock();
        printf("Recursive Insertion (Both): %f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

        // Cleanup
        free(sortedArr);
        free(unsortedArr);
        freeTree(randomBST);
        freeTree(sortedBST);
        printf("\n");
    }
    return 0;
}


// Part 1: Data Generation 
void generateData(int num_files, int* sizes, const char** filenames, const char** sfilenames) 
{
    printf("--- Part 1: Generating Data ---\n"); 
    
    int poolSize = 20001;
    int* pool = (int*)malloc(poolSize * sizeof(int));
    for (int i = 0; i < poolSize; i++) pool[i] = i;

    for (int i = 0; i < num_files; i++) {
        // Shuffle the pool for uniqueness
        for (int j = poolSize - 1; j > 0; j--) {
            int k = rand() % (j + 1);
            int temp = pool[j]; pool[j] = pool[k]; pool[k] = temp;
        }

        // Write Unsorted
        FILE *uFile = fopen(filenames[i], "w");
        int* currentData = (int*)malloc(sizes[i] * sizeof(int));
        for (int j = 0; j < sizes[i]; j++) {
            currentData[j] = pool[j];
            fprintf(uFile, "%d\n", currentData[j]);
        }
        fclose(uFile);

        // Sort and Measure
        clock_t start = clock();
        sortArray(currentData, sizes[i]);
        clock_t end = clock();
        printf("Time to sort array of size %d: %f seconds\n", sizes[i], (double)(end - start) / CLOCKS_PER_SEC);

        // Write Sorted
        FILE *sFile = fopen(sfilenames[i], "w");
        for (int j = 0; j < sizes[i]; j++) {
            fprintf(sFile, "%d\n", currentData[j]);
        }
        fclose(sFile);
        free(currentData);
    }
    free(pool);
    printf("Data generation complete.\n\n");
}

int* readDataToArray(const char* filename, int size){
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file %s\n", filename);
        return NULL;
    }
    int* arr = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);
    return arr;
}

int comp(const void *a, const void *b) 
{
    return (*(int *)a - *(int *)b);
}

void sortArray(int* arr, int size) 
{
    qsort(arr, size, sizeof(int), comp);
}


int linearSearch(int* arr, int size, int target)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == target)
        {
            return i; // Found
        }
    }
    return -1; // Not found
}

int binarySearch(int* arr, int size, int target) 
{
    int left = 0, right = size - 1;
    while (left <= right) 
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
        {
            return mid; // Found
        }

        else if (arr[mid] < target) 
        {
            left = mid + 1; // Search in the right half
        } 

        else 
        {
            right = mid - 1; // Search in the left half
        }
    }
    return -1; // Not found
}

//Part 3: BST Operations
Node* createNode(int key) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


Node* insertRecursive(Node* root, int key) 
{
    if (root == NULL) 
    {
        return createNode(key);
    }

    if (key < root->key)
    {
        root->left = insertRecursive(root->left, key);
    } 
    
    else if (key > root->key) 
    {
        root->right = insertRecursive(root->right, key);
    }

    return root; 
}

Node* insertIterative(Node* root, int key) 
{
    Node* newNode = createNode(key);

    if (root == NULL) 
    {
        return newNode;
    }

    Node* parent = NULL;
    Node* current = root;

    while (current != NULL) 
    {
        parent = current;

        if (key < current->key) 
        {
            current = current->left;
        } 

        else if (key > current->key) 
        {
            current = current->right;
        } 

        else 
        {
            free(newNode); 
            return root; 
        }
    }

    if (key < parent->key) 
    {
        parent->left = newNode;
    } 
    
    else 
    {
        parent->right = newNode;
    }

    return root;
}

Node* searchBST(Node* root, int target) 
{
    while (root != NULL) 
    {
        if (target == root->key) 
        {
            return root; // Found
        } 
        
        else if (target < root->key) 
        {
            root = root->left; // Search in the left subtree
        } 
        
        else 
        {
            root = root->right; // Search in the right subtree
        }
    }
    return NULL; // Not found
}


void freeTree(Node* root) 
{
    if (root != NULL) 
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

//Part 4: Utility Functions
void selectRandomElements(int* sourceArray, int sourceSize, int* targetArray, int numElements) 
{
    for (int i = 0; i < numElements; i++)
    {
        int randomIndex = rand() % sourceSize;
        targetArray[i] = sourceArray[randomIndex];
    }
}