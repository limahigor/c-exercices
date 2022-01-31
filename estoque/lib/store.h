#ifndef LIBSTORE_H
#define LIBSTORE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct product PRODUCT;
typedef struct category CATEGORY;

#pragma pack(push, 1)
typedef struct product{
	unsigned int id, qnt;
	PRODUCT *next, *left, *right;
	char *name;
	/*char *description;
	CATEGORY *categoria;*/
}PRODUCT;

typedef struct category{
	int id;
	char *name;
	char *description;
}CATEGORY;

typedef struct tree{
	PRODUCT *root, *head;
}TREE;

void *libstore_create(TREE *p);

PRODUCT *libstore_insert(TREE *n, PRODUCT *p, int id, int qnt, char *name);

#endif