#include "data_proc.h"
#include <string.h>

void initStruct(WordFreq a[]){
  for (int i=0; i < MAX_WORDS_IN_TEXT; i++){
   a[i].freq = 0;
   strcpy(a[i].word, "");
  }
}
int structCounter(WordFreq a[]){
  int i=0;
  for (; i < MAX_WORDS_IN_TEXT; i++){
   if(a[i].freq < 1) break;
   else continue;
  }
  return i;
}

void readAndWrite(FILE* fpRead, FILE* fpWrite){
  
  char line[MAX_CHARS_LINE];

  while( fgets (line, MAX_CHARS_LINE, fpRead) != NULL ) {
    char* word = lineSplitFirst(line);
    while ( word != NULL){
      if (charLeadingOnes(*word)<=2){
        fputs(normalize(word), fpWrite);
        fputs("\n", fpWrite);
      }
      word = lineSplitNext();
    }
  }
}

void fillArrayStruct(FILE* fpRead, WordFreq a[]){

  char word_from_Texto[MAX_WORD_SIZE];

  //Coloca preenche a primeira posição da estrutura para efeitos de comparação
  strcpy(a[0].word, fgets(word_from_Texto, MAX_WORD_SIZE, fpRead));				
  a[0].freq = 1;

  while( fgets (word_from_Texto, MAX_WORD_SIZE, fpRead) != NULL ) {

    for (int i=0; i < MAX_WORDS_IN_TEXT; i++){
      if(strcmp(word_from_Texto, "\n")==0) continue;
      if(strcmp(a[i].word, word_from_Texto) == 0){
        a[i].freq++;
        break;
      }
      else if(strcmp(a[i].word, "") == 0 ){
        strcpy(a[i].word, word_from_Texto);
        a[i].freq++;
        break;
      }
    }
  }
}

WordFreq* findWord(char* key, WordFreq a[], int size ){

  static WordFreq* foundedKey;
  foundedKey = bsearch(key, a->word, size, sizeof(WordFreq), wordsCompare);

  return foundedKey;
}

int freqCompareMinuspointer(const void *a, const void *b) {
  
  WordFreq *wordA = (WordFreq*) a;
  WordFreq *wordB = (WordFreq*) b;

  return ((wordA)->freq) - ((wordB)->freq);
}

int freqComparePlus(const void *a, const void *b) {
  WordFreq *wordA = (WordFreq*) a;
  WordFreq *wordB = (WordFreq*) b;

  return (wordB->freq) - (wordA->freq);
}

int wordsCompare(const void *a, const void *b) {
  WordFreq *wordA = (WordFreq*) a;
  WordFreq *wordB = (WordFreq*) b;

  return strcoll (wordA->word,wordB->word);
}

void displayStructArray(WordFreq a[], int size, char* x){
  puts(x);
  for (int i=0; i < size ; i++){
    printf("Palavra: %s Freq:%d \n", a[i].word, a[i].freq);
  }
}

void displayMenu(){
  printf("\n\nCHOOSE AN OPTION:\n");
  printf("a : alphabetic order\n");
  printf("w <word>: word frequency\n");
  printf("+ <number> : most frequent words \n");
  printf("- <number> : least frequent words\n");
  printf("q : quit\n");
  
  printf("\n> ");
}


void deleteWarning( char warning){
}
