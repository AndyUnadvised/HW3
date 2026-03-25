/*
* CSE 3318 - Homework 3
* Name: Mason Morales, Abril Hernandez
* UTA ID: 1002210043, 1002191322
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
void selectRandomElements(int* sourceArray, int sourceSize, int*
targetArray, int numElements);
int main() {
 // Seed the random number generator
 srand(time(NULL));

 // Variables for timing
 clock_t start_time, end_time;
 double time_taken;
 int sizes[] = {30, 1000, 6000, 10000};
 const char* filenames[] = {"nodes30.txt", "nodes1000.txt",
"nodes6000.txt", "nodes10000.txt"};
 const char* sfilenames[] = {"snodes30.txt", "snodes1000.txt",
"snodes6000.txt", "snodes10000.txt"};
 int num_files = 4;
 // PART 1: Generation of Data
 printf("--- Part 1: Generating Data ---\n");
 for (int i = 0; i < num_files; i++) {
 // TODO: generate data for each size and filename
 // Ensure the generated integers are UNIQUE and between 0 and 20000
 // Save the data in nodes<x>.txt file
 // Sort the data
 // Example of how to measure time (Use this pattern for all measurements)
 start_time = clock();
 // TODO: Sort the array
 end_time = clock();
 time_taken = ((double)(end_time - start_time)) /
CLOCKS_PER_SEC;
 printf("Time to sort array of size %d: %f seconds\n",
sizes[i], time_taken);
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
 // TODO: Free BSTs (randomBST and sortedBST) using freeTree()

 printf("\n");
 }
 return 0;
}
// -------------------------------------------------------------------

// Function Implementations (Students to complete)
// -------------------------------------------------------------------

// TODO: Implement all the functions declared in the prototypes above.