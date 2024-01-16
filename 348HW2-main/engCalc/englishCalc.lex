%{

/*--------------------------------------------------------------------------*
*----									----*
*----			englishCalc.lex					----*
*----									----*
*----	    This Flex program defines a program that defines an integer	----*
*----	calculator, except that the numbers 1-10 are given as their	----*
*----	names in English.						----*
*----									----*
*----	----	----	----	----	----	----	----	----	----*
*----									----*
*----	Version 1a		2023 January 23		Joseph Phillips	----*
*----									----*
*--------------------------------------------------------------------------*/

/*`
 *	Compile with:
 *	$ flex -o englishCalc.c englishCalc.lex
 *	$ gcc englishCalc.c -o englishCalc -g
 */

/*
 *	Test with:
 *	$ ./calc 
 *	one
 *	1
 *	$ ./calc 
 *	one + two
 *	3
 *	$ ./calc 
 *	one + two + three
 *	6
 *	$ ./calc 
 *	two * (three + four) * five
 *	70
 *	$ ./calc 
 *	two * (three - four) * five
 *	-10
 *	$ ./calc 
 *	eight % two
 *	0
 *	$ ./calc 
 *	eight / two
 *	4
 */

#include		<stdlib.h>
#include		<stdio.h>

extern	int		parseExpr	();

%}

%%

\n	            { return(0);}
\s              {}
zero            { return 0; }
one             { return 1; }
two             { return 2; }
three           { return 3; }
four            { return 4; }
five            { return 5; }
six             { return 6; }
seven           { return 7; }
eight           { return 8; }
nine            { return 9; }
ten             { return 10; }
\(	            { return((int)'('); }
\)	            { return((int)')'); }
\+	            { return((int)'+'); }
\-	            { return((int)'-'); }
\*	            { return((int)'*'); }
\/	            { return((int)'/'); }
\%	            { return((int)'%'); }
%%

int		currentLex	= -1;

int		peek		()
{
  if  (currentLex == -1)
  {
    currentLex	= yylex();
  }

  return(currentLex);
}


void		advance		()
{
  currentLex	= yylex();
}


int		yywrap		()
{
  return(1);
}


int		isNumber	(int	value)
{
  return( (value >= 1) && (value <= 10) );
}


int		isAdd		(int	value)
{
  return( (value == '+') || (value == '-') );
}


int		isMult		(int	value)
{
  return( (value == '*') || (value == '/') || (value == '%') );
}


void		error		(const char*	cPtr)
{
  fprintf(stderr,"Syntax error: %s\n",cPtr);
  exit(EXIT_FAILURE);
}


int		parseFactor	()
{
  int		next	= peek();
  int		returnMe;

  if  (next == '(')
  {
    advance();
    returnMe	= parseExpr();

    if  (peek() != ')')
      error("expect ')'");

    advance();
  }
  else
  if   ( isNumber(next) )
  {
    returnMe	= next;
    advance();
  }
  else
    error("Expected '(' or number");

  return(returnMe);  
}


int		parseTerm	()
{
  int		next	= peek();
  int		returnMe;

  if  ( (next == '(') || isNumber(next) )
  {
    returnMe	= parseFactor();
  }
  else
    error("Expected '(' or number");

  while  ( isMult(peek()) )
  {
    next	= peek();
    advance();

    switch  (next)
    {
    case '*' :
      returnMe	*= parseFactor();
      break;

    case '/' :
      returnMe	/= parseFactor();
      break;

    case '%' :
      returnMe	%= parseFactor();
      break;
    }
  }

  return(returnMe);
}


int		parseExpr	()
{
  int		next	= peek();
  int		returnMe;

  if  ( (next == '(') || isNumber(next) )
  {
    returnMe	= parseTerm();
  }
  else
    error("Expected '(' or number");

  while  ( isAdd(peek()) )
  {
    next	= peek();

    advance();

    switch  (next)
    {
    case '+' :
      returnMe	+= parseTerm();
      break;

    case '-' :
      returnMe	-= parseTerm();
      break;
    }
  }

  return(returnMe);
}


int		parseSent	()
{
  int		next	= peek();
  int		returnMe;

  if  ( (next == '(') || isNumber(next) )
  {
    returnMe	= parseExpr();

    if  (peek() != 0)
    {
      printf("%d\n",peek());
      error("expected end-of-input");
    }
  }
  else
    error("expected '(' or number");

  return(returnMe);
}


int		main		()
{
  printf("%d\n",parseSent());
  return(EXIT_SUCCESS);
}