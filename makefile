CC = g++
LFLAGS = -std=c++11
CFLAGS = -c

# EXECUTABLE_NAME is the name of the program to run.
# SOURCES includes all the .cpp files to compile.

EXECUTABLE_NAME = SimulateOS
SOURCES = main.cpp OperatingSystem.cpp MemoryManagement.cpp ShortTermScheduler.cpp Printer.cpp Disk.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXECUTABLE_NAME)

$(EXECUTABLE_NAME): $(OBJECTS)
	$(CC) -o $(EXECUTABLE_NAME) $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@

clean:
	$(RM) *.o *~ $(EXECUTABLE_NAME)