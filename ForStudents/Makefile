# Makefile for nihonglish
nihonglish	: nihonglish.tab.o nihonglish.o
		g++ -o $@ nihonglish.tab.o nihonglish.o	

nihonglish.o	: nihonglish.c nihonglish.tab.h nihonglish.h Phrase.h Sentence.h
		g++ -c nihonglish.c -g

nihonglish.tab.o : nihonglish.tab.c nihonglish.tab.h nihonglish.h Phrase.h Sentence.h
	  	g++ -c nihonglish.tab.c -g

nihonglish.c	: nihonglish.lex
	  	flex -o $@ nihonglish.lex

nihonglish.tab.c : nihonglish.y
		bison -d nihonglish.y --debug --verbose

nihonglish.tab.h : nihonglish.y
		bison -d nihonglish.y --debug --verbose

clean :		
		rm nihonglish *.o nihonglish.tab.h nihonglish.c nihonglish.output nihonglish.tab.c
