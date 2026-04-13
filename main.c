#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD 100
#define FILE_NAME "dict.txt" 

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m"

// A trie here will act as a Cache for the data I am gonna store onto my disk, so to make all the operations faster like insert, delete and search I'll use a tree data structure to store the word characters as nodes and traverse on it to avoid duplicate during searching with prefix's

typedef struct TrieNode {
    struct TrieNode* children[128];
    int isEndOfWord;
} TrieNode;

TrieNode* root;
int totalWords = 0;


TrieNode* createNode(){
    // Allocate memory of size of the node
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));

    if(!node){
        printf("Memory allocation failed!\n");
        exit(1);
    };

    for(int i = 0; i<128; i++){
        node->children[i] = NULL;
    };

    node->isEndOfWord = 0;

    return node;
};



// insert

void insert(TrieNode* root, const char* word){
    if(strlen(word) == 0) return;

    TrieNode* node = root; // Start at root

    for(int i = 0; word[i] != '\0'; i++){
        int idx = (unsigned char)word[i];

        if(node->children[idx] == NULL){
            node->children[idx] = createNode();
        }

        node = node->children[idx];
    }

    if(!node->isEndOfWord){
        node->isEndOfWord = 1;
        totalWords++;
    }
};

// Search

int searchWord(TrieNode* root, const char* word){
    if (strlen(word) == 0) return 0;

    TrieNode* node = root;

     for(int i = 0; word[i] != '\0'; i++){
        int idx = (unsigned char)word[i];

        if(node->children[idx] == NULL) return 0;
        node = node->children[idx];
    }

    return node->isEndOfWord;
}


// delete

int deleteWord(TrieNode* root, const char* word){
    if (strlen(word) == 0) return 0;

    TrieNode* node = root;

     for(int i = 0; word[i] != '\0'; i++){
        int idx = (unsigned char)word[i];

        if(node->children[idx] == NULL) return 0;
        node = node->children[idx];
     }

     if(node->isEndOfWord){
        node->isEndOfWord = 0;
        totalWords--;
        return 1;
     }

     return 0;
};


// Update Word

int updateWord(TrieNode* root, const char* word, const char* newWord){
    if (strlen(word) == 0) return 0;

    int deleted = deleteWord(root, word);

    if(!deleted) return 0;

    insert(root, newWord);

    return 1;
};


// PrintAllWords in sorted order

void printAllWords(TrieNode* node, char* prefix, int len){
    if(node->isEndOfWord){
        prefix[len] = '\0';
        printf("%s\n", prefix);
    };

    for(int i =0; i<128; i++){
        if(node->children[i] != NULL){
            prefix[len] = (char)i;
            printAllWords(node->children[i], prefix, len+1);
        }
    }

}

// Display all the words

void displayWords(){
    if(totalWords == 0) {printf("Dictionary is empty \n"); return;};

    printf("\n--- All Words (%d) ---\n", totalWords);

    char buffer[100] = {0};
    printAllWords(root, buffer ,0);
};


// Save all words to file persistently

void saveAllwordsToFile(TrieNode* node, FILE* fp, char* prefix, int len){
    if (node->isEndOfWord) {
        prefix[len] = '\0';
        fprintf(fp, "%s\n", prefix);  // Write to the file
    }
    
    for(int i =0; i<128; i++){
        if(node->children[i] != NULL){
            prefix[len] = (char)i;
            saveAllwordsToFile(node->children[i], fp, prefix, len+1);
        }
    }
};


void savetoFile(){
    FILE* fp = fopen(FILE_NAME, "w");
    if(!fp){ printf("Error saving to file!\n"); return; };

    char buffer[1024] = {0};
    saveAllwordsToFile(root, fp, buffer, 0);
    fclose(fp);
};


// Loading data from file to ram

void loadFromFile(){
     FILE* fp = fopen(FILE_NAME, "r");

     if (!fp) return;

     char line[MAX_WORD];
     while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) > 0) {
            insert(root, line);
        }
    }
}


// Prefix Search auto suggestions
void searchPrefix(TrieNode* root, const char* prefix){
    if(strlen(prefix) == 0) return;

    TrieNode* node = root;

    for(int i = 0; prefix[i] != '\0'; i++){
        int idx = (unsigned char)prefix[i];

        if(node->children[idx] == NULL) return;
        node = node->children[idx];
    }

    char buffer[100] = {0};
    for(int i = 0; prefix[i] != '\0'; i++){
        buffer[i] = prefix[i];
    };

    printAllWords(node, buffer, strlen(prefix));

};



// Free Trie

void freeTrieNode(TrieNode* node){
    if (!node) return;

    for(int i =0; i<128; i++){
        if(node->children[i] != NULL){
            freeTrieNode(node->children[i]);            
        }
    }

    free(node);
}


void clearScreen(){
    printf("\033[2J\033[H");
}

void pauseScreen(){
    printf(CYAN "\nPress Enter to go back..." RESET);
    getchar();
}

void runTests(){
    int savedTotal = totalWords;
    printf(CYAN "\n[ Running Tests ]\n\n" RESET);

    TrieNode* testRoot = createNode();
    int testWords = 0;

    char* words[100] = {
        "apple", "banana", "cherry", "date", "elderberry",
        "fig", "grape", "honeydew", "kiwi", "lemon",
        "mango", "nectarine", "orange", "papaya", "quince",
        "raspberry", "strawberry", "tangerine", "ugli", "vanilla",
        "watermelon", "xigua", "yellowfruit", "zucchini", "apricot",
        "blueberry", "cantaloupe", "dragonfruit", "guava", "jackfruit",
        "kumquat", "lime", "mulberry", "olive", "peach",
        "plum", "pomegranate", "starfruit", "tamarind", "avocado",
        "almond", "cashew", "walnut", "pistachio", "hazelnut",
        "pecan", "chestnut", "peanut", "coconut", "macadamia",
        "cat", "dog", "bird", "fish", "rabbit",
        "tiger", "lion", "bear", "wolf", "fox",
        "deer", "horse", "sheep", "goat", "cow",
        "elephant", "giraffe", "zebra", "monkey", "panda",
        "python", "cobra", "viper", "gecko", "iguana",
        "eagle", "falcon", "parrot", "penguin", "flamingo",
        "salmon", "tuna", "shark", "whale", "dolphin",
        "rose", "tulip", "daisy", "orchid", "jasmine",
        "lavender", "sunflower", "poppy", "lotus", "lily",
        "oak", "pine", "maple", "birch", "cedar"
    };

    // insert 100 words
    for(int i = 0; i < 100; i++){
        insert(testRoot, words[i]);
        testWords++;
    }
    printf(testWords == 100 ? GREEN "✓ Inserted 100 words\n" RESET : RED "✗ Insert failed — got %d\n" RESET, testWords);

    // search existing word
    printf(searchWord(testRoot, "apple") ? GREEN "✓ Search existing word (apple)\n" RESET : RED "✗ Search failed (apple)\n" RESET);

    // search another existing word
    printf(searchWord(testRoot, "cedar") ? GREEN "✓ Search existing word (cedar)\n" RESET : RED "✗ Search failed (cedar)\n" RESET);

    // search non existing word
    printf(!searchWord(testRoot, "xyz123") ? GREEN "✓ Search non-existing word (xyz123)\n" RESET : RED "✗ Search failed (xyz123)\n" RESET);

    // duplicate insert
    int before = testWords;
    insert(testRoot, "apple");
    printf(testWords == before ? GREEN "✓ Duplicate insert blocked\n" RESET : RED "✗ Duplicate insert allowed\n" RESET);

    // delete existing word
    deleteWord(testRoot, "apple");
    testWords--;
    printf(!searchWord(testRoot, "apple") ? GREEN "✓ Delete existing word (apple)\n" RESET : RED "✗ Delete failed (apple)\n" RESET);

    // delete non existing word
    printf(!deleteWord(testRoot, "xyz123") ? GREEN "✓ Delete non-existing word handled\n" RESET : RED "✗ Delete non-existing failed\n" RESET);

    // update word
    updateWord(testRoot, "banana", "blueberry2");
    testWords--;
    printf(searchWord(testRoot, "blueberry2") && !searchWord(testRoot, "banana")
        ? GREEN "✓ Update word (banana → blueberry2)\n" RESET
        : RED "✗ Update failed\n" RESET);

    // word count after all operations
    printf(testWords == 98 ? GREEN "✓ Word count correct after operations (98)\n" RESET : RED "✗ Word count wrong — got %d\n" RESET, testWords);

    printf(CYAN "\n--- Tests Done ---\n\n" RESET);
    totalWords = savedTotal;
    freeTrieNode(testRoot);
}


int main(){  
   root = createNode();
   loadFromFile();
   runTests();

   int choice;
   char word[MAX_WORD];
   char newWord[MAX_WORD];

   while(1){
      clearScreen();
      printf(CYAN "╔══════════════════════════╗\n");
      printf("║      Word Dictionary      ║\n");
      printf("╚══════════════════════════╝\n" RESET);
      printf(YELLOW "  1. Add a word\n");
      printf("  2. Search a word\n");
      printf("  3. Delete a word\n");
      printf("  4. Display all words\n");
      printf("  5. Update a word\n");
      printf("  6. Exit\n" RESET);
      printf(CYAN "\nEnter a choice: " RESET);
      
      if(scanf("%d", &choice) != 1){
          while(getchar() != '\n');
          clearScreen();
          printf(RED "Invalid choice!\n" RESET);
          pauseScreen();
          continue;
      }
      getchar();

      switch(choice){
        case 1: {
            clearScreen();
            printf(CYAN "[ Add a Word ]\n\n" RESET);
            printf(YELLOW "Enter word: " RESET);
            fgets(word, MAX_WORD, stdin);
            word[strcspn(word, "\n")] = 0;

            if(searchWord(root, word)){
                printf(RED "\n✗ Word already exists!\n" RESET);
            } else {
                insert(root, word);
                printf(GREEN "\n✓ Word added successfully!\n" RESET);
            }
            pauseScreen();
            break;
        }

        case 2: {
            clearScreen();
            printf(CYAN "[ Search a Word ]\n\n" RESET);
            printf(YELLOW "Enter word to search: " RESET);
            fgets(word, MAX_WORD, stdin);
            word[strcspn(word, "\n")] = 0;

            if(searchWord(root, word)){
                printf(GREEN "\n✓ Word exists.\n" RESET);
            } else {
                printf(RED "\n✗ Exact word not found. Showing prefix matches:\n\n" RESET);
                searchPrefix(root, word);
            }
            pauseScreen();
            break;
        }
        
        case 3: {
            clearScreen();
            printf(CYAN "[ Delete a Word ]\n\n" RESET);
            printf(YELLOW "Enter word to delete: " RESET);
            fgets(word, MAX_WORD, stdin);
            word[strcspn(word, "\n")] = 0;

            if(deleteWord(root, word)){
                printf(GREEN "\n✓ Word deleted.\n" RESET);
            } else {
                printf(RED "\n✗ Word not found.\n" RESET);
            }
            pauseScreen();
            break;
        }

        case 4: {
            clearScreen();
            printf(CYAN "[ All Words ]\n" RESET);
            displayWords();
            pauseScreen();
            break;
        }

        case 5: {
            clearScreen();
            printf(CYAN "[ Update a Word ]\n\n" RESET);
            printf(YELLOW "Enter word to update: " RESET);
            fgets(word, MAX_WORD, stdin);
            word[strcspn(word, "\n")] = 0;

            if(!searchWord(root, word)){
                printf(RED "\n✗ Word not found.\n" RESET);
                pauseScreen();
                break;
            }

            printf(YELLOW "Enter new word: " RESET);
            fgets(newWord, MAX_WORD, stdin);
            newWord[strcspn(newWord, "\n")] = 0;

            if(updateWord(root, word, newWord)){
                printf(GREEN "\n✓ Word updated to: %s\n" RESET, newWord);
            } else {
                printf(RED "\n✗ Error updating word.\n" RESET);
            }
            pauseScreen();
            break;
        }
            
        case 6: {
            clearScreen();
            savetoFile();
            freeTrieNode(root);
            printf(GREEN "✓ Dictionary saved.\n" RESET);
            printf(CYAN "Goodbye!\n\n" RESET);
            exit(0);
        }

        default: {
            clearScreen();
            printf(RED "✗ Invalid choice!\n" RESET);
            pauseScreen();
        }
      }
   }
}