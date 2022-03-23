INCLUDE_DIRS := Includes
CC 			 := g++
CFLAGS 		 := -I$(INCLUDE_DIRS)


OBJS		 := customErrorClass.o Stau_CC2.o RnBTree.o

MAIN		 := Stau_CC2.cpp

.PHONY: clean all

all: Stau_CodeChallenge2

clean:
	rm $(OBJS) Stau_CodeChallenge2

Stau_CC2.o: $(MAIN) customErrorClass.cpp RnBTree.cpp customErrorClass.h RnBTree.h
	$(CC) -c -o $@ $(CFLAGS) $<

customErrorClass.o: customErrorClass.cpp customErrorClass.h 
	$(CC) -c -o $@ $(CFLAGS) $<

RnBTree.o: RnBTree.cpp customErrorClass.h RnBTree.h
	$(CC) -c -o $@ $(CFLAGS) $<

Stau_CodeChallenge2: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) 