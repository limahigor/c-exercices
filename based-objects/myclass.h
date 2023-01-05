#ifndef MYCLASS_H
#define MYCLASS_H

typedef struct myclass *MyClass;

struct myclass{
    char *name;
    double price;
    int quantity;
    struct myclass_private *private;

    void (*destroy)(MyClass);
    void (*add)(MyClass, int);
    void (*rem)(MyClass, int);
    char* (*toString)(MyClass);
    double (*total)(MyClass);
};

MyClass MyClass_create(MyClass this, char *name, int quantity, double price);

#endif