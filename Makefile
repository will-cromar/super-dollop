CC = gcc

TARGET = compile
CFILES = compile.c ./lexer/input_output.c ./lexer/lexer.c ./lexer/symbol_detection.c ./parser/parse.c ./parser/symbols.c

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) -std=c99 -o $(TARGET) $(CFILES)

clean:
	$(RM) $(TARGET)
