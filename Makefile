CC = gcc

TARGET = compiler
CFILES = compiler.c ./lexer/input_output.c ./lexer/lexer.c ./lexer/symbol_detection.c ./parser/parse.c ./parser/symbols.c ./virtual_machine/input_output.c ./virtual_machine/instructions.c ./virtual_machine/util.c ./virtual_machine/vm.c

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) -std=c99 -o $(TARGET) $(CFILES)

clean:
	$(RM) $(TARGET)
