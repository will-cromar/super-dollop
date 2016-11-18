struct _instruction {
    int op;
    int l;
    int m;
    int inputNumber;
};
typedef struct _instruction instruction;

struct _instructMem {
    instruction* mem;
    int length;
};
typedef struct _instructMem instructMem;
