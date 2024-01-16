/*--------------------------------------------------------------------------*
 *----									----*
 *----		student.cpp						----*
 *----									----*
 *----		 (1) Paragraph -> List Final (endOfInput)		----*
 *----		 (2) List -> Sent List					----*
 *----		 (3) List -> 						----*
 *----		 (4) Sent -> ReadSent .					----*
 *----		 (5) Sent -> WriteSent .				----*
 *----		 (6) ReadSent -> read the ReadMaterial			----*
 *----		 (7) ReadMaterial -> book				----*
 *----		 (8) ReadMaterial -> notes				----*
 *----		 (9) WriteSent -> write the WriteMaterial		----*
 *----		(10) WriteMaterial -> homework				----*
 *----		(11) WriteMaterial -> paper				----*
 *----		(12) Final -> take the final .				----*
 *----									----*
 *----	----	----	----	----	----	----	----	----	----*
 *----									----*
 *----	Version 1.0		2023 January 10		Joseph Phillips	----*
 *----									----*
 *--------------------------------------------------------------------------*/
#include	<stdio.h>
#include	<cstdlib>
#include	<cstdio>
#include	<iostream>
#include	<string>
#include	<list>
#include	<map>


//  PURPOSE:  To tell the length of a global string.
const int	TEXT_LEN		= 256;


//  PURPOSE:  To represent the different lexemes in the language.
typedef		enum
		{
		  END_OF_INPUT_SYM,
		  THE_KEYWORD_SYM,

		  READ_KEYWORD_SYM,
		  WRITE_KEYWORD_SYM,
		  TAKE_KEYWORD_SYM,

		  BOOK_KEYWORD_SYM,
		  NOTES_KEYWORD_SYM,
		  HOMEWORK_KEYWORD_SYM,
		  PAPER_KEYWORD_SYM,
		  FINAL_KEYWORD_SYM,

		  PERIOD_SYM,
		  NUMBER_SYM,
		  IDENTIFIER_SYM,
		  STRING_SYM,
		  BEGIN_PAREN_SYM,
		  END_PAREN_SYM,
		  COMMA_SYM
		}
		symbol_ty;

//  PURPOSE:  To represent the string delimitor character.
const char	QUOTE_CHAR		= 0x22;


//  PURPOSE:  To represent the decimal point character.
const char	DECIMAL_PT_CHAR		= '.';


/*  PURPOSE:  To implement an interface that manages the character source.
 */
class	InputCharStream
{
  //  I.  Member vars:
  //  PURPOSE:  To hold the input.
  std::string		input_;

  //  PURPOSE:  To hold where the cursor is.
  int			index_;

  //  II.  Disallowed auto-generated methods:
  
  //  III.  Protected methods:
protected :

public:
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To
  InputCharStream	(std::string&	newInput
  			) :
			input_(newInput),
			index_(0)
			{ }

  //  V.  Accessors:

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To return the current char, or '\0' if there are no more.
  //	No parameters.
  char		peek	()
  			const
			{ return
			  ( (index_ >= input_.length())
			    ? '\0' : input_[index_]
			  );
			}

  //  PURPOSE:  To return 'true' if at eof-of-input, or 'false' otherwise.
  bool		isAtEnd	()
  			const
			{ return(index_ >= input_.length()); }

  //  PURPOSE:  To advance to the next char (if not already at end).  No
  //	parameters.  No return value.
  void		advance	()
			{
			  if  (index_ < input_.length())  index_++;
			}

};


//  PURPOSE:  To represent a parsed symbol, and any associated data.
class		Symbol
{
  //  I.  Member vars:
  //  PURPOSE:  To tell the type of symbol that '*this' represents.
  symbol_ty			symbol_;

  //  PURPOSE:  To hold the address of a string associated with '*this' symbol
  //	(if there is one).
  std::string*			stringPtr_;

  //  PURPOSE:  To hold the number associated with '*this' symbol (if there
  //	is one).
  double			number_;

  //  II.  Disallowed auto-generated methods:
  //  No default constructor:
  Symbol			();

  //  No copy constructor:
  Symbol			(const Symbol&
				);

  //  No copy assignment op:
  Symbol&	operator=	(const Symbol&
				);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To initialize '*this' to hold symbol 'newSymbol'.  No return
  //	value.
  Symbol			(symbol_ty	newSymbol
				) :
				symbol_(newSymbol),
				stringPtr_(NULL),
				number_(0.0)
				{ }

  //  PURPOSE:  To initialize '*this' to hold string 'newString'.  No return
  //	value.
  Symbol			(const std::string&	newString
  				) :
				symbol_(STRING_SYM),
				stringPtr_(new std::string(newString)),
				number_(0.0)
				{ }
				
  //  PURPOSE:  To initialize '*this' to hold number 'newNumber'.  No return
  //	value.
  Symbol			(double	newNumber
				) :
				symbol_(NUMBER_SYM),
				stringPtr_(NULL),
				number_(newNumber)
				{ }

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  ~Symbol			()
				{
				  delete(stringPtr_);
				}

  //  V.  Accessors:
  //  PURPOSE:  To return the type associated with '*this' Symbol.  No
  //  	parameters.
  symbol_ty	getType		()
				const
				{ return(symbol_); }

  //  PURPOSE:  To return a reference to the string stored at '*this' Symbol,
  //	or a reference to the empty string if '*this' is not a string.
  const std::string&
		getString	()
				const
				{
				  static std::string	empty("");

				  return( (stringPtr_ == NULL)
				  	  ? empty
					  : *stringPtr_
					);
				}

  //  PURPOSE:  To return the number stored at '*this' Symbol, or '0' if
  //	'*this' does not represent a number.
  double	getNumber	()
				const
				{ return(number_); }

};


//  PURPOSE:  To hold a shared global array of characters.
char				text[TEXT_LEN];


//  PURPOSE:  To implement an interface that gathers characters into lexemes.
class	TokenStream
{
  //  I.  Member vars:
  //  PURPOSE:  To hold the source of the character input.
  InputCharStream&	inputCharStream_;

  //  PURPOSE:  To hold the lastest lexeme parsed.
  Symbol*	   	lastParsedPtr_;

  //  PURPOSE:  To hold the keyword string to symbol_ty mapping.
  std::map<std::string,symbol_ty>
			keywordToSymbolTMap_;

  //  II.  Disallowed auto-generated methods:
  //  No default constructor:
  TokenStream		();

  //  No copy constructor:
  TokenStream		(const TokenStream&
			);

  //  No copy assignment op:
  TokenStream&		operator=
			(const TokenStream&
			);

protected :
  //  III.  Protected methods:
  //  PURPOSE:  To return a pointer representing a scanned string constant.
  //	No parameters.
  Symbol*	scanString	()
				{
				  std::string	lex("");
				  bool		haveFoundEnd	= false;

				  //  Advance past first quote:
				  inputCharStream_.advance();

				  while  ( !inputCharStream_.isAtEnd() )
				  {
				    char	c = inputCharStream_.peek();

				    inputCharStream_.advance();

				    if  (c == QUOTE_CHAR)
				    {
				      haveFoundEnd	= true;
				      break;
				    }

				    lex	+= c;
				  }

				  if  (!haveFoundEnd)
				    throw "Non-terminated string constant";

				  return(new Symbol(lex));
				}

  //  PURPOSE:  To return a pointer representing a scanned number.  No
  //	parameters.
  Symbol*   	scanNumber	()
				{
				  bool		haveSeenDecimalPt	= false;
				  std::string	lex("");
				  char		c;

				  while  ( c = inputCharStream_.peek(),
				  	   isdigit(c)
				  	   || ( (c == DECIMAL_PT_CHAR)
						&&
						!haveSeenDecimalPt
					      )
				  	 )
				  {
				    lex		       += c;
				    haveSeenDecimalPt	= (c==DECIMAL_PT_CHAR);
				    inputCharStream_.advance();
				  }

				  return(new Symbol(atof(lex.c_str())));
				}


  //  PURPOSE:  To return a pointer to a Symbol instance representing an
  //	address.
  Symbol*	scanIdentifier	()
  				{
				  std::string	lex("");
				  char		c;

				  lex	+= tolower(inputCharStream_.peek());
				  inputCharStream_.advance();

				  while  (c = inputCharStream_.peek(),
				  	   isalnum(c) || (c == '_')
				  	 )
				  {
				    lex		       += tolower(c);
				    inputCharStream_.advance();
				  }

				  std::map<std::string,symbol_ty>::iterator
				    iter = keywordToSymbolTMap_.find(lex);

				  if  (iter != keywordToSymbolTMap_.end())
				    return(new Symbol(iter->second));

				  std::string	keywords;
				  bool		isFirst	= true;

				  return(new Symbol(IDENTIFIER_SYM));
/*
				  for  (iter  = keywordToSymbolTMap_.begin();
				        iter != keywordToSymbolTMap_.end();
					iter++
				       )
				  {
				    if  (isFirst)
				      isFirst	 = false;
				    else
				      keywords	+= ", ";

				    keywords += iter->first;
				  }

				  snprintf
					(text,TEXT_LEN,
					 "Expected one of %s, not %s",
					 keywords.c_str(),lex.c_str()
					);
				  throw text;
 */
				}

  //  PURPOSE:  To return a pointer representing a scanned Symbol, or to return
  //	'new Symbol(END_OF_INPUT_SYM)' if the '*this' is at the end-of-input.
  //	No parameters.
  Symbol*	scanner		()
  				{
				  while  ( isspace(inputCharStream_.peek()) )
				    inputCharStream_.advance();

				  if  ( inputCharStream_.isAtEnd() )
				    return( new Symbol(END_OF_INPUT_SYM) );

				  if  ( inputCharStream_.peek() == QUOTE_CHAR )
				    return( scanString() );

				  if  ( isdigit(inputCharStream_.peek()) )
				    return( scanNumber() );

				  if  ( isalpha(inputCharStream_.peek())
				        || (inputCharStream_.peek() == '_')
				      )
				    return( scanIdentifier() );

				  char	  ch	    = inputCharStream_.peek();
				  Symbol* symbolPtr = NULL;

				  inputCharStream_.advance();

				  switch  (ch)
				  {
				  case '(' :
				    symbolPtr	= new Symbol(BEGIN_PAREN_SYM);
				    break;

				  case ')' :
				    symbolPtr	= new Symbol(END_PAREN_SYM);
				    break;

				  case ',' :
				    symbolPtr	= new Symbol(COMMA_SYM);
				    break;

				  case '.' :
				    symbolPtr	= new Symbol(PERIOD_SYM);
				    break;

				  default :
				    throw "Unexpected character in input";
				  }

				  return(symbolPtr);
				}

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To initialize '*this' to tokenize given characters read from
  //  	'newInputCharStream'.  No parameters.
  TokenStream			(InputCharStream&	newInputCharStream
				) :
				inputCharStream_(newInputCharStream),
				lastParsedPtr_(NULL)
				{
				  keywordToSymbolTMap_["the"]
					= THE_KEYWORD_SYM;
				  keywordToSymbolTMap_["read"]
					= READ_KEYWORD_SYM;
				  keywordToSymbolTMap_["write"]
					= WRITE_KEYWORD_SYM;
				  keywordToSymbolTMap_["take"]
					= TAKE_KEYWORD_SYM;
				  keywordToSymbolTMap_["book"]
					= BOOK_KEYWORD_SYM;
				  keywordToSymbolTMap_["notes"]
					= NOTES_KEYWORD_SYM;
				  keywordToSymbolTMap_["homework"]
					= HOMEWORK_KEYWORD_SYM;
				  keywordToSymbolTMap_["paper"]
					= PAPER_KEYWORD_SYM;
				  keywordToSymbolTMap_["final"]
					= FINAL_KEYWORD_SYM;
				  advance();
				}

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  ~TokenStream			()
				{ }

  //  V.  Accessors:

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To return the 'symbol_ty' of the 'Symbol' instance that is next
  //	in the symbol stream.  No parameters.
  symbol_ty   	peek		()
				{
				  if  (lastParsedPtr_ == NULL)
				    lastParsedPtr_	= scanner();

				  return(lastParsedPtr_->getType());
				}

  //  PURPOSE:  To return the pointer to the old Symbol at that was at the
  //	front of the symbol stream, and then to internally advance to the next
  //	Symbol instance (if not already at the end).  No parameters.
  Symbol*	advance		()
				{
				  Symbol* toReturn	= lastParsedPtr_;

				  lastParsedPtr_	= scanner();
				  return(toReturn);
				}

};

//TODO: Finish parseFinal()
//  PURPOSE:  To parse non-terminal 'Final' from 'tokenizer'.
void		parseFinal	(TokenStream&	tokenizer
				)
{
  //  I.  Application validity check:

  //  II.  Attempt to parse recipe:
  symbol_ty	peek = tokenizer.peek();

  //  YOUR CODE HERE
   if(tokenizer.peek() == TAKE_KEYWORD_SYM){tokenizer.advance();}
   if(tokenizer.peek() == THE_KEYWORD_SYM){tokenizer.advance();}
   if (tokenizer.peek() == FINAL_KEYWORD_SYM){
		tokenizer.advance();
	if (tokenizer.peek() == PERIOD_SYM){
	}else throw "expected: .";
	}//else throw "expected: final";
   //else throw "error parseFinal(): Expected 'Take the final.'.";

  //  III.  Finished:
  delete(tokenizer.advance());
  
}

//TODO: Finish parseReadMaterial()
//  PURPOSE:  To parse non-terminal 'ReadMaterial' from 'tokenizer'.
void		parseReadMaterial
				(TokenStream&	tokenizer
				){
  //  I.  Application validity check:
	delete(tokenizer.advance());
  //  II.  Attempt to parse recipe:
  symbol_ty	peek = tokenizer.peek();


  //  YOUR CODE HERE
  if(peek == BOOK_KEYWORD_SYM || peek == NOTES_KEYWORD_SYM){
  }else throw "error parseReadMaterial(): Expected keyword 'book' or 'notes'.";

  //  III.  Finished:
  delete(tokenizer.advance());
}

//TODO: Finish parseWriteMaterial()
//  PURPOSE:  To parse non-terminal 'WriteMaterial' from 'tokenizer'.
void		parseWriteMaterial
				(TokenStream&	tokenizer
				)
{
  //  I.  Application validity check:
	delete(tokenizer.advance());
  //  II.  Attempt to parse recipe:
  symbol_ty	peek = tokenizer.peek();

  //  YOUR CODE HERE
   if(peek == HOMEWORK_KEYWORD_SYM|| peek == PAPER_KEYWORD_SYM){
 
   }else throw "error parseWriteMaterial():Expected keyword 'homework' or 'paper'.";
  //  III.  Finished:
  delete(tokenizer.advance());
}

//TODO: Finish parseReadSent()
//  PURPOSE:  To parse non-terminal 'ReadSent' from 'tokenizer'.
void		parseReadSent	(TokenStream&	tokenizer
				)
{
  //  I.  Application validity check:
	delete(tokenizer.advance());
  //  II.  Attempt to parse recipe:
  symbol_ty	peek = tokenizer.peek();

  //  YOUR CODE HERE
	if(peek == THE_KEYWORD_SYM){
		parseReadMaterial(tokenizer);
	}
	else throw "error parseReadSent():Expected keyword 'the'.";
  //  III.  Finished:
	delete(tokenizer.advance());
}

//TODO: Finish parseWriteSent()
//  PURPOSE:  To parse non-terminal 'WriteSent' from 'tokenizer'.
void		parseWriteSent	(TokenStream&	tokenizer
				)
{
  //  I.  Application validity check:
	delete(tokenizer.advance());
  //  II.  Attempt to parse recipe:
  symbol_ty	peek = tokenizer.peek();

  //  YOUR CODE HERE
	if(peek == THE_KEYWORD_SYM){
		parseWriteMaterial(tokenizer);
	}
	else throw "error parseWriteSent():Expected keyword 'the'.";
  //  III.  Finished:
	delete(tokenizer.advance());
}

//TODO: Finish parseSent()
//  PURPOSE:  To parse non-terminal 'Sent' from 'tokenizer'.
void		parseSent	(TokenStream&	tokenizer
				)
{
  //  I.  Application validity check:

  //  II.  Attempt to parse recipe:
  symbol_ty	peek = tokenizer.peek();

  //  YOUR CODE HERE
  if(peek == READ_KEYWORD_SYM){
	parseReadSent(tokenizer);

  }else if(peek == WRITE_KEYWORD_SYM){
   parseWriteSent(tokenizer);

  }else if(peek == PERIOD_SYM){
	delete(tokenizer.advance());
  }
  else throw "error parseSent():Expected 'Read', 'Write', or '.'.";

  //  III.  Finished:
  
}

//TODO: Finish parseList()
//  PURPOSE:  To parse non-terminal 'List' from 'tokenizer'.
void		parseList	(TokenStream&	tokenizer
				)
{
  //  I.  Application validity check:

  //  II.  Attempt to parse recipe:
  symbol_ty	peek = tokenizer.peek();

  //  YOUR CODE HERE

  if(peek == READ_KEYWORD_SYM || peek == WRITE_KEYWORD_SYM){
	parseSent(tokenizer);
	parseList(tokenizer);
    delete(tokenizer.advance());
  }
  else if(peek == TAKE_KEYWORD_SYM){
	
  }
  else throw "error parseList():Expected 'Read', 'Write', or 'Take'.";


  //  III.  Finished:

}

//TODO: Finish parseParagraph()
//  PURPOSE:  To parse non-terminal 'Paragraph' from 'tokenizer'.
void		parseParagraph	(TokenStream&	tokenizer
				)
{
  //  I.  Application validity check:

  //  II.  Attempt to parse recipe:
  symbol_ty	peek = tokenizer.peek();

  //  YOUR CODE HERE
if(peek == READ_KEYWORD_SYM  || 
   peek == WRITE_KEYWORD_SYM || 
   peek == TAKE_KEYWORD_SYM   ){
		parseList(tokenizer);
		parseFinal(tokenizer);
		if(tokenizer.peek() == END_OF_INPUT_SYM){
			delete(tokenizer.advance());
		} else
			throw "error parseParagraph():Expected: end of input.";
}else{
	throw "error parseParagraph():Expected: \"Read\", \"Write\", or \"Take\"." ;
}


  //  III.  Finished:
    delete(tokenizer.advance());
  
}


//  PURPOSE:  To return a string with the expression to compute, either from
//	the command line or the keyboard.  'argc' tells how many arguments
//	were on the command line and 'argv[]' points to those arguments.
std::string	getInput	(int		argc,
				 char*		argv[]
				)
{
  //  I.  Application validity check:

  //  II.  Get input:
  //  II.A.  Handle command line input:
  if  (argc > 1)
    return(std::string(argv[1]));

  //  II.B.  Handle keyboard input:
  std::string	input;

  std::cout << "Expression to compute: ";
  std::getline(std::cin,input);

  //  III.  Finished:
  return(input);
}


//  PURPOSE:  To get, and attempt to compute, the expression.  The expression
//	may either come from the command line or the keyboard.  'argc' tells
//	how many arguments were on the command line and 'argv[]' points to
//	those arguments.  Returns 'EXIT_SUCCESS' if the expression was
//	successfully parsed and computed or 'EXIT_FAILURE' otherwise.
int		main		(int		argc,
				 char*		argv[]
				)
{
  std::string		input(getInput(argc,argv));
  InputCharStream	charStream(input);
  int			status	= EXIT_SUCCESS;

  try
  {
    TokenStream		tokenizer(charStream);

    parseParagraph(tokenizer);
    std::cout << "Congratulations, you pass the class!" << std::endl;
  }
  catch  (const char*  messageCPtr
	 )
  {
    std::cerr << messageCPtr << std::endl;
    std::cerr << "Sorry, you failed the course!" << std::endl;
    status	= EXIT_FAILURE;
  }

  return(status);
}