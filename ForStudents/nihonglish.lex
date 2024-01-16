%{
//	nihonglish.lex

#include	"nihonglish.h"
#include	"nihonglish.tab.h"


#undef		YY_INPUT
#define		YY_INPUT(buffer,result,maxSize)		\
		{ result = ourInput(buffer,maxSize);	}

extern
int		ourInput(char* buffer, int maxSize);

%}

%%
// YOUR CODE HERE
"i"		{ yylval.strPtr_ = new std::string("I"); return(T); }
"I"		{ yylval.strPtr_ = new std::string("I"); return(T); }
"you"		{ yylval.strPtr_ = new std::string("you"); return(T); }
"You"		{ yylval.strPtr_ = new std::string("you"); return(T); }
"?"		{ return(question_mark); }
"."		{ return(period); }

%%

#define		MIN(x,y)	(((x)<(y)) ? (x) : (y))

int		ourInput	(char*		buffer,
				 int		maxSize
				)
{
  int	n	= MIN(maxSize,textEndPtr - textPtr);

  if  (n > 0)
  {
    memcpy(buffer,textPtr,n);
    textPtr	+= n;
  }

  return(n);
}


int		yywrap		()
{
  return(1);
}
