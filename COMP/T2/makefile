all: build

flex:
	flex lex.lex

bison:
	bison -d syntax.ypp

build: flex bison	
	g++ -g -c lex.yy.c bib.hpp -lfl
	g++ -g -c syntax.tab.hpp syntax.tab.cpp bib.cpp bib.hpp -lfl
	g++ -g driver.cpp syntax.tab.o bib.o -o compilador -lfl
	make clean

clean:
	rm syntax.tab.* lex.yy.* bib.hpp.* bib.o