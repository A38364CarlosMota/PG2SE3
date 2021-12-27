#include <stdio.h>

#include "word_sep.h"

void getLine(char buffer[], int bufferSize)
{
	if(bufferSize == 0)
		return;
		
	int i = 0;
	do
	{
		char c = getchar();

		if(c == '\n')
			break;
		
		buffer[i] = c;
		i++;
		
		if(i == bufferSize)
		{
			buffer[bufferSize-1] = 0;
			printf("Buffer full\n");
			return;
		}
		
		
	}while(1);
	
	buffer[i] = '\0';
}

char *lineSplitFirst(char line[]){

  if (strlen(line)==0) return NULL;

  char delimeters[] = {' ', '\t', '\n', '.', ',',':', ';', '!', '?', '"'};

  return strtok(line, delimeters);
}

char *lineSplitNext(){

  char delimeters[] = {' ', '\t', '\n', '.', ',',':',';', '!', '?', '"'};

  return strtok(NULL,delimeters);
}

