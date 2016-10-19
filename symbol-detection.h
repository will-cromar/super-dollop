// Team name: Compiler Builder 7
// William Cromar
// Luke Myers
// Jonathan Guilbe

#ifndef LEXER_SYMBOL_DETECTION_H
#define LEXER_SYMBOL_DETECTION_H

#include "tokens.h"

int match(const char* x, char* y);
int isNullsym(char* ptr);
int isPlussym(char* ptr);
int isMinussym(char* ptr);
int isMultsym(char* ptr);
int isSlashsym(char* ptr);
int isOddsym(char* ptr);
int isEqlsym(char* ptr);
int isNeqsym(char* ptr);
int isLeqsym(char* ptr);
int isGtrsym(char* ptr);
int isGeqsym(char* ptr);
int isLparentsym(char* ptr);
int isRparentsym(char* ptr);
int isCommasym(char* ptr);
int isSemicolonsym(char* ptr);
int isPeriodsym(char* ptr);
int isBecomessym(char* ptr);
int isBeginsym(char* ptr);
int isEndsym(char* ptr);
int isIfsym(char* ptr);
int isThensym(char* ptr);
int isWhilesym(char* ptr);
int isDosym(char* ptr);
int isCallsym(char* ptr);
int isConstsym(char* ptr);
int isVarsym(char* ptr);
int isProcsym(char* ptr);
int isWritesym(char* ptr);
int isReadsym(char* ptr);
int isElsesym(char* ptr);
TokenIndex getType(char* ptr);
int numIdentifierError(char* ptr);
int isNumTooLarge(char* ptr);
int isIdentTooLong(char* ptr);
int isInvalidToken(char *ptr);

#endif //LEXER_SYMBOL_DETECTION_H
