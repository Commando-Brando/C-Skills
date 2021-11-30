# Define the machine object files for your program
OBJECTS = hsi501p2.o Queue.o
# Define your include file
INCLUDES = Queue.h

# make for the executable
project2: ${OBJECTS}
	gcc -g -o project2 ${OBJECTS}

# Simple suffix rules for the .o
%.o: %.c ${INCLUDES}
	gcc -g -c $<

# Clean the .o files
clean:
	rm -f ${OBJECTS}
