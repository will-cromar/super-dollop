// Team name: Compiler Builder 7
// William Cromar
// Luke Myers
// Jonathan Guilbe

#include <stdio.h>
#include <stdlib.h>
#include "parse.h"
#include "errordefs.h"
#include "../virtual_machine/opcodes.h"
#include "../parser/symbols.h"
#include <string.h>

instruction code[CODE_SIZE];
int cx;
int curStackPointer = 0;


Token *iterator(Token *feed) {
    static Token *cur = NULL;

    if (feed != NULL) {
        cur = feed;
        return NULL;
    } else {
        Token *temp = cur;
        // Advance only if this is not the terminating token
        if (cur != NULL && cur->type != nulsym) {
            // Skip erroneous tokens
            do {
                cur = cur->next;
            } while (cur->type < 0);
        }

        if (DEBUG_VERBOSE_ADVANCE) puts(temp->token);
        return temp;
    }
}

// Start the iterator at feed
void startIter(Token *feed) {
    iterator(feed);
}

// Advance the iterator
Token *advance() {
    return iterator(NULL);
}

void parseTokenChain(Token *tail) {
    // Start parsing from tail
    startIter(tail);

    parseProgram();
    emit(SIO, 0, 2); //halt instruction to end program
}

void parseProgram() {

    curStackPointer += 4; // accounts for space taken up by AR.

    parseBlock();

    Token *token = advance();
    if (token->type != periodsym)
        reportParserError(MISSING_PERIOD);
}

void parseBlock() {
    Token *token = NULL;
    char *varName = NULL;
    int numericalValue = 0;

    token = advance();
    if (token->type == constsym) {
        do {
            token = advance();
            if (token->type != identsym)
                reportParserError(MISSING_IDENTIFIER);
            varName = token->token;

            token = advance();
            if (token->type != eqsym)
                reportParserError(MISSING_CONST_EQL);
            token = advance();
            if (token->type != numbersym)
                reportParserError(MISSING_CONST_NUMBER);

            numericalValue = atoi(token->token);
            symbol *tempSym = malloc( sizeof(symbol) * 1);
            tempSym->kind = 1;
            tempSym->val = numericalValue;
            strcpy(tempSym->name, varName);
            insert(varName, tempSym);

            token = advance();
        } while (token->type == commasym);

        if (token->type != semicolonsym)
            reportParserError(MISSING_CONST_SEMICOLON);

        token = advance();
    }

    int numVars = 0;
    if (token->type == varsym) {
        do {
            token = advance();
            if (token->type != identsym)
                reportParserError(MISSING_IDENTIFIER);

            numVars++;

            symbol *tempSym = malloc( sizeof(symbol) * 1);
            tempSym->addr = curStackPointer;
            strcpy(tempSym->name, token->token);
            insert(token->token, tempSym);
            curStackPointer++;

            token = advance();
        } while (token->type == commasym);

        if (token->type != semicolonsym)
            reportParserError(MISSING_VAR_SEMICOLON);

        token = advance();

    }
    emit(INC, 0 , numVars + 4);

    // This may not be necessary; project description ambiguous -Will
    // EBNF grammar on lecture 8 slides does not include procedure -Luke
    while (token->type == procsym) {
        token = advance();
        if (token->type != identsym)
            reportParserError(MISSING_IDENTIFIER);

        token = advance();
        if (token->type != semicolonsym)
            reportParserError(MISSING_PROC_DECL_SEMICOLON);

        parseBlock();

        token = advance();
        if (token->type != semicolonsym)
            reportParserError(MISSING_PROC_END_SEMICOLON);

        token = advance();
    }

    if (token->type == periodsym)
        reportParserError(MISSING_STATEMENT);

    // Pull iterator back a step for the statement parser
    startIter(token);
    parseStatement();
}

void parseStatement() {
    Token *token = NULL;
    Token *tempTok = NULL;
    symbol *sym = NULL;
    token = advance();

    if (token->type == identsym) {
        tempTok = token;
        token = advance();
        if (token->type != becomessym)
            reportParserError(MISSING_IDENT_BECOMES);
        parseExpression();
        sym = get(tempTok->token);
        emit(STO, 0, sym->addr);
    }
    else if (token->type == callsym) {
        token = advance();
        if (token->type == identsym)
            reportParserError(MISSING_CALL_IDENT);
    }
    else if (token->type == beginsym) {
        do {
            parseStatement();
            token = advance();
        } while (token->type == semicolonsym);

        //token = advance();
        if (token->type != endsym)
            reportParserError(MISSING_BEGIN_END);
    }
    else if (token->type == ifsym) {
        parseCondition();

        token = advance();
        if (token->type != thensym)
            reportParserError(MISSING_THEN);
        int curInstructionIndex = cx;
        emit(JPC, 0, 0);
        parseStatement();
        code[curInstructionIndex].m = cx;
    }
    else if (token->type == whilesym) {
       int curInstrIndex1 = cx;

        parseCondition();

        int curInstrIndex2 = cx;
        emit(JPC, 0, 0);

        token = advance();
        if (token->type != dosym)
            reportParserError(MISSING_DO);

        parseStatement();
        emit(JMP, 0,  curInstrIndex1);
        code[curInstrIndex2].m = cx;
    }
    else if (token->type == readsym){
        emit(SIO, 0, 1);
        int offset = 0;
        token = advance();
        if (token->type == identsym){
            symbol *tempSym = get(token->token);
            if(tempSym->kind ==  1){
                emit(LIT, 0, tempSym->val);
            }
            else {
                emit(STO, 0, tempSym->addr);
            }
        }
        else{
            reportParserError(MISSING_IDENTIFIER); //Maybe make a more specific error message
        }
    }
    else if (token->type == writesym){
        int offset = 0;
        token = advance();
        if (token->type == identsym){
            symbol *tempSym = get(token->token);
            if(tempSym->kind ==  1){
                emit(LIT, 0, tempSym->val);
            }
            else {
                emit(LOD, 0, tempSym->addr);
            }
        }
        else{
            reportParserError(MISSING_IDENTIFIER); //Maybe make a more specific error message
        }
        emit(SIO, 0, 0);
    }
    else {
        startIter(token);
    }
}

void parseCondition() {
    Token *token = NULL;
    Token *tempTok = NULL;
    token = advance();

    if (token->type == oddsym) {
        parseExpression();
        emit(OPR, 0, ODD);
    }
    else {
        startIter(token);
        parseExpression();

        token = advance();
        tempTok = token;
        if (!isRelationOperation(token))
            reportParserError(MISSING_REL_OP);

        parseExpression();

        switch (tempTok->type) {
            case eqsym:
                emit(OPR, 0, EQL);
                break;
            case neqsym:
                emit(OPR, 0, NEQ);
                break;
            case lessym:
                emit(OPR, 0, LSS);
                break;
            case leqsym:
                emit(OPR, 0, LEQ);
                break;
            case gtrsym:
                emit(OPR, 0, GTR);
                break;
            case geqsym:
                emit(OPR, 0, GEQ);
                break;
            default:
                break; //this shouldn't happen unless MISSING_REL_OP is true.
        }
    }
}

void parseExpression() {
    Token *token = NULL;
    Token *tempTok = NULL;

    token = advance();
    if(token->type == minussym || token->type == plussym){
        tempTok = token;
        //token = advance();
        parseTerm();
        if(tempTok->type == minussym){
            emit(OPR, 0, NEG);
        }
    }
    else{
        startIter(token);
        parseTerm();
    }

    token = advance();
    while (token->type == plussym || token->type == minussym) {
        tempTok = token;
        parseTerm();
        token = advance();
        if(tempTok->type == plussym){
            emit(OPR, 0, ADD);
        }
        else if(tempTok->type == minussym){
            emit(OPR, 0, SUB);
        }
    }

    startIter(token);
}

void parseTerm() {
    Token *token = NULL;
    Token *tempTok = NULL;

    parseFactor();

    token = advance();
    while (token->type == multsym || token->type == slashsym) {
        tempTok = token;
        parseFactor();
        token = advance();
        if(tempTok->type == multsym){
            emit(OPR, 0, MUL);
        }
        else if(tempTok->type == slashsym){
            emit(OPR, 0, DIV);
        }
    }

    startIter(token);
}

void parseFactor() {
    Token *token = NULL;
    token = advance();
    int numberValue = 0;

    if (token->type == identsym){
        symbol *tempSym = get(token->token);
        if(tempSym->kind ==  1){
            emit(LIT, 0, tempSym->val);
        }
        else {
            emit(LOD, 0, tempSym->addr);
        }
        return; // This is a valid terminal sym
    }
    else if(token->type == numbersym){
        numberValue = atoi(token->token);
        emit(LIT, 0, numberValue);
        return; // This is a valid terminal sym
    }
    else if (token->type == lparentsym) {
        parseExpression();
        token = advance();
        if (token->type != rparentsym)
            reportParserError(MISSING_RPARENT);
    }
    else {
        reportParserError(MISSING_FACTOR);
    }
}

int isRelationOperation(Token *token) {
    switch (token->type) {
        case eqsym:
        case neqsym:
        case lessym:
        case leqsym:
        case gtrsym:
        case geqsym:
            return 1;

        default:
            return 0;
    }
}

void reportParserError(const char const *error) {
    printf("Parser error: %s\n", error);
    exit(-1);
}

void emit(int op, int l, int m){
    if(cx > CODE_SIZE){
        reportParserError("Program is larger than code buffer.\n");
    }
    else{
        code[cx].op = op;
        code[cx].l = l;
        code[cx].m = m;
        cx++;
    }
}

instructMem getCode(){
    instructMem machineCode;
    machineCode.mem = code;
    machineCode.length = cx - 1;
    return machineCode;
}