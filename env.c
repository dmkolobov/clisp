#include "env.h"

struct Env * bind_env( struct Env * parent ){

	struct Env * env = malloc( sizeof(struct Env) );

	env->symbol_table = alloc_hash_map( ENV_HASH_SIZE );
	env->parent = parent;

	return parent;

}

void free_env( struct Env * env ){
	
	free_hash_map( env->symbol_table, &decrement_ref_count );
	free( env );

}

cell_t * make_binding( struct Env * env, char * name, cell_t * value ){

	increment_ref_count( value );
	insert_entry( env->symbol_table, name, value );
	return value;

}

cell_t * load_binding( struct Env * env, char * name ){

	return (cell_t *) search_hash( env->symbol_table, name );

}
