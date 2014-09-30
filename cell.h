#ifndef CELL_H
#define CELL_H

#include <stdio.h>
#include <stdlib.h>

#define CELL_BLOCK_SIZE 100

#include "gc.h"

typedef enum {

	C_NUMBER,
	C_SYMBOL,
	C_LIST,
	C_LAMBDA,
	C_PRIMITIVE,
	C_SPECIAL,
	C_UNDEFINED

} cell_typet;

typedef struct Cell {

	CellRecord * record;
	void * value;
	struct Cell * next;
	cell_type type;

} cell_t;

#endif
