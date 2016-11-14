//
// Created by will on 10/21/16.
//

#ifndef SUPER_DOLLOP_ERRORDEFS_H
#define SUPER_DOLLOP_ERRORDEFS_H

#define MISSING_PERIOD "Program must end with '.'"
//#define MISSING_CONST_IDENT "Constant declaration must begin with identifier"
#define MISSING_CONST_EQL "Constant declaration requires '=' assignment operator"
#define MISSING_CONST_NUMBER "'=' must be followed by a number"
#define MISSING_CONST_SEMICOLON "Constant declarations must be terminated by semicolon"
#define MISSING_IDENTIFIER "'const', 'var', 'procedure', 'read', and 'write' must be followed by an identifier"
//#define MISSING_IDENTIFIER_NAME "'var' declaration requires valid identifier"
#define MISSING_VAR_SEMICOLON "Identifiers in 'var' declaration must be followed by a ',' or ';'"
//#define MISSING_PROC_IDENT "Procedure must begin with identifier"
#define MISSING_PROC_DECL_SEMICOLON "Procedure decalaration must end with a semicolon (?)"
#define MISSING_PROC_END_SEMICOLON "Procedure block must be terminated with a semicolon"
#define MISSING_IDENT_BECOMES "Identifier must be followed by ':='"
#define MISSING_CALL_IDENT "'Call' keyword must be followed by identifier"
#define MISSING_BEGIN_END "Statement in 'begin' block must be followed by ';' or 'end'"
#define MISSING_THEN "'if' condition must be followed by then"
#define MISSING_DO "'while' condition must be followed by 'do'"
#define MISSING_REL_OP "Condition must contain relational operator"
#define MISSING_RPARENT "'(' must be followed by ')'"
#define MISSING_FACTOR "'*' and '/' must be followed by valid expression, number, or identifier"
#define MISSING_STATEMENT "Statement expected"

#endif //SUPER_DOLLOP_ERRORDEFS_H
