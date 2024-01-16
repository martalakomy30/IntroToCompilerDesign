/*-------------------------------------------------------------------------*
 *---									---*
 *---		Sentence.h						---*
 *---									---*
 *---	    This file declares and defines a class representing a	---*
 *---	sentence composed 1 or 2 phrase, the present-tense verb "to go"	---*
 *---	that is either in a question or declarative form.		---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a	2023 February 13	Joseph Phillips		---*
 *---									---*
 *-------------------------------------------------------------------------*/

class	Sentence
{
  //  I.  Member vars:
  //  PURPOSE:  To hold the address of the topic phrase, if one is given.
  TopicPhrase*			asForPtr_;

  //  PURPOSE:  To hold the address of the location phrase, if one is given.
  ToPhrase*			toPtr_;

  //  PURPOSE:  To hold 'true' if '*this' represents a question or 'false'
  //	if '*this' represents a declarative sentence.
  bool				isAQuestion_;

  //  II.  Disallowed auto-generated methods:
  //  No default constructor:
  Sentence			();

  //  No copy constructor:
  Sentence			(const Sentence&);

  //  No copy assignment op:
  Sentence&	operator=	(const Sentence&);

protected :
  //  III.  Protected methods:
  //  PURPOSE:  To attach phrase '*phrasePtr' to '*this' Sentence.
  //	No return value.
  void		attach		(Phrase*	phrasePtr
				)
  {
    TopicPhrase*	asForPtr;
    ToPhrase*		toPtr;

    asForPtr	= dynamic_cast<TopicPhrase*>(phrasePtr);
    toPtr	= dynamic_cast<ToPhrase*>(phrasePtr);

    if  (asForPtr != NULL)
    {
      if  (asForPtr_ != NULL)
      {
        fprintf(stderr,"Ambiguity: 2 people mentioned\n");
        exit(EXIT_FAILURE);
      }

      asForPtr_	= asForPtr;
    }
    else    
    if  (toPtr != NULL)
    {
      if  (toPtr_ != NULL)
      {
        fprintf(stderr,"Ambiguity: 2 places mentioned\n");
        exit(EXIT_FAILURE);
      }

      toPtr_	= toPtr;
    }
  }

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To initialize '*this' Sentence with the list of phrases given
  //	in 'phrasePtr' to be a question if 'isAQuestion' is 'true' or a
  //	declarative sentence otherwise.  No return value.
  Sentence			(Phrase*	phrasePtr,
				 bool		isAQuestion
				) :
				asForPtr_(NULL),
				toPtr_(NULL),
				isAQuestion_(isAQuestion)
				{
				  if  (phrasePtr != NULL)
				  {
				    attach(phrasePtr);

				    if  (phrasePtr->getNextPtr() != NULL)
				    {
				      attach(phrasePtr->getNextPtr());
				    }
				  }
				}

  //  PURPOSE:  To release the resoures of '*this'.  No parameters.
  //	No return value.
  ~Sentence			()
				{
				  delete(toPtr_);
				  delete(asForPtr_);
				}

  //  V.  Accessors:

  //  VI.  Mutators:

  //  VII.  Methods that do the main and misc work of the class:
  //  PURPOSE:  To print to 'filePtr' a string representation of '*this'
  //  	Sentence in conventional English.  No return value.
  void		fprint		(FILE*	filePtr
				)
  {
    if  (isAQuestion_)
    {
      if  ( (asForPtr_ == NULL)  ||  (asForPtr_->getStr() == "you") )
	fprintf(filePtr,"Are you going");
      else
	fprintf(filePtr,"Am I going");

      if  (toPtr_ != NULL)
      {
	fprintf(filePtr," %s?\n",toPtr_->getStr().c_str());
      }
      else
        fprintf(filePtr,"?\n");
    }
    else
    {
      if  ( (asForPtr_ == NULL)  ||  (asForPtr_->getStr() == "I") )
	fprintf(filePtr,"I am going");
      else
	fprintf(filePtr,"You are going");

      if  (toPtr_ != NULL)
      {
	fprintf(filePtr," to %s.\n",toPtr_->getStr().c_str());
      }
      else
        fprintf(filePtr,".\n");
    }
  }

};
