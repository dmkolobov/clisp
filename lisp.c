#include "lisp.h"

cell_t * eval( cell_t * cell, struct Env * env ){

	if( cell->type == C_NUMBER || cell->type == C_UNDEFINED)
		return cell;

	else if( cell->type == C_SYMBOL )
		return load_binding( env, (char *) cell->value );

	else if( cell->type == C_LIST ){
		cell_t * op = (cell_t *) cell->value;

		if( op->type == C_SPECIAL )
			return eval_special( cell, env );
		else 			
			return apply( eval( op, env ), eval_operands( cell->value->next, env ), env );
		
	}

}

cell_t * eval_operands( cell_t * operands, struct Env * env ){

	if( operands == NULL )
		return NULL;
	else {
		cell_t * value = copy_cell( eval( operands, env ) );
		value->next = eval_operands( operands->next, env );
		return value;
	}

}

cell_t * apply( cell_t * op, cell_t * operands, struct Env * env ){
	
	if( op->type == C_LAMBDA )
		return apply_lambda( (lambda_t) op->value, operands, env );

	else if( op->type == C_PRIMITIVE )
		return apply_primitive( (primitive_t) op->value, operands, env );

	else
		return undefined("Undefined application of non procedure.";
	
}
