static cell_record_t * free_cells;
static cell_record_t * live_cells;

// allocates CELL_BLOCK_SIZE number of cells and adds them to the free list
void initialize(){
	int i = 0;

	cell_t ** cells = calloc( CELL_BLOCK_SIZE, sizeof(cell_t) );
	cell_record_t ** cell_records = calloc( CELL_BLOCK_SIZE, sizeof(cell_record_t) );

	for( i = 0; i < CELL_BLOCK_SIZE; i++ ){
		// Associate cell[i] with cell_record[i]
		cell_records[i]->cell = cells[i];
		cells[i] = cell_records[i];

		// Chain cell_records
		if( CELL_BLOCK_SIZE - i > 1 )
			cell_records[i]->next = cell_record[i+1];
	}
	
	free_cells = cell_record[0];
}

void garbage_collect(){
	cell_record_t * survivors = NULL;
	cell_record_t * iter = live_cells;

	while( iter != NULL ){
		live_cells = iter->next;	

		if( iter->ref_count == 0 ){
			// clean up any allocated value memory and zero cell memory.
			free_cell( iter->cell );
			
			// Add cell record to free cell list.
			iter->next = free_cells;
			free_cells = iter;
		} else {
			iter->next = survivors;
			survivors = iter;
		}
		iter = live_cells;
	}

	live_cells = survivors;
}

void free_cell( cell_t * cell ){

	switch( cell->type ){
		case C_NUMBER:
		case C_SYMBOL:
		case C_LAMBDA:
			free( cell->value );
			break;
	}

	memset( cell, 0, sizeof(cell_t) ); 

}

void iter_cells( cell_t * cell, void (*visit)(cell_t *)){
	if( cell == NULL )
		return;
	} else if( cell->type == C_LIST ){
		iter_cells( (cell_t *) cell->value, visit );
	} else if( cell->type == C_LAMBDA ){
		lambda_t * lambda = (lambda_t *) cell->value;
		iter_cells( lambda->parameters, visit );
		iter_cells( lambda->body, visit );
	}

	visit( cell );
	iter_cells( cell->next, visit );
}

void inc_ref_count( cell_t * cell ){
	cell->record->ref_count += 1;
}
void dec_ref_count( cell_t * cell ){
	cell->record->ref_count -= 1;
}

void increment_ref_count( cell_t * cell ){ 
	iter_cells( cell, &inc_ref_count );
}
void decrement_ref_count( cell_t * cell ){
	iter_cells( cell, &dec_ref_count );
}

cell_t * alloc_cell(){
	if( free_cells == NULL ) initialize();

	cell_tRecord * record = free_cells;

	free_cells = record->next;
	record->next = live_cells;
	live_cells = record;

	return record->cell;
}

cell_t * copy_cell( cell_t * cell ){
	cell_t * cell_copy = alloc_cell();

	if( cell->type == C_NUMBER ){

		cell_copy->value = malloc( sizeof(int) );
		cell_copy->value = *( (int *) cell->value );

	} else if( cell->type == C_SYMBOL ){

		int length = strlen( cell->value ) + 1;
		cell_copy->value = calloc( length, sizeof(char) );
		strncopy( cell_copy->value, cell->value, length );

	} else 
		cell_copy->value = cell->value;

	cell_copy->type = cell->type;
	return cell_copy;	
} 
