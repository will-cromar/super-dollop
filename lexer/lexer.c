// Team name: Compiler Builder 7
// William Cromar
// Luke Myers
// Jonathan Guilbe

#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "input_output.h"
#include "symbol_detection.h"

char *purgeComments(const char const *orig) {
    size_t k = (strlen(orig) + 1);
    char *cleaned = malloc(sizeof(char) * k);
    strcpy(cleaned, orig);

    int commentFlag = 0;
    char cur = 0, prev = 0;
    for (int i = 0; i < (k - 1); i++) {
        prev = cur;
        cur = cleaned[i];

        // If this character and the last were "/*"
        if (prev == '/' && cur == '*') {
            cleaned[i - 1] = ' ';
            commentFlag = 1;
        }

        // Erase every LF/CR character by replacing it with a space
        if (commentFlag == 1 && cleaned[i] != '\n' && cleaned[i] != '\r') {
            cleaned[i] = ' ';
        }

        // Stop erasing things if we find a "*/"
        if (prev == '*' && cur == '/') {
            commentFlag = 0;
        }
    }

    return cleaned;
}

Token *tokenize(const char const *code) {
    size_t k = strlen(code);
    int i = 0; // pointer into the code buffer

    // Start and front of the linked list, respectively
    Token *tail = calloc(1, sizeof(Token));
    Token *head = tail;

    while (i < k) {
        // Move pointer past whitespace
        while (i < k && isspace(code[i]))
            i++;

        // Read in identifiers and numbers
        if (isalpha(code[i]) || isdigit(code[i])) {
            int ptr = 0;
            while (code[i] != '\0' && (isalpha(code[i]) || isdigit(code[i]))) {
                head->token[ptr++] = code[i++];

                if (ptr >= BUFFERSIZE) {
                    puts("Error: Identifier too long.");
                    break;
                }
            }
        }
        // Handle symbols
        else if (isSymbol(code[i])) {
            int twoCharOperator = 0;

            // Special case for >=, <=, and := operators
            if (i < k - 1 && (code[i] == '>' || code[i] == '<' || code[i] == ':') && code[i + 1] == '=')
                twoCharOperator = 1;
            // Special case for <> operator
            else if (i < k - 1 && code[i] == '<' && code[i + 1] == '>')
                twoCharOperator = 1;

            // Always read in the first symbol
            head->token[0] = code[i++];

            // Handle the operators that are two characters (eg ":=")
            if (twoCharOperator)
                head->token[1] = code[i++];
        }
        // Otherwise, tokenize (probably erroneous) character by itself
        else {
            head->token[0] = code[i++];
        }

        //puts(head->token);
        TokenType type = getType(head->token);
        head->type = type;

        head = addLink(head);
    }

    head->type = nulsym;
    return tail;
}

Token *addLink(Token *head) {
    Token *new = calloc(1, sizeof(Token));
    head->next = new;
    return new;
}

int isSymbol(char c) {
    switch (c) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '>':
        case '<':
        case '=':
        case ':':
        case '.':
        case ',':
        case ';':
        case '(':
        case ')':
            return 1;

        default:
            return 0;
    }
}

int isEmptyPathError(char* filePath){
    if (filePath == NULL) {
        return 1;
    }
    return 0;
}

int isBadFilePointerError(FILE* fp){
    if (fp == NULL) {
        return 1;
    }
    return 0;
}