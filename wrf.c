//gcc -Wall -o prog wrf.c word_sep.c word_norm.c data_proc.c


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "data_proc.h"
#include "word_sep.h"
#include "word_norm.h"
#include "locale.h"

#define BUFFER_SIZE (512)

int main(int argc, char** argv){
	
  setlocale(LC_ALL,"pt_PT.UTF-8");
  
  WordFreq words_array[MAX_WORDS_IN_TEXT];
  WordFreq *aux[MAX_WORDS_IN_TEXT];
  
  int counter = 0;
  FILE *fpRead=fopen(argv[1] , "r");
  FILE *fpWrite=fopen("Texto.txt" , "w");

  if(fpRead == NULL) {
    perror("Error opening ");
    return(-1);
  }
  if(fpWrite == NULL) {
    perror("Error opening ");
    fclose(fpRead);
    return(-1);
  }
  //Lê o conteúdo do ficheiro fpRead e coloca em fpWrite já tratado
  readAndWrite(fpRead,fpWrite);

  fclose(fpWrite);
  fclose(fpRead);

  FILE *fpRead_Texto=fopen("Texto.txt" , "r");

  if(fpRead_Texto == NULL) {
    perror("Error opening ");
    return(-1);
  }
  //Inicia o array de estruturas de dados 
  initStruct(words_array);
  //Prenche a estrutura de dados
  fillArrayStruct(fpRead_Texto, words_array);
  //Conta o número de estruturas do array; Retorna o contador
  counter = structCounter(words_array);
  
  for(int z = 0 ; z < counter; z++){  
	  aux[z]=&words_array[z];
  }
    
  
  
  while(1){

    displayMenu();    
	char option = getchar();
	char trash = getchar();
	char key[MAX_WORD_SIZE];
    int numberOfWordsDisp = 0;
    char buffer[BUFFER_SIZE];
    qsort(words_array, counter, sizeof(WordFreq),wordsCompare);
    
	
	switch(option){
      case 'a':
       
       displayStructArray(words_array, counter, "ARRAY ORDENADO:");
      break;

      case 'w':
        getLine(buffer,BUFFER_SIZE);
        //qsort(words_array, counter, sizeof(WordFreq),wordsCompare);
        strcpy(key,buffer);
        strcat(key, "\n");

        WordFreq* foundedKey =  findWord(key, words_array, counter);

        foundedKey != NULL ? printf("\n%sFounded! Frequency:%d\n",key ,foundedKey->freq):
        printf("NOT Founded!");
		break;

      case '+':
        //getLine(buffer,BUFFER_SIZE);
        scanf("%d", &numberOfWordsDisp) ;
        trash = getchar();
        
        strcpy(key,buffer);
        deleteWarning(trash);
        qsort(words_array, counter, sizeof(WordFreq),freqComparePlus);
        
        displayStructArray(words_array, numberOfWordsDisp, "\n--->AS PALAVRAS MAIS UTILIZADAS<--- \n");
        
		break;

      case '-':
        //getLine(buffer,BUFFER_SIZE);
        scanf("%d", &numberOfWordsDisp);
        trash = getchar();
        deleteWarning(trash);
        
        qsort(*aux, counter, sizeof(WordFreq),freqCompareMinuspointer);
        displayStructArray(*aux, numberOfWordsDisp, "\n--->AS PALAVRAS MENOS UTILIZADAS<---\n");
		break;

      case 'q':
        fclose(fpRead_Texto);
        return 0;

      default:
        printf("Not a valid Option! Try again\n");
    }
  }
  fclose(fpRead_Texto);
  return 0;
}

