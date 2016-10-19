// Team name: Compiler Builder 7
// William Cromar
// Luke Myers
// Jonathan Guilbe

#ifndef LEXER_INPUT_OUTPUT_H
#define LEXER_INPUT_OUTPUT_H

#include <stdio.h>
#include "tokens.h"

struct _MainArguments {
    char *filePath;
    int printSrcOption;
    int printCleanSrcOption;
};
typedef struct _MainArguments MainArguments;

MainArguments* parseArguments(int argc, char **argv);
char *readFile(FILE *f);
void printToken(Token *link);
void printTokenList(Token *tail);
void printEmptyPathError();
void printBadFilePointerError();
void printSourceCode(char *sourceCode);
void printCleanSourceCode(char *sourceCode);
void printNumIdentError();
void printNumTooLargeError();
void printIdentTooLongError();
void printInvalidTokenError();

#endif //LEXER_INPUT_OUTPUT_H
