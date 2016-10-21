// Team name: Compiler Builder 7
// William Cromar
// Luke Myers
// Jonathan Guilbe

#include "input-output.h"
#include "symbol-detection.h"
#include <string.h>
#include <stdlib.h>


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

char *readFile(FILE *f) {
    fseek(f, 0L, SEEK_END);
    size_t size = (size_t) ftell(f);
    rewind(f);

    char *contents = calloc((size + 1), sizeof(char));
    fread(contents, 1, size, f);

    return contents;
}

void printToken(Token *link) {
    // Skip erroneous and null tokens
    if (link->type > 1) {
        printf("%-12s %d\n", link->token, link->type);
    }
    // Print error messages
    else if (link->type < 0){
        printError(link->type);
    }
}

void printTokenList(Token *tail){
    puts("tokens:");
    puts("-------");
    Token *temp = tail;
    while (temp != NULL) {
        printToken(temp);
        temp = temp->next;
    }
}

void printEmptyPathError(){
    puts("Error: pass in file name as argument. File name cannot start with \"--\".");
    puts("Other options:");
    puts("\t--source: print the source code as it was read from the file");
    puts("\t--clean:  print the source code without comments");
}

void printBadFilePointerError(){
    puts("Error: Bad file pointer.");
}

void printSourceCode(char *sourceCode){
    puts("\nsource code:");
    puts("------------");
    puts(sourceCode);
}

void printCleanSourceCode(char *sourceCode){
    puts("source code without comments:");
    puts("-----------------------------");
    puts(sourceCode);
}

void printError(TokenType type) {
    printf("Lexer error: ");
    switch (type) {
        case numIdent:
            puts("Identifier starts with a number");
            break;

        case numTooLarge:
            puts("Number too large");
            break;

        case identTooLong:
            puts("Identifier too long");
            break;

        case invalidToken:
            puts("Invalid token");
            break;

        default:
            return;
    }
}

void printNumIdentError(){
    printf("Identifier starts with a number\n");
}

void printNumTooLargeError(){
    printf("Number too large\n");
}

void printIdentTooLongError(){
    printf("Identifier too long\n");
}

void printInvalidTokenError(){
    printf("Invalid token\n");
}