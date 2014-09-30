#include "hash.h"

void print_hash( struct Hash * map, visiting_t print_entry){
	int i;
	struct HashEntry * entry ;
	struct HashEntry * chain ;

	printf("\n-------------\n");
	for( i = 0 ; i < map->m ; i ++ ){
		entry = map->table[i];

		while( entry != NULL ){
			chain = entry->next;
			printf("%s[%d]:\t", entry->key, i );
			print_entry( entry->value );
			printf("\n");		
			entry = chain;
		}

	}
	printf("\n");
}

struct Hash * alloc_hash_map( int m ){

	int i = 0;
	struct Hash * map = malloc( sizeof(struct Hash) );

	map->m = m;
	map->table = calloc( m, sizeof(struct HashEntry *) );
	
	for( i = 0 ; i < m ; i ++ )
		map->table[i] = NULL;
	
	return map;

}

void free_hash_map( struct Hash * map, visiting_t cb ){
	int i;
	struct HashEntry * entry ;
	struct HashEntry * chain ;

	for( i = 0 ; i < map->m ; i ++ ){
		entry = map->table[i];

		while( entry != NULL ){
			
			chain = entry->next;
			cb( entry->value );
			free( entry->key );
			free( entry );
			entry = chain;

		}

	}
	free( map->table );
	free( map );
}

int hash( char * key, int m ){
	int sum = 0;
	int i = 0;

	while( *(key + i) != '\0' )
		sum += (int) *(key + i++);

	return sum % m ;
}

struct HashEntry * search_hash_entry( struct Hash * map, char * key ){

	int index = hash( key, map->m );
	struct HashEntry * entry = map->table[ index ];

	while( entry != NULL && strcmp( key, entry->key ) != 0 )
		entry = entry->next;

	return entry;
}

void insert_entry( struct Hash * map, char * key, void * value ){

	int index = hash( key, map->m );
	struct HashEntry * entry = calloc( 1, sizeof(struct HashEntry) );
	struct HashEntry * collision = map->table[ index ];

	entry->value = value;
	entry->key = calloc( strlen( key ) + 1, sizeof(char) );
	strcpy( entry->key, key );

	if( collision != NULL ){
		collision->previous = entry;
		entry->next = collision;	
	}
	
	map->table[ index ] = entry;

}

void * delete_entry( struct Hash * map, char * key ){

	int index = hash( key, map->m );
	struct HashEntry * entry = search_hash_entry( map, key );

	if( entry == NULL ) return NULL;
	else {

		struct HashEntry * previous = entry->previous;
		struct HashEntry * next = entry->next;

		if( previous == NULL )
			map->table[ index ] = next;
		else if( next == NULL )
			previous->next = NULL;
		else {
			previous->next = next;
			next->previous = previous;	
		}
	
		void * value = entry->value;
		free( entry->key );
		free( entry );
		return value;

	}
	
}

void * search_hash( struct Hash * map, char * key ){

	struct HashEntry * entry = search_hash_entry( map, key );
	if( entry == NULL )
		return NULL;
	else
		return entry->value;

}


