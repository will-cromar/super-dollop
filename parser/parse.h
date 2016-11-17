// Team name: Compiler Builder 7
// William Cromar
// Luke Myers
// Jonathan Guilbe

#ifndef SUPER_DOLLOP_PARSE_H
#define SUPER_DOLLOP_PARSE_H

#include "../lexer/tokens.h"
#include "../instructions.h"

#define CODE_SIZE 502
#define DEBUG_VERBOSE_ADVANCE 1

Token *iterator(Token *feed);
void startIter(Token *feed);
Token *advance();
void parseTokenChain(Token* tail);
void parseProgram();
void parseBlock();
void parseStatement();
void parseCondition();
void parseExpression();
void parseTerm();
void parseFactor();

int isRelationOperation(Token *token);

void reportParserError(const char const *error);
void emit(int op, int l, int m);
instructMem getCode();

#endif //SUPER_DOLLOP_PARSE_H
