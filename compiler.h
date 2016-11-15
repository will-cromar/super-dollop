struct _MainArguments {
    char *inputPath;
    char *outputPath;

};
typedef struct _MainArguments MainArguments;

MainArguments* parseArguments(int argc, char **argv);
FILE* getOutputFile();