//
// Created by will on 10/21/16.
//
#include <stdlib.h>
#include <string.h>

#include "lexer/lexer.h"
#include "lexer/input_output.h"
#include "parser/parse.h"
#include "compiler.h"

int main(char **argv) {

    // Parse command line arguments
    MainArguments *arguments = parseArguments(argv);

    // Check to see if a file path wasn't passed via command line
    if(isEmptyPathError(arguments->inputPath) || isEmptyPathError(arguments->outputPath)){
        printEmptyPathError();
        exit(-1);
    }

    // Open the file
    FILE *input = fopen(arguments->inputPath, "r");
    FILE *output = fopen(arguments->outputPath, "w");

    // Check for errors in opening the file
    if(isBadFilePointerError(input) || isBadFilePointerError(output)){
        printBadFilePointerError();
        exit(-1);
    }

    // Read in the file's contents
    char *sourceCode = readFile(input);
    fclose(input);

    // Preprocess sourceCode to remove comments
    char *cleanSourceCode = purgeComments(sourceCode);

    // Break the uncommented source code into tokens
    Token *tail = tokenize(cleanSourceCode);

    parseTokenChain(tail);

    Token *temp = NULL;
    // Free the token chain
    while (tail != NULL) {
        temp = tail;
        tail = tail->next;
        free(temp);
    }
    free(sourceCode);
    free(cleanSourceCode);

    return 0;
}


MainArguments* parseArguments(char **argv){
    // Pull out the command line arguments
    MainArguments* arguments = calloc(1, sizeof(MainArguments));
    arguments->inputPath = argv[0];
    arguments->outputPath = argv[1];
    return arguments;
}
