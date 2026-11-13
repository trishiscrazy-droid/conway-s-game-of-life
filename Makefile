CC = g++
CFLAGS = -Wall -Wextra -O1 -Wno-missing-braces -I include/
LDFLAGS = -L lib/
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

TARGET = GameOfLife
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LDFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)