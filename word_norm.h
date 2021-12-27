#include "word_sep.h"
#include <ctype.h>
#include <limits.h>

#define FIRST_BYTE_UTF  (0xc3)
#define FIRST_LOWERCASE (0xa0)
#define CONVR_UPTOLOW  (0x20)


char *normalize( char *word);
int utf8SetLower(char* symb);
int charLeadingOnes (char value);
