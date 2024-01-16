%{

#include	"nihonglish.h"

%}

%error-verbose

%union
{
  std::string*		strPtr_;
  Phrase*		nodePtr_;
}

%start			// YOUR STARTING SYMBOL HERE

%token			question_mark period
%token<strPtr_>		T
%type<nodePtr_>		PP



%%			// Rules start here:

PP	:		T as for
			{
			  $$	= new TopicPhrase($1);
			}

%%

char*		textPtr		= NULL;
char*		textEndPtr	= NULL;
Sentence*	sentencePtr	= NULL;

int		yyerror		(const char*	cPtr
				)
{
  printf("%s, sorry!\n",cPtr);
  return(EXIT_FAILURE);
}


int		main		(int		argc,
				 char*		argv[]
				)
{
  char	line[LINE_LEN];

  if  (argc >= 2)
    textPtr    = argv[1];
  else
  {
    printf("Please enter a sentence: ");
    textPtr	= fgets(line,LINE_LEN,stdin);
  }

  textEndPtr	= textPtr + strlen(textPtr);
  yyparse();

  if  (sentencePtr != NULL)
  {
    sentencePtr->fprint(stdout);
    delete(sentencePtr);
  }

  return(EXIT_SUCCESS);
}
