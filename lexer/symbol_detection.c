// Team name: Compiler Builder 7
// William Cromar
// Luke Myers
// Jonathan Guilbe

#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "input_output.h"
#include "symbol_detection.h"

#define NUMBER_BASE 10
#define MAX_PL0_NUM 65535

const char *NULLSYM = "";
const char *PLUSSYM = "+";
const char *MINUSYM = "-";
const char *MULTSYM = "*";
const char *SLASHSYM = "/";
const char *ODDSYM = "odd";
const char *EQLSYM = "=";
const char *NEQSYM = "<>";
const char *LESSSYM = "<";
const char *LEQSYM = "<=";
const char *GTRSYM = ">";
const char *GEQSYM = ">=";
const char *LPARENTSYM = "(";
const char *RPARENTSYM = ")";
const char *COMMASYM = ",";
const char *SEMICOLONSYM = ";";
const char *PERIODSYM = ".";
const char *BECOMESSYM = ":=";
const char *BEGINSYM = "begin";
const char *ENDSYM = "end";
const char *IFSYM = "if";
const char *THENSYM = "then";
const char *WHILESYM = "while";
const char *DOSYM = "do";
const char *CALLSYM = "call";
const char *CONSTSYM = "const";
const char *VARSYM = "var";
const char *PROCSYM = "procedure";
const char *WRITESYM = "write";
const char *READSYM = "read";
const char *ELSESYM = "else";

int match(const char* x, char* y){
    if(strcmp(x,y) == 0){
        return 1;
    }
    return 0;
}

int isNullsym(char* ptr) {
    return match(NULLSYM, ptr);
}

int isPlussym(char* ptr) {
    return match(PLUSSYM, ptr);
}

int isMinussym(char* ptr){
    return match(MINUSYM, ptr);
}

int isMultsym(char* ptr){
    return match(MULTSYM, ptr);
}

int isSlashsym(char* ptr){
    return match(SLASHSYM, ptr);
}

int isOddsym(char* ptr){
    return match(ODDSYM, ptr);
}

int isEqlsym(char* ptr){
    return match(EQLSYM, ptr);
}

int isNeqsym(char* ptr){
    return match(NEQSYM, ptr);
}

int isLesssym(char* ptr){
    return match(LESSSYM, ptr);
}

int isLeqsym(char* ptr){
    return match(LEQSYM, ptr);
}

int isGtrsym(char* ptr){
    return match(GTRSYM, ptr);
}

int isGeqsym(char* ptr){
    return match(GEQSYM, ptr);
}

int isLparentsym(char* ptr){
    return match(LPARENTSYM, ptr);
}

int isRparentsym(char* ptr){
    return match(RPARENTSYM, ptr);
}

int isCommasym(char* ptr){
    return match(COMMASYM, ptr);
}

int isSemicolonsym(char* ptr){
    return match(SEMICOLONSYM, ptr);
}

int isPeriodsym(char* ptr){
    return match(PERIODSYM, ptr);
}

int isBecomessym(char* ptr){
    return match(BECOMESSYM, ptr);
}

int isBeginsym(char* ptr){
    return match(BEGINSYM, ptr);
}

int isEndsym(char* ptr){
    return match(ENDSYM, ptr);
}

int isIfsym(char* ptr){
    return match(IFSYM, ptr);
}

int isThensym(char* ptr){
    return match(THENSYM, ptr);
}

int isWhilesym(char* ptr){
    return match(WHILESYM, ptr);
}

int isDosym(char* ptr){
    return match(DOSYM, ptr);
}

int isCallsym(char* ptr){
    return match(CALLSYM, ptr);
}

int isConstsym(char* ptr){
    return match(CONSTSYM, ptr);
}

int isVarsym(char* ptr){
    return match(VARSYM, ptr);
}

int isProcsym(char* ptr){
    return match(PROCSYM, ptr);
}

int isWritesym(char* ptr){
    return match(WRITESYM, ptr);
}

int isReadsym(char* ptr){
    return match(READSYM, ptr);
}

int isElsesym(char* ptr){
    return match(ELSESYM, ptr);
}

TokenType getType(char* ptr){
    if(isNullsym(ptr))
        return nulsym;
    else if(isPlussym(ptr))
        return plussym;
    else if(isMinussym(ptr))
        return minussym;
    else if(isMultsym(ptr))
        return multsym;
    else if(isSlashsym(ptr))
        return slashsym;
    else if(isOddsym(ptr))
        return oddsym;
    else if(isEqlsym(ptr))
        return eqsym;
    else if(isNeqsym(ptr))
        return neqsym;
    else if(isLesssym(ptr))
        return lessym;
    else if(isLeqsym(ptr))
        return leqsym;
    else if(isGtrsym(ptr))
        return gtrsym;
    else if(isGeqsym(ptr))
        return geqsym;
    else if(isLparentsym(ptr))
        return lparentsym;
    else if(isRparentsym(ptr))
        return rparentsym;
    else if(isCommasym(ptr))
        return commasym;
    else if(isSemicolonsym(ptr))
        return semicolonsym;
    else if(isPeriodsym(ptr))
        return periodsym;
    else if(isBecomessym(ptr))
        return becomessym;
    else if(isBeginsym(ptr))
        return beginsym;
    else if(isEndsym(ptr))
        return endsym;
    else if(isIfsym(ptr))
        return ifsym;
    else if(isThensym(ptr))
        return thensym;
    else if(isWhilesym(ptr))
        return whilesym;
    else if(isDosym(ptr))
        return dosym;
    else if(isCallsym(ptr))
        return callsym;
    else if(isConstsym(ptr))
        return constsym;
    else if(isVarsym(ptr))
        return varsym;
    else if(isProcsym(ptr))
        return procsym;
    else if(isWritesym(ptr))
        return writesym;
    else if(isReadsym(ptr))
        return readsym;
    else if(isElsesym(ptr))
        return elsesym;
    else if(isalpha((int) *ptr)) {
        if(isIdentTooLong(ptr)) {
            return identTooLong;
        }
        if(isInvalidToken(ptr)) {
            return invalidToken;
        }
        return identsym;
    }
    else if(isdigit((int) *(ptr))){
        if(isInvalidToken(ptr)) {
            return invalidToken;
        }
        if(numIdentifierError(ptr)){
            return numIdent;
        }
        else {
            if(isNumTooLarge(ptr)) {
                return numTooLarge;
            }
        }
        return numbersym;
    }
    else {
        return invalidToken;
    }
}

// Handles error when an identifier starts with a number.
int numIdentifierError(char* ptr){
    int index = 0;
    while(*(ptr + index) != 0){
        if(isalpha(*(ptr + index))){
            return 1;
        }
        index++;
    }
    return 0;
}

int isNumTooLarge(char* ptr){
    char *extraChars;
    long value = strtol(ptr, &extraChars, NUMBER_BASE);
    if(value > MAX_PL0_NUM)
        return 1;

    return 0;
}

int isIdentTooLong(char* ptr){
    if(strlen(ptr) > 12){
        return 1;
    }
    return 0;
}

int isInvalidToken(char *ptr){
    int index = 0;
    while( *(ptr + index) != 0){
        if(!isalnum(*(ptr + index))){
            return 1;
        }
        index++;
    }
    return 0;
}