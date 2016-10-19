// Team name: Compiler Builder 7
// William Cromar
// Luke Myers
// Jonathan Guilbe

#ifndef CAUTIOUS_CARNIVAL_LEXER_H
#define CAUTIOUS_CARNIVAL_LEXER_H

// Max token length is 12
#include <stdio.h>
#include "tokens.h"

int isSymbol(char c);
Token *addLink(Token *head);
char *purgeComments(const char const *orig);
Token *tokenize(const char const *code);
int isEmptyPathError(char* filePath);
int isBadFilePointerError(FILE* fp);

#endif //CAUTIOUS_CARNIVAL_LEXER_H
