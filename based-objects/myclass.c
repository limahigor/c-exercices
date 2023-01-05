#include <stdlib.h>
#include <stdio.h>

#include "myclass.h"

struct myclass_private{
    double totalValue;
};

static void myclass_totalValue(MyClass this){
    this->private->totalValue = this->price * this->quantity;
}

static double myclass_getTotal(MyClass this){
    return this->private->totalValue;
}

static void myclass_add(MyClass this, int x){
    this->quantity += x;
    myclass_totalValue(this);
}

static void myclass_rem(MyClass this, int x){
    this->quantity -= x;
    myclass_totalValue(this);
}

char *myclass_toString(MyClass this){
    char *string = malloc(256);
    sprintf(string, "%s, $ %.2lf, %d units, Total: $ %.2lf", this->name, this->price, this->quantity, this->total(this));
    return string;
}

static void myclass_destroy(MyClass this){}


MyClass MyClass_create(MyClass this, char *name, int quantity, double price){
    this = (MyClass)malloc(sizeof(struct myclass));
    struct myclass_private *private = (struct myclass_private *)malloc(sizeof(struct myclass_private));

    this->private = private;
    this->name = name;
    this->price = price;
    this->quantity = quantity;

    this->add = myclass_add;
    this->rem = myclass_rem;
    this->total = myclass_getTotal;
    this->toString = myclass_toString;
    this->destroy = myclass_destroy;

    myclass_totalValue(this);

    return this;
}