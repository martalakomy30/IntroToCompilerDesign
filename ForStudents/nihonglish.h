#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<string>
#include	"Phrase.h"
#include	"Sentence.h"

const int	LINE_LEN	= 256;

extern
Sentence*	sentencePtr;

extern
char*		textPtr;

extern
char*		textEndPtr;


extern
int		yylex		();

extern
int		yyerror		(const char*	cPtr);
