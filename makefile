PROJECT = B00135581

#Project 2, xml parser

SRC_FILES =   \
	String.hpp \
	Node.hpp   \
	Element.hpp \
  Text.hpp \
  Visitor.hpp \
	Parser.hpp \
  parser_test.cpp \
	Makefile   \
	README

#specify the compiler -- the -g option is to enable debugging
GXX=g++ -g -Wall

# Specifiy the target
all: parser_test

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable

parser_test: String.o Node.o Visitor.o Text.o Element.o Parser.o parser_test.o
	$(GXX)  String.o Node.o Visitor.o Text.o Element.o Parser.o parser_test.o -o parser_test

# Specify how the object files should be created from source files

String.o: String.cpp
	$(GXX)  -c  String.cpp

Node.o: Node.cpp
	$(GXX)  -c  Node.cpp

Visitor.o: Visitor.cpp
	$(GXX)  -c  Visitor.cpp

Text.o: Text.cpp
	$(GXX)  -c  Text.cpp

Element.o: Element.cpp
	$(GXX)  -c  Element.cpp

Parser.o: Parser.cpp
	$(GXX)  -c  Parser.cpp

parser_test.o: parser_test.cpp
	$(GXX)  -c  parser_test.cpp


# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o *~ core parser_test

#This target makes a archive containing all the project source files,
#suitable for submission.
submit:	$(SRC_FILES)
	tar cvfz $(PROJECT).tar.gz $(SRC_FILES)
