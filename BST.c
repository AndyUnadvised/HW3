/* 
 * CSE 3318 - Homework 3 
 * Name: [Mason Morales] 
 * UTA ID: [1002210043] 
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
void generateData(int size, const char* filename);

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
    // Seed the random number generator 
    srand(time(NULL)); 
     
    // Variables for timing 
    clock_t start_time, end_time; 
    double time_taken; 
 
    int sizes[] = {30, 1000, 6000, 10000}; 
    const char* filenames[] = {"nodes30.txt", "nodes1000.txt", "nodes6000.txt", "nodes10000.txt"}; 
    const char* sfilenames[] = {"snodes30.txt", "snodes1000.txt", "snodes6000.txt", "snodes10000.txt"}; 
    int num_files = 4;

    generateData(num_files, sizes);

}


//Part 1: Data Generation   
void generateData(int num_files, int* sizes) 
{

   // PART 1: Generation of Data 
    printf("--- Part 1: Generating Data ---\n"); 
    for (int i = 0; i < num_files; i++) { 
        // TODO: generate data for each size and filename 


        // Ensure the generated integers are UNIQUE and between 0 and  20000 
        FILE *file = fopen(filenames[i], "w");
        for (int j = 0; j < sizes[i]; j++)
        {
            int num = rand() % 20001 ; // Random integer between 0 and 20000
            fprintf(file, "%d\n", num);
        }
        fclose(file);


        // Save the data in nodes<x>.txt file 
        // Sort the data 
        // Example of how to measure time (Use this pattern for all measurements) 
        start_time = clock(); 
        // TODO: Sort the array  

        end_time = clock(); 
        time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC; 
        printf("Time to sort array of size %d: %f seconds\n", sizes[i], time_taken); 
 
         // Save the sorted data in snode<x>.txt file 
    } 
    printf("Data generation complete.\n\n"); 
 
 
    // PART 2 & 3 Loop: Process each dataset size 
    for (int i = 0; i < num_files; i++) { 
        printf("=== Processing Dataset Size: %d ===\n", sizes[i]); 
 
        // --- PART 2: Search on Sorted Array --- 
        // TODO: Read data from sfilenames[i] into an array 
         
        // TODO: Select 10 random elements from the array 
         
        // TODO: Measure time for Linear Search of the 10 elements 
        // TODO: Measure time for Binary Search of the 10 elements 
 
 
        // --- PART 3: Search and Insertion on Binary Search Tree --- 
         
        // 1. Random BST (Insert keys in the exact order they appear in the file) 
        Node* randomBST = NULL; 
        // TODO: Read from file again or use an unsorted copy of the array to insert elements 
         
        // 2. Sorted BST (Insert keys from the sorted array) 
        Node* sortedBST = NULL; 
  // TODO: Measure time to Search for those 10 elements in BOTH trees 
// TODO: Insert elements from the sorted array into sortedBST 
         
        // TODO: Generate 10 NEW random elements (between 0 and 20000) 
         
        // TODO: Measure time for Iterative Insertion of these 10 elements into BOTH trees 
        // TODO: Measure time for Recursive Insertion of these 10 elements into BOTH trees 
         
 
// Cleanup memory for this iteration 
// TODO: Free arrays 
        free(arr); // Assuming arr is the array used for this iteration
// TODO: Free BSTs (randomBST and sortedBST) using freeTree() 
    freeTree(randomBST);
    freeTree(sortedBST);

printf("\n"); 
} 
    return 0; 
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

void selectRandomElements(int* sourceArray, int sourceSize, int* targetArray, int numElements) 
{
    for (int i = 0; i < numElements; i++)
    {
        int randomIndex = rand() % sourceSize;
        targetArray[i] = sourceArray[randomIndex];
    }
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