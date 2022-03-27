#ifndef _VALUE
#define _VALUE

typedef enum
{
    INT_TYPE,
    DOUBLE_TYPE,
    STR_TYPE,
    CONS_TYPE,
    NULL_TYPE,
    PTR_TYPE,
    OPEN_TYPE,
    CLOSE_TYPE,
    BOOL_TYPE,
    SYMBOL_TYPE,
    CLOSURE_TYPE,
    PRIMITIVE_TYPE,

    // Types below are only for bonus work (feel free to comment them out)
    OPENBRACKET_TYPE,
    CLOSEBRACKET_TYPE,
    DOT_TYPE,
    SINGLEQUOTE_TYPE,
    VOID_TYPE
} valueType;

struct Value
{
    valueType type;
    union
    {
        int i;
        double d;
        char *s;
        void *p;
        struct ConsCell
        {
            struct Value *car;
            struct Value *cdr;
        } c;
        struct Closure
        {
            // List of parameter names
            struct Value *paramNames;
            // Tree for the body of the function
            struct Value *functionCode;
            // Active frame when function was defined
            struct Frame *frame;
        } cl;

        // The 'pf' variable can hold a pointer to a C function with the
        // right signature
        struct Value *(*pf)(struct Value *);
    };
};
// Where do you store a boolean in the union? It's up to you, but I recommend
// using an int (0 for false, 1 for true).

typedef struct Value Value;

// A frame contains a pointer to a parent frame and a linked list of bindings. A
// binding is a variable name (represented as a string) and a pointer to the Value
// struct it is bound to.

struct Frame
{
    struct Frame *parent;
    Value *bindings;
};

typedef struct Frame Frame;

#endif
