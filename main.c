#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_WORD 100
#define FILE_NAME "dict.txt"

int addWord(char *word);    // Normalize the input, Check duplicates, Add words to .txt one word per line.
int searchWord(char *word);  // Search a specific and returns the word if exist
int deleteWord(char *word);  // Checks the word from file, Delete if exist
void displayWords();          // Checks if the words exist, Display all the words if exist.

int main(){  
   // Give user a choice for CLI
   int choice;
   char word[MAX_WORD];

   while(1){
      printf("\n-- Word Dictionary ---\n");
      printf("1. Add a word \n");
      printf("2. Search a word \n");
      printf("3. Delete a word \n");
      printf("4. Display all words \n");
      printf("5. Exit \n");

      printf("Enter a choice: ");
      scanf("%d", &choice);
      getchar();

      switch(choice){
        case 1: {

            printf("Enter Word: ");
            fgets(word, MAX_WORD, stdin); // gets the word from user
            word[strcspn(word, "\n")] = 0; // Clean word
            int added = addWord(word);    // Writes to a file
            if(added){
                printf("Word added to dict \n");
            }
            else{
                printf("Error adding the word \n");
            }

            break;
        }
        case 2: {

            printf("Enter word to search: ");
            fgets(word, MAX_WORD, stdin);
            word[strcspn(word, "\n")] = 0;
            int found = searchWord(word);
            
            if(found){
                printf("Word Exist \n");
            }
            else{
                printf("Word doesn't exist \n");
            }
            break;
        }
        
        case 3: {

            printf("Write a word you want to delete: ");
            fgets(word, MAX_WORD, stdin); // gets the word from user
            word[strcspn(word, "\n")] = 0;
            int deleted = deleteWord(word);
            if(deleted){
                printf("Word deleted from file. \n");
            }
            else{
                printf("Error deleting word from file. \n");
            }
            break;
            
        }
        case 4: {
            printf("Displaying All words.. \n");
            displayWords();
            break;
        }
            
        case 5: {

            printf("Exiting the CLI..");
            exit(0);
        }
            
        default: {
            printf("Invalid case \n");
        }
      }
   }
};

// -- Implementations -----

int addWord(char *word){

}

int searchWord(char * word){

}

int deleteWord(char *word){

}

void displayWords(){
    // Open file in read mode using code
    FILE *fp = fopen(FILE_NAME, "r");  // fp pointing to the txt file
    char line[MAX_WORD];
    if (fp == NULL) {
        printf("No words found \n");
        return;
    }

    // Print all the words till end
    while(fgets(line, sizeof(line) , fp)){  // Accessing the content from the file..
        printf("%s", line);
    }

    fclose(fp);
}