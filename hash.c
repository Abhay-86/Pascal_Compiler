#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "hash.h"
#include "gencode.h"
#include "tree.h"
#include "compiler.tab.h"
#include "externs.h"

table_t* head_table;
table_t* caller;


int hashpjw( char *s )
{
	char *p; 
	unsigned h = 0, g; 

	for ( p = s; *p != '\0'; p++ ) 
	{ 
		h = (h << 4) + (*p); 
		if ( g = h & 0xf0000000 ) 
		{ 
			h = h ^ ( g >> 24 ); 
			h = h ^ g; 
		} 
	} 
	return h % TABLE_SIZE; 
}



table_t* push_table(char* name, int class)
{
	
	table_t* ptr = (table_t*)malloc(sizeof(table_t));
	for(int i = 0; i < TABLE_SIZE; i++)
		ptr->hash_table[i] = NULL;
	ptr->table_name = strdup(name);
	ptr->table_class = class;
	ptr->table_size = 0;
	ptr->assembly_label = 0;
	ptr->temp_offset = 2*8; 
	ptr->parent = top_table();

	
	ptr->next = head_table;
	ptr->prev = head_table->prev;
	ptr->id = ptr->prev->id + 1;

	
	head_table->prev->next = ptr;
	head_table->prev = ptr;
	
	return ptr;
}



void pop_table()
{
	
	table_t* to_remove = head_table->prev;
	if(to_remove == head_table)
	{
		fprintf(stderr, "Cannot pop head table!");
		return;
	}

	
	for(int i = 0; i < TABLE_SIZE; i++)
	{
		while(1)
		{
			entry_t* cur_entry = to_remove->hash_table[i];
			
			
			if(cur_entry == NULL)
				break;
			
			else if(cur_entry->next == NULL)
			{
				free(cur_entry->entry_name);
				free(cur_entry->arg_types);
				free(cur_entry);
				cur_entry = NULL;
				break;
			}
			
			else
			{
				
				while(cur_entry->next->next != NULL)
					cur_entry = cur_entry->next;
				
				
				free(cur_entry->next->entry_name);
				free(cur_entry->next->arg_types);
				free(cur_entry->next);
				cur_entry->next = NULL;
			}

		}
	}


	
	to_remove->prev->next = head_table;
	head_table->prev = to_remove->prev;

	
	to_remove->next = NULL;
	to_remove->prev = NULL;
	to_remove->parent = NULL;
	free(to_remove);

	
	caller = top_table();
}



table_t* top_table()
{
	return head_table->prev;
}






void print_table(table_t* table)
{
	fprintf(stderr, "\n\n\nHASH TABLE %d: %s '%s'\n", table->id, class_string(table->table_class), table->table_name);
	for(int i = 0; i < 75; i++)
		fprintf(stderr, "_");
	fprintf(stderr, "\n\nname\tclass\ttype\tvalue\t\targs\targ_types\n\n");
	for(int i = 0; i < TABLE_SIZE; i++)
	{
		entry_t* entry = table->hash_table[i];
		while(entry != NULL)
		{
			
			switch(entry->entry_class)
			{
			case FUNCTION:
				switch(entry->return_type)
				{
				case INUM:
					fprintf(stderr, "%s\t%s\t%s\t%s\t\t%d\t%s\n", 
						entry->entry_name, class_string(entry->entry_class), 
						type_string(entry->return_type), "none", entry->arg_num,
						arg_string(entry->arg_num, entry->arg_types));
					break;
				case RNUM:
					fprintf(stderr, "%s\t%s\t%s\t%s\t\t%d\t%s\n", 
						entry->entry_name, class_string(entry->entry_class), 
						type_string(entry->return_type), "none", entry->arg_num,
						arg_string(entry->arg_num, entry->arg_types));
					break;
				default:
					fprintf(stderr, "\nERROR, LINE %d: function of unknown type.\n", yylineno);
				}
				break;

			case PROCEDURE:
				fprintf(stderr, "%s\t%s\t%s\t%s\t\t%d\t%s\n", 
					entry->entry_name, class_string(entry->entry_class), 
					"none", "none", entry->arg_num, 
					arg_string(entry->arg_num, entry->arg_types));
				break;

			case ARRAY:
				switch(entry->return_type)
				{
				case INUM:
					fprintf(stderr, "%s\t%s\t%s\t%p\t%d\n", 
						entry->entry_name, class_string(entry->entry_class), 
						type_string(entry->return_type), entry->entry_value.aival, 
						entry->arg_num);
					break;
				case RNUM:
					fprintf(stderr, "%s\t%s\t%s\t%p\t%d\n", 
						entry->entry_name, class_string(entry->entry_class), 
						type_string(entry->return_type), entry->entry_value.afval, 
						entry->arg_num);
					break;
				default:
					fprintf(stderr, "\nERROR, LINE %d: array of unknown type.\n", yylineno);
				}
				break;

			case VAR:
				switch(entry->return_type)
				{
				case INUM:
					fprintf(stderr, "%s\t%s\t%s\t%d\t\t%d\n", 
						entry->entry_name, class_string(entry->entry_class), 
						type_string(entry->return_type), entry->entry_value.ival, 
						entry->arg_num);
					break;
				case RNUM:
					fprintf(stderr, "%s\t%s\t%s\t%f\t%d\n", 
						entry->entry_name, class_string(entry->entry_class), 
						type_string(entry->return_type), entry->entry_value.fval, 
						entry->arg_num);
					break;
				case STRING:
					fprintf(stderr, "%s\t%s\t%s\t%s\t\t%d\n", 
						entry->entry_name, class_string(entry->entry_class), 
						type_string(entry->return_type), entry->entry_value.sval, 
						entry->arg_num);
					break;
				case PROGRAM:
					fprintf(stderr, "%s\t%s\t%s\t%d\t\t%d\n", 
						entry->entry_name, class_string(entry->entry_class), 
						type_string(entry->return_type), entry->entry_value.ival, 
						entry->arg_num);
					break;
				default:
					fprintf(stderr, "\nERROR, LINE %d: variable of unknown type.\n", yylineno);
					break;
				}
				break;
			default:
				fprintf(stderr, "\nERROR, LINE %d: object of unknown class.\n", yylineno);
				break;

			}
			entry = entry->next;
		}
	}
	fprintf(stderr, "\n\n");
}



char* arg_string(int argnum, int* args)
{
	char* string = (char*)malloc(100*sizeof(char));
	for(int i = 0; i < 100; i++)
		string[i] = '\0';
	for(int i = 0; i < argnum; i++)
	{
		strcat(string, type_string(args[i]));
		strcat(string, " ");
	}
	return string;
}



char* type_string(int token)
{
	switch(token)
	{
		case RNUM:
			return "real";
		case INUM:
			return "int";
		case STRING:
			return "string";
		case BOOL:
			return "bool";
		case PROGRAM:
			return "i/o";
		case EMPTY:
			return "empty";
		case INTEGER:
			return "integer keyword"; // BAD!
		case REAL:
			return "real keyword"; // BAD!

		case ADDOP:
			return "addop";
		case MULOP:
			return "mulop";
		case RELOP:
			return "relop";
		case ASSOP:
			return ":=";
		case NOT:
			return "not";
			
		case ARRAYOP:
			return "[]";
		case PARENOP:
			return "()";
		case LISTOP:
			return ",";

		case IDENT:
			return "ident";

		default:
			return "other";
	}
}



char* class_string(int token)
{
	switch(token)
	{
		case VAR:
			return "var";
		case ARRAY:
			return "array";
		case FUNCTION:
			return "fcn";
		case PROCEDURE:
			return "proc";
		default:
			return "other";
	}
}



entry_t* make_entry(char* name, int entry_class, value* val_ptr, int return_type, int arg_num, int* arg_types, int start_idx, int stop_idx)
{
	entry_t* ptr = (entry_t*)malloc(sizeof(entry_t));
	ptr->entry_name = strdup(name);
	ptr->entry_class = entry_class;
	ptr->return_type = return_type;
	
	if(entry_class == VAR) // or VAR_PARAM
	{
		switch(return_type)
		{
		case INUM:
			ptr->entry_value.ival = val_ptr->ival;
			break;
		case RNUM:
			ptr->entry_value.fval = val_ptr->fval;
			break;
		case STRING:
			ptr->entry_value.sval = val_ptr->sval;
			break;
		default:
			break;
		}
	}
	
	ptr->arg_num = arg_num;
	
	if(arg_num > 0)
	{
		ptr->arg_types = (int*)malloc(arg_num*sizeof(int));
		memcpy(ptr->arg_types, arg_types, arg_num*sizeof(int));
	}
	else
	{
		ptr->arg_types = NULL;
	}
	
	ptr->start_idx = start_idx;
	ptr->stop_idx = stop_idx;
	ptr->next = NULL;
	return ptr;
}



entry_t* get_entry(table_t* table, char* name)
{
	entry_t* cur_entry = table->hash_table[ hashpjw(name) ];
	while(cur_entry != NULL)
	{
		if( !strcmp(name, cur_entry->entry_name) )
			return cur_entry;
		else
			cur_entry = cur_entry->next;
	}
	return NULL;
}



entry_t* find_entry(table_t* table, char* name)
{
	
	while(table != head_table)
	{
		entry_t* cur_entry = table->hash_table[ hashpjw(name) ];
		while(cur_entry != NULL)
		{
			if( !strcmp(name, cur_entry->entry_name) )
				return cur_entry;
			else
				cur_entry = cur_entry->next;
		}
		table = table->prev;
	}
	return NULL;
}



int insert_entry(entry_t* entry_ptr, table_t* table)
{
	
	if(get_entry(table, entry_ptr->entry_name) != NULL)
	{
		fprintf(stderr, "\nERROR, LINE %d: entry '%s' already exists within current scope.\n", yylineno, entry_ptr->entry_name);
		exit(0);
	}

	else 
	{
		table->table_size++;
		entry_ptr->id = table->table_size;

		entry_t* last_entry = table->hash_table[ hashpjw(entry_ptr->entry_name) ];
		
		if(last_entry != NULL)
		{
			while(last_entry->next != NULL)
				last_entry = last_entry->next;
			last_entry->next = entry_ptr;
		}
		else 
		{
			table->hash_table[hashpjw(entry_ptr->entry_name)] = entry_ptr;
		}
		return 1;
	}
}



int num_keyword_to_type(int token)
{
	switch(token)
	{
	case INTEGER:
		return INUM;
		break;
	case REAL:
		return RNUM;
		break;
	default:
		return EMPTY;
		break;
	}
}



void make_function(tree_t* fn_ptr, tree_t* type_ptr)
{

	int fn_class = FUNCTION;
	char *fn_name, *fn_name2;
	int fn_arg_num = 0;
	int *fn_args, *fn_args2;
	int fn_type = num_keyword_to_type(type_ptr->type);
	
	if(fn_ptr->type != PARENOP) 
	{
		fn_name = fn_ptr->attribute.sval;
		entry_t* entry_ptr = 
			make_entry(fn_name, fn_class, NULL, fn_type, 0, NULL, 0, 0);
		insert_entry(entry_ptr, top_table()->prev); 
		
		
		fn_name2 = fn_ptr->attribute.sval;
		entry_t* entry_ptr2 = 
			make_entry(fn_name2, fn_class, NULL, fn_type, 0, NULL, 0, 0);
		insert_entry(entry_ptr2, top_table()); 
	}
	else 
	{
		fn_name = fn_ptr->left->attribute.sval;
		fn_arg_num = count_args(fn_ptr->right);
		fn_args = get_args(fn_ptr->right, fn_arg_num);
		entry_t* entry_ptr = 
			make_entry(fn_name, fn_class, NULL, fn_type, fn_arg_num, fn_args, 0, 0);
		insert_entry(entry_ptr, top_table()->prev); 
		
		
		fn_name2 = fn_ptr->left->attribute.sval;
		fn_args2 = get_args(fn_ptr->right, fn_arg_num);
		entry_t* entry_ptr2 = 
			make_entry(fn_name2, fn_class, NULL, fn_type, fn_arg_num, fn_args2, 0, 0);
		insert_entry(entry_ptr2, top_table()); 
	}
}



void make_procedure(tree_t* proc_ptr)
{
	int proc_class = PROCEDURE;
	char* proc_name;
	int proc_arg_num = 0;
	int* proc_args;
	int proc_type = EMPTY;
	
	if(proc_ptr->type != PARENOP) 
	{
		proc_name = proc_ptr->attribute.sval;
		entry_t* entry_ptr = 
			make_entry(proc_name, proc_class, NULL, proc_type, 0, NULL, 0, 0);
		insert_entry(entry_ptr, top_table()->prev);
	}
	else 
	{
		proc_name = proc_ptr->left->attribute.sval;
		proc_arg_num = count_args(proc_ptr->right);
		proc_args = get_args(proc_ptr->right, proc_arg_num);
		entry_t* entry_ptr = 
			make_entry(proc_name, proc_class, NULL, 
				proc_type, proc_arg_num, proc_args, 0, 0);
		insert_entry(entry_ptr, top_table()->prev);
	}
}


void check_function(tree_t* head_ptr, tree_t* body_ptr)
{
	if(head_ptr->type == FUNCTION)
	{
		int fn_type = num_keyword_to_type(head_ptr->right->type);

		head_ptr = head_ptr->left;
		if(head_ptr->type == PARENOP)
			head_ptr = head_ptr->left;
		char* fn_name = head_ptr->attribute.sval;
		
		
		tree_t* return_stmt = find_return_stmt(fn_name, body_ptr);
		if(return_stmt == NULL)
		{
			fprintf(stderr, 
				"\nERROR, LINE %d: return statement missing from function '%s'.\n", 
				yylineno, fn_name);
			exit(0);
		}

		
		if(type(return_stmt->right) != fn_type)
		{
			fprintf(stderr, "\nERROR, LINE %d: '%s's return statement of type '%s' given argument of type '%s'.\n", yylineno, fn_name, type_string(fn_type), type_string(type(return_stmt->right)));
			exit(0);
		}
	}
}



tree_t* find_return_stmt(char* fn_name, tree_t* t)
{
	
	if(t == NULL || t->type == EMPTY)
		return NULL;

	
	if(t->type == ASSOP)
	{
		char* assigned_name = t->left->attribute.sval;
		if(!strcmp(assigned_name, fn_name))
			return t;
		else
		{
			
			if(get_entry(top_table(), assigned_name) == NULL && 
				find_entry(top_table()->prev, assigned_name) != NULL)
			{
				fprintf(stderr, "\nERROR LINE %d: cannot assign value of non-local variable '%s' from within function '%s'.\n", yylineno, assigned_name, fn_name);
				exit(0);
			}
		}
	}

	
	else
	{
		tree_t* left = find_return_stmt(fn_name, t->left);
		tree_t* right = find_return_stmt(fn_name, t->right);
		if(right != NULL)
			return right;
		if(left != NULL)
			return left;
	}

	
	return NULL;
}



int count_args(tree_t* arg_ptr)
{
	int count = 0;
	while(arg_ptr->type == LISTOP && !leaf_node(arg_ptr))
	{
		count++;
		arg_ptr = arg_ptr->left;
	}
	return count;
}



int* get_args(tree_t* arg_ptr, int arg_num)
{
	int* type_list_ptr = (int*)malloc(sizeof(int)*arg_num);
	for(int i = 0; i < arg_num; i++)
	{
		type_list_ptr[i] = num_keyword_to_type(arg_ptr->right->right->type);
		arg_ptr = arg_ptr->left;
	}
	return type_list_ptr;
}



void make_vars(tree_t* var_ptr, tree_t* type_ptr)
{
	int var_type = 0;
	int var_class = 0;
	int start_idx = 0;
	int stop_idx = 0;

	
	if(type_ptr->type == ARRAY) 
	{
		var_class = ARRAY;
		var_type = type_ptr->right->type;
		
		type_ptr = type_ptr->left;
		if(type_ptr->type != DOTDOT)
		{
			fprintf(stderr, "\nERROR, LINE %d: array index missing DOTDOT.\n", yylineno);
			exit(0);
		}

		if(type_ptr->left->type != INUM || type_ptr->right->type != INUM)
		{
			fprintf(stderr, "\nERROR, LINE %d: array indices must be integral.\n", yylineno);
			exit(0);
		}

		start_idx = type_ptr->left->attribute.ival;
		stop_idx = type_ptr->right->attribute.ival;
	}
	else 
	{
		var_class = VAR;
		var_type = type_ptr->type;
	}

	
	while(var_ptr->type == LISTOP)
	{
		char* var_name = var_ptr->right->attribute.sval;
		switch(var_class)
		{
		case VAR:
			switch(var_type)
			{
			case INTEGER:
				top_table()->temp_offset += 8;
				make_var_inum(var_name);
				break;
			case REAL:
				top_table()->temp_offset += 8;
				make_var_rnum(var_name);
				break;
			default:
				fprintf(stderr, "\nERROR, LINE %d: invalid type, must be integer or real.\n", yylineno);
				exit(0);
				break;
			}
			break;

		case ARRAY:
			switch(var_type)
			{
			case INTEGER:
				make_arr_inum(var_name, start_idx, stop_idx);
				break;
			case REAL:
				make_arr_rnum(var_name, start_idx, stop_idx);
				break;
			default:
				fprintf(stderr, "\nERROR, LINE %d: invalid type, must be integer or real.\n", yylineno);
				exit(0);
				break;
			}
			break;
		default:
				fprintf(stderr, "\nERROR, LINE %d: invalid class declaration, must be variable or array.\n", yylineno);
				exit(0);
		}
		var_ptr = var_ptr->left;
	}
	top_table()->num_locals = top_table()->table_size - top_table()->num_params;
}



void add_io(tree_t* ident_list_ptr)
{
	while(ident_list_ptr->type == LISTOP)
	{
		int proc_class = PROCEDURE;
		char* proc_name;
		int proc_arg_num = 0;
		int* proc_args;
		int proc_type = EMPTY;
		char* io_option = ident_list_ptr->right->attribute.sval;

		if(!strcmp(io_option, "input"))
		{
			proc_name = "read";
			proc_arg_num = 1;
			proc_args = (int*)malloc(sizeof(int));
			*proc_args = INUM;
			entry_t* entry_ptr = 
				make_entry(proc_name, proc_class, NULL, 
					proc_type, proc_arg_num, proc_args, 0, 0);
			insert_entry(entry_ptr, top_table());
		}
		else if(!strcmp(io_option, "output"))
		{
			proc_name = "write";
			proc_arg_num = 1;
			proc_args = (int*)malloc(sizeof(int));
			*proc_args = INUM;
			entry_t* entry_ptr = 
				make_entry(proc_name, proc_class, NULL, 
					proc_type, proc_arg_num, proc_args, 0, 0);
			insert_entry(entry_ptr, top_table());
		}
		else
		{
			fprintf(stderr, "\nERROR, LINE %d: 'input' and 'output' are only valid i/o options, not %s\n", yylineno, io_option);
			exit(0);
		}

		ident_list_ptr = ident_list_ptr->left;
	}
	top_table()->num_params = top_table()->table_size;
	add_io_code();
}



void add_params(tree_t* param_ptr)
{
	
	while(param_ptr->type != EMPTY)
	{
		int var_type = 0;
		int var_class = 0;
		int start_idx = 0;
		int stop_idx = 0;

		
		tree_t* type_ptr = param_ptr->right->right;
		if(type_ptr->type == ARRAY) 
		{
			var_class = ARRAY;
			var_type = type_ptr->right->type;
			
			type_ptr = type_ptr->left;
			if(type_ptr->type != DOTDOT)
			{
				fprintf(stderr, "\nERROR, LINE %d: parameter array index missing DOTDOT\n.", yylineno);
				exit(0);
			}

			if(type_ptr->left->type != INUM || type_ptr->right->type != INUM)
			{
				fprintf(stderr, "\nERROR, LINE %d: parameter array indices must be integral.\n", yylineno);
				exit(0);
			}
			start_idx = type_ptr->left->attribute.ival;
			stop_idx = type_ptr->right->attribute.ival;
		}
		else 
		{
			var_class = VAR; 
			var_type = type_ptr->type;
		}


		
		tree_t* var_ptr = param_ptr->right->left;
		value default_val;
		while(var_ptr->type == LISTOP)
		{
			char* var_name = var_ptr->right->attribute.sval;
			switch(var_class)
			{
			case VAR:
				switch(var_type)
				{
				case INTEGER:
					make_var_inum(var_name);
					
					break;
				case REAL:
					make_var_rnum(var_name);
					break;
				default:
					fprintf(stderr, "\nERROR, LINE %d: invalid parameter type, must be integer or real.\n", yylineno);
					exit(0);
				}
				break;

			case ARRAY:
				switch(var_type)
				{
				case INTEGER:
					make_arr_inum(var_name, start_idx, stop_idx);
					break;
				case REAL:
					make_arr_rnum(var_name, start_idx, stop_idx);
					break;
				default:
					fprintf(stderr, "\nERROR, LINE %d: invalid parameter type, must be integer or real.\n", yylineno);
					exit(0);
				}
				break;
			default:
				fprintf(stderr, "\nERROR, LINE %d: invalid parameter class, must be variable or array.\n", yylineno);
				exit(0);
			}
			var_ptr = var_ptr->left;
		}

		param_ptr = param_ptr->left;
	}
	top_table()->num_params = top_table()->table_size;
}


void make_var_inum(char* name)
{
	int default_ival = 0;

	
	entry_t* ptr = (entry_t*)malloc(sizeof(entry_t));
	ptr->entry_name = strdup(name);
	ptr->entry_class = VAR;
	ptr->return_type = INUM;
	ptr->entry_value.ival = default_ival;
	ptr->next = NULL;

	
	ptr->arg_num = 0;
	ptr->arg_types = NULL;
	ptr->start_idx = 0;
	ptr->stop_idx = 0;

	insert_entry(ptr, top_table());
}


void make_var_io(char* name)
{
	int default_ioval = 0;

	
	entry_t* ptr = (entry_t*)malloc(sizeof(entry_t));
	ptr->entry_name = strdup(name);
	ptr->entry_class = VAR;
	ptr->return_type = PROGRAM;
	ptr->entry_value.ival = default_ioval;
	ptr->next = NULL;

	
	ptr->arg_num = 1;
	int* args = (int*)malloc(sizeof(int));
	args[0] = INUM;
	ptr->arg_types = args;
	ptr->start_idx = 0;
	ptr->stop_idx = 0;

	insert_entry(ptr, top_table());
}


void make_var_rnum(char* name)
{
	float default_fval = 0.0;

	
	entry_t* ptr = (entry_t*)malloc(sizeof(entry_t));
	ptr->entry_name = strdup(name);
	ptr->entry_class = VAR;
	ptr->return_type = RNUM;
	ptr->entry_value.fval = default_fval;
	ptr->next = NULL;

	
	ptr->arg_num = 0;
	ptr->arg_types = NULL;
	ptr->start_idx = 0;
	ptr->stop_idx = 0;

	insert_entry(ptr, top_table());
}
	
void make_arr_inum(char* name, int start_idx, int stop_idx)
{
	int default_ival = 0;

	
	entry_t* ptr = (entry_t*)malloc(sizeof(entry_t));
	ptr->entry_name = strdup(name);
	ptr->entry_class = ARRAY;
	ptr->return_type = INUM;

	int* arr_ptr = (int*)malloc(sizeof(int)*(stop_idx-start_idx+1));
	for(int i = start_idx; i <= stop_idx; i++)
		arr_ptr[i-start_idx] = default_ival;
	
	ptr->entry_value.aival = arr_ptr;
	ptr->next = NULL;
	ptr->start_idx = start_idx;
	ptr->stop_idx = stop_idx;

	
	ptr->arg_num = 0;
	ptr->arg_types = NULL;

	insert_entry(ptr, top_table());
}

void make_arr_rnum(char* name, int start_idx, int stop_idx)
{
	float default_fval = 0;

	
	entry_t* ptr = (entry_t*)malloc(sizeof(entry_t));
	ptr->entry_name = strdup(name);
	ptr->entry_class = ARRAY;
	ptr->return_type = RNUM;

	float* arr_ptr = (float*)malloc(sizeof(float)*(stop_idx-start_idx+1));
	for(int i = start_idx; i <= stop_idx; i++)
		arr_ptr[i-start_idx] = default_fval;
	
	ptr->entry_value.afval = arr_ptr;
	ptr->next = NULL;
	ptr->start_idx = start_idx;
	ptr->stop_idx = stop_idx;

	
	ptr->arg_num = 0;
	ptr->arg_types = NULL;

	insert_entry(ptr, top_table());
}

int get_entry_id(table_t* table, char* name)
{
	entry_t* entry_ptr = get_entry(table, name);
	if(entry_ptr != NULL)
		return entry_ptr->id;
	else
		return 0;
	
}
