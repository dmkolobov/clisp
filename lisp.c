#include "lisp.h"

cell_t * eval( cell_t * cell, struct Env * env ){

	if( cell->type == C_NUMBER || cell->type == C_UNDEFINED)
		return cell;

	else if( cell->type == C_SYMBOL )
		return load_binding( env, (char *) cell->value );

	else if( cell->type == C_LIST ){
		cell_t * operator = (cell_t *) cell->value;

		if( operator->type == C_SPECIAL )
			return eval_special( cell, env );
		else {
	
			cell_t * operands = operator->next ;

			return apply( eval( operator, env ), operands, env );

		}		
	}

}

cell_t * apply( cell_t * operator, cell_t * operands, struct Env * env ){
	
	if( operator->type == C_LAMBDA )
		return apply_lambda( (lambda_t) operator->value, operands, env );

	else if( operator->type == C_PRIMITIVE )
		return apply_primitive( (primitive_t) operator->value, operands, env );

	else
		return error( "Undefined application of non-procedure", operator );
	
}
