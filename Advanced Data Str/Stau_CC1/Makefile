INCLUDE_DIRS := Includes
CC 			 := g++
CFLAGS 		 := -I$(INCLUDE_DIRS)

OBJS		 := customErrorClass.o class_template.o
DEPS		 := customErrorClass.cpp $(INCLUDE_DIRS)/customErrorClass.h 
MAIN		 := class_template.cpp

.PHONY: clean all

all: Stau_CodeChallengeOne

clean:
	rm $(OBJS) Stau_CodeChallengeOne

class_template.o: $(MAIN) $(DEPS)
	$(CC) -c -o $@ $(CFLAGS) $<

customErrorClass.o: $(DEPS) 
	$(CC) -c -o $@ $(CFLAGS) $<

Stau_CodeChallengeOne: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) 