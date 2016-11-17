// Team name: Compiler Builder 7
// William Cromar
// Luke Myers
// Jonathan Guilbe

struct _MainArguments {
    char *inputPath;
    char *outputPath;
    // This is a secret (ssh)
    char *vmOutputPath;
};
typedef struct _MainArguments MainArguments;

MainArguments* parseArguments(int argc, char **argv);
FILE* getOutputFile();

void printFileInstruction(instruction code, FILE *output);
void printCode(instructMem memory);