# Define the machine object files for your program
OBJECTS = hsi501Project4.o Queue.o Graph.o Stack.o
# Define your include file
INCLUDES = Queue.h Graph.h Stack.h

# make for the executable
p4: ${OBJECTS}
	gcc -g -o p4 ${OBJECTS}

# Simple suffix rules for the .o
%.o: %.c ${INCLUDES}
	gcc -g -c -O3 $<

# Clean the .o files
clean:
	rm -f ${OBJECTS}
