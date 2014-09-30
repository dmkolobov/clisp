#ifndef ENV_H
#define ENV_H

#define ENV_HASH_SIZE 97

struct Env {

	struct Env * parent;
	struct Hash * symbol_table;

};

struct Env * bind_env( struct Env * parent );
struct Env * free_env( struct Env * env );
struct Cell * make_binding( struct Env * env, char * name, struct Cell * value );
struct Cell * load_binding( struct Env * env, char * name ); 
