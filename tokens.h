// Team name: Compiler Builder 7
// William Cromar
// Luke Myers
// Jonathan Guilbe

#ifndef LEXER_TOKENS_H
#define LEXER_TOKENS_H

#define BUFFERSIZE 100

enum _TokenIndex {
    nulsym = 1, identsym, numbersym, plussym, minussym,
    multsym, slashsym, oddsym, eqsym, neqsym, lessym, leqsym,
    gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
    periodsym, becomessym, beginsym, endsym, ifsym, thensym,
    whilesym, dosym, callsym, constsym, varsym, procsym, writesym,
    readsym , elsesym
};
typedef enum _TokenIndex TokenIndex;

struct _Token {
    char token[BUFFERSIZE];
    struct _Token *next;
};
typedef struct _Token Token;

#endif //LEXER_TOKENS_H
