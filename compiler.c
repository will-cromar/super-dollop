//
// Created by will on 10/21/16.
//
#include <stdlib.h>
#include <string.h>

#include "lexer/lexer.h"
#include "lexer/input_output.h"
#include "compiler.h"

int main(int argc, char **argv) {

    // Parse command line arguments
    MainArguments *arguments = parseArguments(argc, argv);

    // Check to see if a file path wasn't passed via command line
    if(isEmptyPathError(arguments->filePath)){
        printEmptyPathError();
        exit(-1);
    }

    // Open the file
    FILE *f = fopen(arguments->filePath, "r");

    // Check for errors in opening the file
    if(isBadFilePointerError(f)){
        printBadFilePointerError();
        exit(-1);
    }

    // Read in the file's contents
    char *sourceCode = readFile(f);
    fclose(f);

    // Print the original contents
    if(arguments->printSrcOption)
        printSourceCode(sourceCode);

    // Preprocess sourceCode to remove comments
    char *cleanSourceCode = purgeComments(sourceCode);

    // Print the commentless sourceCode
    if(arguments->printCleanSrcOption)
        printCleanSourceCode(cleanSourceCode);

    // Break the uncommented source code into tokens
    Token *tail = tokenize(cleanSourceCode);

    // Print the tokens according to output spec
    printTokenList(tail);

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


MainArguments* parseArguments(int argc, char **argv){
    // Pull out the command line arguments
    MainArguments* arguments = calloc(1, sizeof(MainArguments));
    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "--", 2) != 0 && arguments->filePath == NULL) {
            arguments->filePath = argv[i];
        }
        else if (strcmp(argv[i], "--source") == 0)
            arguments->printSrcOption = 1;
        else if (strcmp(argv[i], "--clean") == 0)
            arguments->printCleanSrcOption = 1;
    }
    return arguments;
}
