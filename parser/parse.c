//
// Created by will on 10/21/16.
//


#include <stdio.h>
#include <stdlib.h>

#include "parse.h"
#include "errordefs.h"

#define DEBUG_VERBOSE_ADVANCE 1

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
}

void parseProgram() {
    parseBlock();

    Token *token = advance();
    if (token->type != periodsym)
        reportParserError(MISSING_PERIOD);
}

void parseBlock() {
    Token *token = NULL;

    token = advance();
    if (token->type == constsym) {
        do {
            token = advance();
            if (token->type != identsym)
                reportParserError(MISSING_CONST_IDENT);
            token = advance();
            if (token->type != eqsym)
                reportParserError(MISSING_CONST_EQL);
            token = advance();
            if (token->type != numbersym)
                reportParserError(MISSING_CONST_NUMBER);

            token = advance();
        } while (token->type == commasym);

        if (token->type != semicolonsym)
            reportParserError(MISSING_CONST_SEMICOLON);

        token = advance();
    }

    if (token->type == varsym) {
        do {
            token = advance();
            if (token->type != identsym)
                reportParserError(MISSING_IDENTIFIER_NAME);

            token = advance();
        } while (token->type == commasym);

        if (token->type != semicolonsym)
            reportParserError(MISSING_VAR_SEMICOLON);

        token = advance();
    }

    // This may not be necessary; project description ambiguous -Will
    while (token->type == procsym) {
        token = advance();
        if (token->type != identsym)
            reportParserError(MISSING_PROC_IDENT);

        token = advance();
        if (token->type != semicolonsym)
            reportParserError(MISSING_PROC_DECL_SEMICOLON);

        parseBlock();

        token = advance();
        if (token->type != semicolonsym)
            reportParserError(MISSING_PROC_END_SEMICOLON);

        token = advance();
    }

    // Pull iterator back a step for the statement parser
    startIter(token);
    parseStatement();
}

void parseStatement() {
    Token *token = NULL;
    token = advance();

    if (token->type == identsym) {
        token = advance();
        if (token->type != becomessym)
            reportParserError(MISSING_IDENT_BECOMES);

        parseExpression();
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

        parseStatement();
    }
    else if (token->type == whilesym) {
        parseCondition();

        token = advance();
        if (token->type != dosym)
            reportParserError(MISSING_DO);

        parseStatement();
    }
    else {
        startIter(token);
    }
}

void parseCondition() {
    Token *token = NULL;
    token = advance();

    if (token->type == oddsym) {
        parseExpression();
    }
    else {
        startIter(token);
        parseExpression();

        token = advance();
        if (!isRelationOperation(token))
            reportParserError(MISSING_REL_OP);

        parseExpression();
    }
}

void parseExpression() {
    Token *token = NULL;

    parseTerm();

    token = advance();
    while (token->type == plussym || token->type == minussym) {
        parseTerm();
        token = advance();
    }

    startIter(token);
}

void parseTerm() {
    Token *token = NULL;

    parseFactor();

    token = advance();
    while (token->type == multsym || token->type == slashsym) {
        parseFactor();
        token = advance();
    }

    startIter(token);
}

void parseFactor() {
    Token *token = NULL;
    token = advance();

    if (token->type == identsym || token->type == numbersym)
        return; // This is a valid terminal sym
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