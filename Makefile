EXENAME = main
OBJS = main.o Graph.o Airports.o simpleEdge.o simpleNode.o

CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME) : output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

#object file dependncies
main.o : main.cpp Graph.cpp Graph.h 
	$(CXX) $(CXXFLAGS) main.cpp

Graph.o : Graph.cpp Graph.h
	$(CXX) $(CXXFLAGS) Graph.cpp

Airports.o : Airports.cpp Airports.h
	$(CXX) $(CXXFLAGS) Airports.cpp

simpleNode.o : simpleNode.h simpleNode.cpp
	$(CXX) $(CXXFLAGS) simpleNode.cpp

simpleEdge.o : simpleEdge.cpp simpleEdge.h
	$(CXX) $(CXXFLAGS) simpleEdge.cpp

IS_EWS=$(shell hostname | grep "ews.illinois.edu")
IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
ifneq ($(strip $(IS_EWS)),)
ifeq ($(strip $(IS_CORRECT_CLANG)),)
CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1'. $(ccend))
endif
else
CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline. $(ccend))
endif

output_msg: ; $(CLANG_VERSION_MSG)

test: output_msg cs225/catch/catchmain.cpp tests/tests.cpp Graph.cpp simpleEdge.cpp Airports.cpp simpleNode.cpp
	$(LD) cs225/catch/catchmain.cpp tests/tests.cpp Graph.cpp simpleEdge.cpp Airports.cpp simpleNode.cpp $(LDFLAGS) -o test

.PHONY: output_msg