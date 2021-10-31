CC = g++
CFLAGS = -Wall
OBJFILES = min_heap.o Graph.o main.o
TARGET = DSLAB_Assignment4

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
