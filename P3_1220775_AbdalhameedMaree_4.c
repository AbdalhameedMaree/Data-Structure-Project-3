/*
  ABDALHAMEED MAREE - 1220775 - SEC: 4
              PROJECT NUM: 3
          HASHING AND AVL TREES
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASH_SIZE 1009
#define REHASH_SIZE 2027

// This section is for the AVL Binary Tree

// AVLNode structure definition
typedef struct AVLNode
{
  char string[50];       // String stored in the node
  struct AVLNode *Left;  // Pointer to the left child
  struct AVLNode *Right; // Pointer to the right child
  int Height;            // Height of the node in the tree
  int frequency;         // Frequency of the string
} AVLNode;

// Function prototypes for AVL tree operations
AVLNode *Find(char *string, AVLNode *root);   // Find a node with the given string
AVLNode *FindMin(AVLNode *root);              // Find the node with the minimum value
AVLNode *FindMax(AVLNode *root);              // Find the node with the maximum value
AVLNode *SingleRotateToRight(AVLNode *root);  // Single right rotation
AVLNode *SingleRotateToLeft(AVLNode *root);   // Single left rotation
AVLNode *DoubleRotateToRight(AVLNode *root);  // Double right rotation
AVLNode *DoubleRotateToLeft(AVLNode *root);   // Double left rotation
AVLNode *Insert(char *string, AVLNode *root); // Insert a node into the AVL tree
AVLNode *Delete(char *string, AVLNode *root); // Delete a node from the AVL tree
int Height(AVLNode *root);                    // Get the height of a node
int Max(int Lhs, int Rhs);                    // Get the maximum of two integers
int toAscii(char *string);                    // Convert a string to its ASCII sum
void PrintInOrder(AVLNode *root);             // Print the AVL tree in order

// The following functions are used for hashing

// HashNode structure definition for hash table
typedef struct HashNode
{
  char string[50]; // String stored in the hash table node
  int frequency;   // Frequency of the string
} HashNode;

int Counter = 0, REHASHFLAG = 0;
HashNode *ReHashTable[REHASH_SIZE] = {NULL};

// Function prototypes for hash table operations
void InsertToHashTable(char *string, HashNode *Array[], int size, int frequency); // Insert a string into the hash table
int FirstHashFunction(int number, int size);                                      // First hash function
int SecondHashFunction(int number, int size);                                     // Second hash function
void DeleteFromHashTable(char *string, HashNode *Array[], int size);              // Delete a string from the hash table
int search(char *string, HashNode *Array[], int HashSize);                        // Search for a string in the hash table
void PrintHashData(HashNode *Array[], int size);                                  // Print the contents of the hash table
void InsertFromAVLToHash(AVLNode *root, HashNode *Array[]);                       // Insert all elements from AVL tree to hash table
void ReHash(HashNode *OldArray[], HashNode *NewArray[]);                          // Doing the rehash operation
/*
  this section is used for global functions
*/
void menu();
AVLNode *LoadInputFile(AVLNode *root);
void fixString(char *string);
void toLowerCase(char *string);

int main()
{
  AVLNode *root;
  HashNode *HashTable[HASH_SIZE];
  int option, AVLFlag = 0, HashFlag = 0;

  while (1)
  {
    menu();
    printf("Enter your choice: ");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
    {
      if (AVLFlag == 0)
      {
        printf("The Tree is not created yet.\n");
        break;
      }
      else
        root = LoadInputFile(root);

      printf("The file has been loaded successfully.\n");
      break;
    }
    case 2:
    {
      root = NULL;
      printf("The AVLTree has been created successfully. \n");
      AVLFlag = 1;
      break;
    }
    case 3:
    {
      if (AVLFlag != 1)
      {
        printf("The AVLTree is not created yet.\n");
        break;
      }

      printf("Enter the word you want to add: ");
      char string[50];
      scanf("%s", string);
      fixString(string);
      toLowerCase(string);
      root = Insert(string, root);
      printf("The word has been added successfully.\n");
      break;
    }
    case 4:
    {
      if (AVLFlag != 1)
      {
        printf("The AVLTree is not created yet.\n");
        break;
      }

      printf("Enter the word you want to Delete: ");
      char string[50];
      scanf("%s", string);
      toLowerCase(string);
      root = Delete(string, root);
      printf("The word has been deleted successfully.\n");
      break;
    }
    case 5:
    {
      if (AVLFlag != 1)
      {
        printf("The AVLTree is not created yet.\n");
        break;
      }

      PrintInOrder(root);
      break;
    }
    case 6:
    {
      for (int i = 0; i < HASH_SIZE; i++)
        HashTable[i] = NULL;

      if (HashTable == NULL)
      {
        printf("Out of memory\n");
        break;
      }
      HashFlag = 1;
      InsertFromAVLToHash(root, HashTable);
      printf("Hash table created successfully.\n");
      break;
    }
    case 7:
    {
      if (HashFlag != 1 || HashTable == NULL)
      {
        printf("The hash Table is not created yet.\n");
        break;
      }

      char word[50];
      printf("Enter a word to insert: ");
      scanf("%s", word);
      fixString(word);
      toLowerCase(word);

      if (REHASHFLAG == 0)
        InsertToHashTable(word, HashTable, HASH_SIZE, 1);
      else
        InsertToHashTable(word, ReHashTable, REHASH_SIZE, 1);
      printf("Word inserted into hash table.\n");
      break;
    }
    case 8:
    {
      if (HashFlag != 1 || HashTable == NULL)
      {
        printf("The hash Table is not created yet.\n");
        break;
      }

      char wordToDelete[50];
      printf("Enter word to delete: ");
      scanf("%s", wordToDelete);
      toLowerCase(wordToDelete);
      if (REHASHFLAG == 0)
        DeleteFromHashTable(wordToDelete, HashTable, HASH_SIZE);
      else
        DeleteFromHashTable(wordToDelete, ReHashTable, REHASH_SIZE);

      printf("Word deleted from hash table.\n");
      break;
    }
    case 9:
    {
      if (HashFlag != 1 || HashTable == NULL)
      {
        printf("The hash Table is not created yet.\n");
        break;
      }

      char wordToSearch[50];
      printf("Enter word to search: ");
      scanf("%s", wordToSearch);
      toLowerCase(wordToSearch);
      int searchResult;
      if (REHASHFLAG == 0)
        searchResult = search(wordToSearch, HashTable, HASH_SIZE);

      else
        searchResult = search(wordToSearch, ReHashTable, REHASH_SIZE);

      if (searchResult == -1)
      {
        printf("Word not found in hash table.\n");
      }
      else
        printf("Word found at index %d in hash table. Frequency: %d\n", searchResult, HashTable[searchResult]->frequency);
      break;
    }

    case 10:
    {
      if (HashFlag != 1 || HashTable == NULL)
      {
        printf("The hash Table is not created yet.\n");
        break;
      }
      if (REHASHFLAG == 0)
        PrintHashData(HashTable, HASH_SIZE);
      else
        PrintHashData(ReHashTable, REHASH_SIZE);
      break;
    }
    case 11:
    {
      printf("Exiting the application.\n");
      exit(0);
    }
    default:
      printf("Invalid choice. Please enter a number between 1 and 11.\n");
      break;
    }
  }

  return 0;
}

void menu()
{
  printf(
      "\n"
      "1. Load data from the file.\n"
      "2. Create the AVL tree.\n"
      "3. Insert a word to the AVL tree.\n"
      "4. Delete a word from the AVL tree.\n"
      "5. Print the words as sorted in the AVL tree.\n"
      "6. Create the Hash Table.\n"
      "7. Insert a word to the Hash table.\n"
      "8. Delete a word from the hash table.\n"
      "9. Search for a word in the hash table and print its frequency.\n"
      "10. Print words statistics.\n"
      "11. Exit the application.\n");
}

AVLNode *LoadInputFile(AVLNode *root) // loads the input data
{
  FILE *input = fopen("input.txt", "r");
  if (input == NULL)
  {
    printf("can't open the file.\n");
    return NULL;
  }

  char string[100];
  while (fgets(string, sizeof(string), input) != NULL)
  {
    char *str = strtok(string, " ");
    while (str != NULL)
    {
      fixString(str);
      toLowerCase(str);
      root = Insert(str, root);
      str = strtok(NULL, " ");
    }
  }

  fclose(input);
  return root;
}

void fixString(char *string)
{
  int j = 0;
  for (int i = 0; string[i] != '\0'; i++)
  {
    if ((string[i] >= 'A' && string[i] <= 'Z') || (string[i] >= 'a' && string[i] <= 'z'))
    {
      string[j++] = string[i];
    }
  }
  string[j] = '\0';
}

void toLowerCase(char *string)
{
  for (int i = 0; string[i] != '\0'; i++)
    tolower(string[i]);
}

int toAscii(char *string)
{
  int counter = 0;
  while (*string != '\0')
  {
    counter += *string;
    string++;
  }
  return counter;
}

AVLNode *Find(char *string, AVLNode *root)
{
  if (root == NULL)
    return NULL;
  if (strcmp(string, root->string) == -1)
    return Find(string, root->Left);
  else if (strcmp(string, root->string) == 1)
    return Find(string, root->Right);
  else
    return root;
}

AVLNode *FindMin(AVLNode *root)
{
  if (root == NULL)
    return NULL;
  else if (root->Left == NULL)
    return root;
  else
    return FindMin(root->Left);
}

AVLNode *FindMax(AVLNode *root)
{
  if (root != NULL)
    while (root->Right != NULL)
      root = root->Right;

  return root;
}

int Height(AVLNode *root)
{
  if (root == NULL)
    return -1;
  else
    return root->Height;
}

int Max(int Lhs, int Rhs)
{
  return Lhs > Rhs ? Lhs : Rhs;
}

AVLNode *SingleRotateToRight(AVLNode *root)
{
  AVLNode *tempNode;

  tempNode = root->Left;
  root->Left = tempNode->Right;
  tempNode->Right = root;

  root->Height = Max(Height(root->Left), Height(root->Right)) + 1;
  tempNode->Height = Max(Height(tempNode->Left), root->Height) + 1;

  return tempNode;
}

AVLNode *SingleRotateToLeft(AVLNode *root)
{
  AVLNode *tempNode;

  tempNode = root->Right;
  root->Right = tempNode->Left;
  tempNode->Left = root;

  root->Height = Max(Height(root->Left), Height(root->Right)) + 1;
  tempNode->Height = Max(Height(tempNode->Right), root->Height) + 1;

  return tempNode;
}

AVLNode *DoubleRotateToRight(AVLNode *root)
{
  /* Rotate between K1 and K2 */
  root->Left = SingleRotateToLeft(root->Left);

  /* Rotate between K3 and K2 */
  return SingleRotateToRight(root);
}

AVLNode *DoubleRotateToLeft(AVLNode *root)
{
  /* Rotate between K3 and K2 */
  root->Right = SingleRotateToRight(root->Right);

  /* Rotate between K1 and K2 */
  return SingleRotateToLeft(root);
}

AVLNode *Insert(char *string, AVLNode *root)
{
  if (root == NULL)
  {
    root = (AVLNode *)malloc(sizeof(AVLNode));
    if (root == NULL)
      printf("Out of space!\n");
    else
    {
      fixString(string);
      strcpy(root->string, string);
      root->Height = 0;
      root->frequency = 1;
      root->Left = root->Right = NULL;
    }
  }
  else if (strcmp(string, root->string) == -1)
  {
    root->Left = Insert(string, root->Left);
    if (Height(root->Left) - Height(root->Right) == 2)
      if (strcmp(string, root->Left->string) == -1)
        root = SingleRotateToRight(root);
      else
        root = DoubleRotateToRight(root);
  }
  else if (strcmp(string, root->string) == 1)
  {
    root->Right = Insert(string, root->Right);
    if (Height(root->Right) - Height(root->Left) == 2)
      if (strcmp(string, root->Right->string) == 1)
        root = SingleRotateToLeft(root);
      else
        root = DoubleRotateToLeft(root);
  }
  else
  {
    root->frequency++;
    return root;
  }
  root->Height = Max(Height(root->Left), Height(root->Right)) + 1;
  return root;
}

AVLNode *Delete(char *string, AVLNode *root)
{
  if (root == NULL)
    return NULL;

  if (strcmp(string, root->string) == -1)
  {
    root->Left = Delete(string, root->Left);
    if (Height(root->Right) - Height(root->Left) == 2)
    {
      if (Height(root->Right->Left) > Height(root->Right->Right))
        root = DoubleRotateToLeft(root);
      else
        root = SingleRotateToLeft(root);
    }
  }
  else if (strcmp(string, root->string) == 1)
  {
    root->Right = Delete(string, root->Right);
    if (Height(root->Left) - Height(root->Right) == 2)
    {
      if (Height(root->Left->Right) > Height(root->Left->Left))
        root = DoubleRotateToRight(root);
      else
        root = SingleRotateToRight(root);
    }
  }
  else
  {
    if (root->frequency > 1)
    {
      root->frequency--;
      return root;
    }

    if (root->Left && root->Right)
    {
      if (Height(root->Left) > Height(root->Right))
      {
        AVLNode *maxNode = FindMax(root->Left);
        strcpy(root->string, maxNode->string);
        root->Left = Delete(root->string, root->Left);
      }
      else
      {
        AVLNode *minNode = FindMin(root->Right);
        strcpy(root->string, minNode->string);
        root->Right = Delete(root->string, root->Right);
      }
    }
    else
    {
      AVLNode *temp = root;
      if (root->Left == NULL)
        root = root->Right;
      else if (root->Right == NULL)
        root = root->Left;
      free(temp);
    }
  }

  if (root == NULL)
    return root;

  root->Height = Max(Height(root->Left), Height(root->Right)) + 1;
  return root;
}

void PrintInOrder(AVLNode *root)
{
  if (root != NULL)
  {
    PrintInOrder(root->Left);
    printf("%s\t frequency: %d\n", root->string, root->frequency);
    PrintInOrder(root->Right);
  }
}

void InsertFromAVLToHash(AVLNode *root, HashNode *Array[])
{
  if (root != NULL)
  {
    InsertFromAVLToHash(root->Left, Array);
    InsertToHashTable(root->string, Array, HASH_SIZE, root->frequency);
    InsertFromAVLToHash(root->Right, Array);
  }
}

int FirstHashFunction(int number, int size)
{
  return number % size;
}

int SecondHashFunction(int number, int size)
{
  return size - (number % size);
}

void InsertToHashTable(char *string, HashNode *Array[], int size, int frequency)
{
  int length = toAscii(string);
  int i = 0;
  int index = (FirstHashFunction(length, size) + i * SecondHashFunction(length, size)) % size;

  while (index < size && Array[index] != NULL)
  {
    if (strcmp(string, Array[index]->string) == 0)
    {
      Array[index]->frequency += frequency;
      return;
    }

    else
    {
      i++;
      index = (FirstHashFunction(length, size) + i * SecondHashFunction(length, size)) % size;
    }
  }
  HashNode *newNode = (HashNode *)malloc(sizeof(HashNode));
  strcpy(newNode->string, string);
  newNode->frequency = frequency;
  Array[index] = newNode;
  if (REHASHFLAG == 0)
    Counter++;

  if (Counter > HASH_SIZE * 0.66 && REHASHFLAG == 0)
  {
    printf("REHASHING ....\n");
    REHASHFLAG = 1;
    ReHash(Array, ReHashTable);
  }
}

void DeleteFromHashTable(char *string, HashNode *Array[], int size)
{
  int index = search(string, Array, size);
  if (index == -1)
  {
    printf("The word doesn't exist\n");
    return;
  }

  if (Array[index]->frequency > 1)
  {
    Array[index]->frequency--;
  }
  else
  {
    free(Array[index]);
    Array[index] = NULL;

    if (REHASHFLAG == 0)
    {
      HashNode *TempArray[HASH_SIZE];
      for (int i = 0; i < size; i++)
      {
        TempArray[i] = Array[i];
        Array[i] = NULL;
      }

      for (int i = 0; i < size; i++)
      {
        if (TempArray[i] != NULL)
        {
          InsertToHashTable(TempArray[i]->string, Array, size, TempArray[i]->frequency);
          free(TempArray[i]);
        }
      }
    }
    else
    {
      HashNode *TempArray[REHASH_SIZE];
      for (int i = 0; i < size; i++)
      {
        TempArray[i] = Array[i];
        Array[i] = NULL;
      }

      for (int i = 0; i < size; i++)
      {
        if (TempArray[i] != NULL)
        {
          InsertToHashTable(TempArray[i]->string, Array, size, TempArray[i]->frequency);
          free(TempArray[i]);
        }
      }
    }
  }
}

int search(char *string, HashNode *Array[], int HashSize)
{
  int i = 0;
  int size = toAscii(string);
  int index = (FirstHashFunction(size, HashSize) + i * SecondHashFunction(size, HashSize)) % HashSize;
  int firstIndex = index;

  while (index < HashSize && Array[index] != NULL)
  {
    if (strcmp(string, Array[index]->string) == 0)
      return index;

    else
    {
      i++;
      index = (FirstHashFunction(size, HashSize) + i * SecondHashFunction(size, HashSize)) % HashSize;
      if (firstIndex == index)
        break;
    }
  }

  // if not found
  return -1;
}

void PrintHashData(HashNode *Array[], int size)
{
  int counter = 0;
  int maxFrequencyIndex = 0;
  int maxFrequency = 0;
  int freq, higherfreqCounter = 0;
  printf("please enter the frequency number to print the number of words that have more than this number: ");
  scanf("%d", &freq);

  for (int i = 0; i < size; i++)
    if (Array[i] != NULL)
    {
      if (Array[i]->frequency > freq)
        higherfreqCounter++;

      if (Array[i]->frequency > maxFrequency)
      {
        maxFrequency = Array[i]->frequency;
        maxFrequencyIndex = i;
      }
      counter++;
      // printf("string: %s\t frequency: %d\n", Array[i]->string, Array[i]->frequency);
    }
  printf("The Total Number of Uniqe words is: %d\n", counter);
  if (Array[maxFrequencyIndex]->frequency > 1)
    printf("The Maximum Frequency word is : %s with Frequency of: %d\n", Array[maxFrequencyIndex]->string, Array[maxFrequencyIndex]->frequency);
  else
    printf("All words have the same frequency\n");

  printf("The number of words has a frequency more than %d is: %d\n", freq, higherfreqCounter);
}

void ReHash(HashNode *OldArray[], HashNode *NewArray[])
{
  for (int i = 0; i < HASH_SIZE; i++)
  {
    if (OldArray[i] != NULL)
    {
      InsertToHashTable(OldArray[i]->string, NewArray, REHASH_SIZE, OldArray[i]->frequency);
      free(OldArray[i]);
      OldArray[i] = NULL;
    }
  }
}