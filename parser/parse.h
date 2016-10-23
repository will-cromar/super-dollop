//
// Created by will on 10/21/16.
//

#ifndef SUPER_DOLLOP_PARSE_H
#define SUPER_DOLLOP_PARSE_H

#include "../lexer/tokens.h"

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

#endif //SUPER_DOLLOP_PARSE_H
