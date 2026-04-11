#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_WORD 100
#define FILE_NAME "dict.txt"

int addWord(char *word);   
int searchWord(char *word);  
int deleteWord(char *word); 
int updateWord(char *word, char *newWord);
void displayWords();          

int main(){  
   int choice;
   char word[MAX_WORD];
   FILE *fp = fopen(FILE_NAME, "a");
   fclose(fp);

   while(1){
      printf("\n-- Word Dictionary ---\n");
      printf("1. Add a word \n");
      printf("2. Search a word \n");
      printf("3. Delete a word \n");
      printf("4. Display all words \n");
      printf("5. Update a Word \n");
      printf("6. Exit \n");

      printf("Enter a choice: ");
      if(scanf("%d", &choice) != 1){
          while(getchar() != '\n');
          printf("Invalid Choice!!");
          continue;
      }
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
            fgets(word, MAX_WORD, stdin);
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
        };

        case 5: {
            printf("Enter the word you want to update: ");
            fgets(word, MAX_WORD, stdin);
            word[strcspn(word, "\n")] = 0;

            // Search for the word
            int found = searchWord(word);

            if(found){
                printf("Word found \n Enter the updated Word: ");
                char updatedWord[MAX_WORD];

                fgets(updatedWord, MAX_WORD, stdin);
                updatedWord[strcspn(updatedWord, "\n")] = 0;

                int updated = updateWord(word, updatedWord);

                if(updated){
                    printf("Word has been updated %s", updatedWord);
                }
                else{
                    printf("Error updaing the word %s", updatedWord);
                }

            }
            else{
                printf("Word not found %s", word);
            }
            break;
        }
            
        case 6: {
            printf("Exiting the CLI..");
            exit(0);
        };
      }
   }
};


int addWord(char *word){
    FILE *fp = fopen(FILE_NAME, "r");
    
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 0;
    }

    char line[MAX_WORD];
    rewind(fp);

    while(fgets(line, sizeof(line) , fp)){
        if(strstr(line, word) != NULL){
            printf("Word Already Exist in the dictionary");
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    fp = fopen(FILE_NAME, "a");
    
    fprintf(fp, "%s\n", word);
    fclose(fp);
    return 1;
}

int searchWord(char * word){
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 0;
    }

    char line[MAX_WORD];
    rewind(fp);
    while(fgets(line, sizeof(line) , fp)){
        if(strstr(line, word) != NULL){
            printf("Word Found: %s\n", word);
            fclose(fp);
            return 1;
        }
    }

    printf("Word not found.");
    fclose(fp);
    return 0;
}

int deleteWord(char *word){
    FILE *fp = fopen(FILE_NAME, "r");
    FILE *tfp = fopen("temp.txt", "w");

    if(fp == NULL){
        printf("Error opening file!\n");
        return 0;
    }
    char line[MAX_WORD];
    int found = 0;
    
    while(fgets(line, sizeof(line), fp)){      
            line[strcspn(line, "\n")] = 0; 
            if(strcmp(line, word) == 0){       // strcmp instead of strstr
                found = 1;                     // skip this line (don't copy it)
            } else {
                fprintf(tfp, "%s\n", line);    // copy everything else
            }
            
        }

    fclose(fp);
    fclose(tfp);

    if(found){
        remove(FILE_NAME);
        rename("temp.txt", FILE_NAME);
        printf("Word deleted.\n");
    } else {
        remove("temp.txt");
        printf("Word not found.\n");
    }

    return found;
    };

void displayWords(){
    FILE *fp = fopen(FILE_NAME, "r");
    char line[MAX_WORD];
    if (fp == NULL) {
        printf("No words found \n");
        return;
    }

    // Print all the words till end
    while(fgets(line, sizeof(line) , fp)){
        printf("%s", line);
    }

    fclose(fp);
}

int updateWord(char *word, char *updatedWord){
    FILE *fp = fopen(FILE_NAME, "r");
    FILE *tfp = fopen("temp.txt", "w");

    if(fp == NULL){
        printf("Error opening file!\n");
        return 0;
    }
    char line[MAX_WORD];
    int found = 0;
    
    while(fgets(line, sizeof(line), fp)){      
            line[strcspn(line, "\n")] = 0; 
            if(strcmp(line, word) == 0){       
                fprintf(tfp, "%s\n", updatedWord);
                found = 1;                     
            } else {
                fprintf(tfp, "%s\n", line);
            }
            
        }

    fclose(fp);
    fclose(tfp);

    if(found){
        remove(FILE_NAME);        
        rename("temp.txt", FILE_NAME);  
        printf("Word Updated.\n");
    } else {
        remove("temp.txt");      
        printf("Word not found.\n");
    }

    return found;
}