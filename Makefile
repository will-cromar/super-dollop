CC = gcc

TARGET = lexer
CFILES = lexer.c input-output.c symbol-detection.c

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) -std=c99 -o $(TARGET) $(CFILES)

clean:
	$(RM) $(TARGET)