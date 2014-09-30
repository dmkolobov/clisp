#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Hash {
	
	int m;
	struct HashEntry ** table;

};

struct HashEntry {

	struct HashEntry *previous;
	struct HashEntry *next;
	void * value;
	char * key;

};

typedef void (*visiting_t)(void *);

struct Hash * alloc_hash_map( int m );
void free_hash_map( struct Hash * map, visiting_t cb );

int hash( char * key, int m );

void insert_entry( struct Hash * map, char * key, void * entry );
void * delete_entry( struct Hash * map, char * key );
void * search_hash( struct Hash *map, char * key );

#endif
