#include "lambda.h"

struct Env * bind_operands( lambda_t * lambda, cell_t * operands ){

	struct Env * lenv = bind_env( lambda->closure );

	cell_t * operand = operands;
	cell_t * parameter = lambda->parameters;
	
	while( operand != NULL && parameter != NULL ){
		make_binding( lenv, (char *) parameter->value, operand );
		operand = operand->next;
		parameter = paramter->next;
	}

	return lenv;

}

cell_t * apply_lambda( lambda_t * lambda, cell_t * operands, struct Env * env ){

	struct Env * lenv = bind_operands( lambda, operands );

	cell_t * s_expression = lambda->body;
	cell_t * value;

	while( body_iter != NULL ){
		garbage_collect();

		value = eval( s_expression, lenv );
		s_expression = s_expression->next;
	}

	free_env( lenv );

	return value; 

}
