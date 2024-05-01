###
### Makefile for Gerp Project
###
### Author(s):  Allison Zhang and Baydan Hussen

MAKEFLAGS += -B

CXX = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow -O2
LDFLAGS = -g3

gerp: main.o Gerp.o GerpIndexer.o DirNode.o FSTree.o
	${CXX} ${LDFLAGS} -o gerp main.o Gerp.o GerpIndexer.o DirNode.o FSTree.o

mmain.o: main.cpp Gerp.h GerpIndexer.h DirNode.o FSTree.o
	$(CXX) $(CXXFLAGS) -c main.cpp

Gerp.o: Gerp.cpp Gerp.h GerpIndexer.h DirNode.o FSTree.o
	$(CXX) $(CXXFLAGS) -c Gerp.cpp

GerpIndexer.o: GerpIndexer.cpp GerpIndexer.h DirNode.o FSTree.o
	$(CXX) $(CXXFLAGS) -c GerpIndexer.cpp

processing.o: processing.cpp processing.h
	$(CXX) $(CXXFLAGS) -c processing.cpp

unit_test: unit_test_driver.o processing.o DirNode.o FSTree.o GerpIndexer.o
	$(CXX) $(CXXFLAGS) $^

##
## Here is a special rule that removes all .o files besides the provided ones 
## (DirNode.o and FSTree.o), all temporary files (ending with ~), and 
## a.out produced by running unit_test. First, we find all .o files 
## that are not provided files, then we run rm -f on each found file 
## using the -exec find flag. Second, we delete the temporary files
## and a.out. @ is used to suppress stdout.
## 
## You do not need to modify or further comment this rule!
##
clean:
	@find . -type f \( \
		-name '*.o' ! -name 'FSTree.o' ! -name 'DirNode.o' \
		\) -exec rm -f {} \;
	@rm -f *~ a.out