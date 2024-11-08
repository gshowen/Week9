#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

const int PASS_LEN = 20;        // Maximum any password will be
const int HASH_LEN = 33;        // Length of MD5 hash strings


// Given a target plaintext word, use it to try to find
// a matching hash in the hashFile.
// Get this function working first!
char * tryWord(char * plaintext, char * hashFilename)
{
    // Hash the plaintext
    char *hashVal = md5(plaintext, strlen(plaintext));

    // Open the hash file
    FILE *hashFile = fopen(hashFilename, "r");

    // Loop through the hash file, one line at a time.
    char *lineRead = malloc((HASH_LEN)*sizeof(char));

    while(!feof(hashFile)){
        if(fgets(lineRead, HASH_LEN, hashFile) != NULL){
            // Attempt to match the hash from the file to the
            // hash of the plaintext.
            
            //returns the hash value if the same
            if(strcmp(lineRead, hashVal)==0){
                return lineRead;
            }
            
        }
    }


    //close file
    fclose(hashFile);

    //freeing memory
    free(lineRead);

    //if no match was found
    return NULL;
}


int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        fprintf(stderr, "Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }

    // // These two lines exist for testing. When you have
    // // tryWord working, it should display the hash for "hello",
    // // which is 5d41402abc4b2a76b9719d911017c592.
    // // Then you can remove these two lines and complete the rest
    // // of the main function below.
    // char *found = tryWord("hello", "hashes00.txt");
    // printf("%s %s\n", found, "hello");


    // Open the dictionary file for reading.
    FILE *dictFile = fopen(argv[2], "r");
     

    // For each dictionary word, pass it to tryWord, which
    // will attempt to match it against the hashes in the hash_file.
    // If we got a match, display the hash and the word

    char *password = malloc(PASS_LEN * sizeof(char)); //password from file
    int crackedPassCount = 0; //number of cracked passwords

    //reading every password in dictionary file
    while(fgets(password, PASS_LEN, dictFile) != NULL){

        //trimming off \n
        if(password[strlen(password)-1] == '\n'){
            password[strlen(password)-1] = '\0';
        }

        //finding the hash within the hash_file or getting NULL
        char *foundHash = tryWord(password, argv[1]);

        //if there was a hash found, display it
        if(foundHash != NULL){
            printf("%s %s\n", foundHash, password);
            crackedPassCount++;
        }
    }
    
    // Close the dictionary file.
    fclose(dictFile);
    
    // Display the number of hashes that were cracked.
    printf("%d passwords cracked\n", crackedPassCount);
    
    // Free up any malloc'd memory?
    free(password);
}

