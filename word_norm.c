#include "word_norm.h"


char *normalize( char *word){

  char *ptrFirst = word;
  //int endOfString= (sizeof(word)/sizeof(char)); 
  int j = 0;
  int flagSpecialChar = 0;
  int tam = strlen(word) ;	
  for(int i=0; i< tam; i++){

    if (word[i] == '-' || word[i] == '\'' ){
      if(!flagSpecialChar) {
        word[j++] = word[i];
        flagSpecialChar = 1;
      }
    }
    if( isalnum(word[i])){
      utf8SetLower(word+i);
      word[j++] = word[i];
    }
    if(word[i] == (char)FIRST_BYTE_UTF){
      utf8SetLower(word + i);
      word[j++] = word[i];
      i++;
      word[j++] = word[i];
    }
  }
  word[j] = '\0';

  return ptrFirst;
}

int utf8SetLower(char* symb){

  for (; *symb != '\0' ; symb++){
    
    if (*symb == (char)FIRST_BYTE_UTF){
      if(*(symb + 1) < (char)FIRST_LOWERCASE)
        *(symb+1) = *(symb+1) + CONVR_UPTOLOW;
    }
    if( *symb >= 'A' && *symb <= 'Z' )
      *symb = *symb + CONVR_UPTOLOW;
    
    else continue;
  }  
  
  return charLeadingOnes(*symb);
}

int charLeadingOnes (char value){

 int count = 0;  
  for (unsigned int mask = 1 << (CHAR_BIT -1); mask >= 1  ; mask >>= 1 ){
    if ((value & mask) == 0) return count;
    else if ((value & mask)) count ++;
  }
  return count;
}
