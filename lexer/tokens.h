// Team name: Compiler Builder 7
// William Cromar
// Luke Myers
// Jonathan Guilbe

#ifndef LEXER_TOKENS_H
#define LEXER_TOKENS_H

#define BUFFERSIZE 100

enum _TokenType {
    // Invalid types
    numIdent = -4, numTooLarge = -3, identTooLong = -2, invalidToken = -1,

    // Valid types
    nulsym = 1, identsym, numbersym, plussym, minussym,
    multsym, slashsym, oddsym, eqsym, neqsym, lessym, leqsym,
    gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
    periodsym, becomessym, beginsym, endsym, ifsym, thensym,
    whilesym, dosym, callsym, constsym, varsym, procsym, writesym,
    readsym , elsesym
};
typedef enum _TokenType TokenType;

struct _Token {
    char token[BUFFERSIZE];
    TokenType type;
    struct _Token *next;
};
typedef struct _Token Token;

#endif //LEXER_TOKENS_H
