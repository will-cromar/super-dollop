struct _MainArguments {
    char *inputPath;
    char *outputPath;

};
typedef struct _MainArguments MainArguments;

MainArguments* parseArguments(char **argv);