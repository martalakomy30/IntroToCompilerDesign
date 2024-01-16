/*-------------------------------------------------------------------------*
 *---									---*
 *---		Phrase.h						---*
 *---									---*
 *---	    This file declares and defines a hierarchy of classes	---*
 *---	representing phrases that are kind of equivalent to		---*
 *---	prepositional phrases.						---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a	2023 February 13	Joseph Phillips		---*
 *---									---*
 *-------------------------------------------------------------------------*/

//  PURPOSE:  To serve as the base class for all phrases.
class	Phrase
{
  //  I.  Member vars:

  //  II.  Disallowed auto-generated methods:
  //  No copy constructor:
  Phrase			(const Phrase&		source
  				);

  //  No copy assignment op:
  Phrase&	operator=	(const Phrase&		source
				);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To initialize '*this' to blank phrase.  No parameters.
  //	No return value.
  Phrase			()
  				{ }

  //  PURPOSE:  To release the resources of '*this'.  No parameters.
  //	No return value.
  virtual
  ~Phrase			()
  				{ }

  //  V.  Accessors:
  //  PURPOSE:  To return the address of the next phrase, if there is one.
  //	No parameters.
  virtual
  Phrase*	getNextPtr	()
  				const
				= 0;

  //  VI.  Mutators:
  //  PURPOSE:  To make 'nextPtr' the phrase after '*this' one.
  //	No return value.
  virtual
  void		attach		(Phrase*	nextPtr
  				)
				= 0;

};


//  PURPOSE:  To represent phrase telling where to.
class	ToPhrase : public Phrase
{
  //  I.  Member vars:
  //  PURPOSE:  To hold the location.
  std::string			str_;

  //  PURPOSE:  To hold the next phrase in the list, if there is one.
  Phrase*			nextPtr_;

  //  II.  Disallowed auto-generated methods:
  //  No default constructor:
  ToPhrase			();

  //  No copy constructor:
  ToPhrase			(const ToPhrase&	source
				);

  //  No copy assignment op:
  ToPhrase&	operator=	(const ToPhrase&	source
				);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To make a phrase the represents "to *newStrPtr".
  //	No return value.
  ToPhrase			(std::string*	newStrPtr
  				) :
				Phrase(),
				str_(*newStrPtr),
				nextPtr_(NULL)
				{
				  delete(newStrPtr);
				}

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No
  //  	return value.
  ~ToPhrase			()
  				{ }

  //  V.  Accessors:
  //  PURPOSE: To return the name of the place.  No parameters.
  const std::string&
		getStr		()
				const
				{ return(str_); }

  //  PURPOSE: To return the address of the next phrase, or 'NULL' if there is
  //	none.  No parameters.
  Phrase*	getNextPtr	()
  				const
				{ return(nextPtr_); }

  //  VI.  Mutators:
  //  PURPOSE:  To make 'nextPtr' the phrase after '*this' one.
  //	No return value.
  void		attach		(Phrase*	nextPtr
  				)
				{ nextPtr_	= nextPtr; }

};


class	TopicPhrase : public Phrase
{
  //  I.  Member vars:
  //  PURPOSE:  To hold the what or whom.
  std::string			str_;

  //  PURPOSE:  To hold the next phrase in the list, if there is one.
  Phrase*			nextPtr_;

  //  II.  Disallowed auto-generated methods:
  //  No default constructor:
  TopicPhrase			();

  //  No copy constructor:
  TopicPhrase			(const TopicPhrase&	source
				);

  //  No copy assignment op:
  TopicPhrase&	operator=	(const TopicPhrase&	source
				);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To make a phrase the represents "asFor *newStrPtr".
  //	No return value.
  TopicPhrase			(std::string*	newStrPtr
  				) :
				Phrase(),
				str_(*newStrPtr),
				nextPtr_(NULL)
				{
				  delete(newStrPtr);
				}

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No
  //  	return value.
  ~TopicPhrase			()
  				{ }

  //  V.  Accessors:
  //  PURPOSE: To return the name of what or whom.  No parameters.
  const std::string&
		getStr		()
				const
				{ return(str_); }

  //  PURPOSE: To return the address of the next phrase, or 'NULL' if there is
  //	none.  No parameters.
  Phrase*	getNextPtr	()
  				const
				{ return(nextPtr_); }

  //  VI.  Mutators:
  //  PURPOSE:  To make 'nextPtr' the phrase after '*this' one.
  //	No return value.
  void		attach		(Phrase*	nextPtr
  				)
				{
				  nextPtr_	= nextPtr;
				}

};
