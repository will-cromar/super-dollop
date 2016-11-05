//
// Created by will on 10/21/16.
//

#ifndef SUPER_DOLLOP_PARSE_H
#define SUPER_DOLLOP_PARSE_H

#include "../lexer/tokens.h"

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

#endif //SUPER_DOLLOP_PARSE_H
