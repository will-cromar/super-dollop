struct _MainArguments {
    char *filePath;
    int printSrcOption;
    int printCleanSrcOption;
};
typedef struct _MainArguments MainArguments;

MainArguments* parseArguments(int argc, char **argv);