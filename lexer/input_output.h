// Team name: Compiler Builder 7
// William Cromar
// Luke Myers
// Jonathan Guilbe

#ifndef LEXER_INPUT_OUTPUT_H
#define LEXER_INPUT_OUTPUT_H

#include <stdio.h>
#include "tokens.h"

char *readFile(FILE *f);
void printToken(Token *link);
void printTokenList(Token *tail);
void printEmptyPathError();
void printBadFilePointerError();
void printSourceCode(char *sourceCode);
void printCleanSourceCode(char *sourceCode);
void printError(TokenType type);

#endif //LEXER_INPUT_OUTPUT_H
