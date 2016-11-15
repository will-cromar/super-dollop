struct _MainArguments {
    char *inputPath;
    char *outputPath;
    // This is a secret (ssh)
    char *vmOutputPath;
};
typedef struct _MainArguments MainArguments;

MainArguments* parseArguments(int argc, char **argv);
FILE* getOutputFile();