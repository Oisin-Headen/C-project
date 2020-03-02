HEADERS= list.h main.h reader.h saver.h tree.h datastructure.h vector_wrapper.h stdlist_wrapper.h set_wrapper.h iter_util.h

OBJECTS = list.o tree.o main.o reader.o saver.o iter_util.o vector_wrapper.o stdlist_wrapper.o set_wrapper.o

CXX=g++
RM=rm -f

CFLAGS= -Wall -pedantic -std=c++17 -g
LFLAGS= -lboost_program_options

.PHONY: all
all: cpt_323_merge_sorter


cpt_323_merge_sorter: $(OBJECTS) 
	$(CXX) $(LFLAGS) $(OBJECTS) -o cpt_323_merge_sorter



list.o: list.cpp list.h datastructure.h
	$(CXX) $(CFLAGS) -c list.cpp
tree.o: tree.cpp tree.h datastructure.h
	$(CXX) $(CFLAGS) -c tree.cpp
vector_wrapper.o: vector_wrapper.cpp $(HEADERS)
	$(CXX) $(CFLAGS) -c vector_wrapper.cpp 
stdlist_wrapper.o: stdlist_wrapper.cpp $(HEADERS)
	$(CXX) $(CFLAGS) -c stdlist_wrapper.cpp 
set_wrapper.o: set_wrapper.cpp $(HEADERS)
	$(CXX) $(CFLAGS) -c set_wrapper.cpp 

main.o: main.cpp $(HEADERS)
	$(CXX) $(CFLAGS) -c main.cpp
reader.o: reader.cpp $(HEADERS)
	$(CXX) $(CFLAGS) -c reader.cpp
saver.o: saver.cpp $(HEADERS)
	$(CXX) $(CFLAGS) -c saver.cpp 
iter_util.o: iter_util.h iter_util.cpp
	$(CXX) $(CFLAGS) -c iter_util.cpp 



.PHONY: clean
clean:
	$(RM) *.o cpt_323_merge_sorter

.PHONY: export
export: 
	$(RM) *.o cpt_323_merge_sorter
	rsync -avzp -e ssh ../a2 s3513821@titan.csit.rmit.edu.au:c++_prog/ --exclude=".*" --exclude="*.dSYM"
