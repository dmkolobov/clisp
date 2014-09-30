#ifndef LAMBDA_H
#define LAMBDA_H

#include "cell.h"
#include "gc.h"
#include "env.h"

typedef struct Lambda {

	struct Cell * parameters; 
	struct Cell * body; 
	struct Env * closure;

} lambda_t;

cell_t * apply_lambda( lambda_t * lambda, cell_t * operands, struct Env * env );

#endif
