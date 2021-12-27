#include <stdio.h>
#include <stdlib.h>
#include "word_norm.h"

#define MAX_WORD_SIZE (24)
#define MAX_WORDS_IN_TEXT (120000)
#define MAX_CHARS_LINE (3250)

typedef struct{ 
    char word[MAX_WORD_SIZE]; 
    int freq; 
} WordFreq;

void initStruct(WordFreq a[]);
int structCounter(WordFreq a[]);
void readAndWrite(FILE* fpRead, FILE* fpWrite);
void fillArrayStruct(FILE* fpRead, WordFreq a[]);
WordFreq* findWord(char* key, WordFreq a[], int size );
int freqCompareMinuspointer(const void *a, const void *b);
int freqComparePlus(const void *a, const void *b);
int wordsCompare(const void *a, const void *b);
void displayStructArray(WordFreq a[], int size, char* x);
void displayMenu();
void deleteWarning( char warning);
