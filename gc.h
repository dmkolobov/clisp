#ifndef GC_H
#define GC_H

#include "cell.h"

#define CELL_BLOCK_SIZE 100

struct CellRecord {
	
	int ref_count;
	struct CellRecord * next;
	struct Cell * cell;

};

void garbage_collect();

struct Cell * alloc_cell();
void copy_cell( struct Cell * cell );

void increment_ref_count( struct Cell * cell );
void decrement_ref_count( struct Cell * cell );

#endif 
