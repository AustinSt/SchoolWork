INCLUDE_DIRS := Includes
CC 			 := g++
CFLAGS 		 := -I$(INCLUDE_DIRS)


OBJS		 := customErrorClass.o Stau_ERS.o binaryFile.o

MAIN		 := Stau_ERS.cpp

.PHONY: clean all

all: Stau_EmployeeFinal

clean:
	rm $(OBJS) Stau_EmployeeFinal Sorted_smallBinaryInput.dat Sorted_mediumBinaryInput.dat Sorted_largeBinaryInput.dat

Stau_ERS.o: $(MAIN) customErrorClass.cpp binaryFile.cpp customErrorClass.h binaryFile.h
	$(CC) -c -o $@ $(CFLAGS) $<

customErrorClass.o: customErrorClass.cpp customErrorClass.h 
	$(CC) -c -o $@ $(CFLAGS) $<

binaryFile.o: binaryFile.cpp customErrorClass.h binaryFile.h
	$(CC) -c -o $@ $(CFLAGS) $<

Stau_EmployeeFinal: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) 