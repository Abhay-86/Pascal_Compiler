#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#include "gencode.h"
#include "tree.h"
#include "hash.h"
#include "reg_stack.h"
#include "externs.h"
#include "compiler.tab.h"

FILE* outfile;


void file_header(char* filename)
{
	if (GENCODE_DEBUG) fprintf(outfile, "# file header\n");
	fprintf(outfile, "\t.file\t\"%s\"\n", filename);
	fprintf(outfile, "\t.intel_syntax noprefix\n\n");
}



void add_io_code()
{
	if(get_entry(top_table(), "write") || get_entry(top_table(), "read"))
	{
		if (GENCODE_DEBUG) fprintf(outfile, "\n# create io format strings\n");
		fprintf(outfile, "\t.section\t.rodata\n");
		fprintf(outfile, ".LC0: # reading\n");
		fprintf(outfile, "\t.string \"%%lld\"\n");
		fprintf(outfile, ".LC1: # writing\n");
		fprintf(outfile, "\t.string \"%%lld\\n\"\n");
	}
	fprintf(outfile, "\t.text\n\n\n");
}



void file_footer()
{
	if (GENCODE_DEBUG) fprintf(outfile, "\n# file footer\n");
	fprintf(outfile, "\t.ident\t\"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609\"\n");
	fprintf(outfile, "\n\t.section\t.note.GNU-stack,\"\",@progbits\n");
}



void function_header(tree_t* n)
{
	tree_t* name_ptr = n->left;
	if(name_ptr->type == PARENOP)
		name_ptr = name_ptr->left;
	if(name_ptr->type != IDENT)
	{
		fprintf(stderr, "\nERROR, LINE %d: function name expected.\n", yylineno);
		exit(1);
	}

	char* fn_name = name_ptr->attribute.sval;

	
	if (GENCODE_DEBUG) fprintf(outfile, "\n# function header\n");
	fprintf(outfile, "\t.globl\t%s\n", fn_name);
	fprintf(outfile, "\t.type\t%s, @function\n", fn_name);
	fprintf(outfile, "%s:\n", fn_name);
	fprintf(outfile, "\tpush\trbp\n");
	fprintf(outfile, "\tmov\t\trbp, rsp\n\n");

	
	if (GENCODE_DEBUG) fprintf(outfile, "\n# set up stack frame\n");
	fprintf(outfile, "\tpush\t0\n");
	push_static_parent();
	fprintf(outfile, "\tsub\t\trsp, %d\n", 8*(top_table()->num_locals));
	if (GENCODE_DEBUG) fprintf(outfile, "\t# end function header\n");
}



void function_footer(tree_t* n)
{
	tree_t* name_ptr = n->left;
	if(name_ptr->type == PARENOP)
		name_ptr = name_ptr->left;
	if(name_ptr->type != IDENT)
	{
		fprintf(stderr, "\nERROR, LINE %d: function name expected.\n", yylineno);
		exit(1);
	}

	char* fn_name = name_ptr->attribute.sval;

	if (GENCODE_DEBUG) fprintf(outfile, "\n# function footer\n");
	fprintf(outfile, ".L%d:\n", n->attribute.ival);
	fprintf(outfile, "\tmov\t\trax, QWORD PTR [rbp-8]\n");
	fprintf(outfile, "\tmov\t\trsp, rbp\n");
	fprintf(outfile, "\tpop\t\trbp\n");
	fprintf(outfile, "\tret\n");
	fprintf(outfile, "\t.size\t%s, .-%s\n\n\n", fn_name, fn_name);
}



void main_header()
{
	if (GENCODE_DEBUG) fprintf(outfile, "\n# main header\n");
	fprintf(outfile, "\t.globl\tmain\n");
	fprintf(outfile, "\t.type\tmain, @function\n");
	fprintf(outfile, "main:\n");
	fprintf(outfile, "\tpush\trbp\n");
	fprintf(outfile, "\tmov\t\trbp, rsp\n");

	
	if (GENCODE_DEBUG) fprintf(outfile, "\n# set up stack frame\n");
	fprintf(outfile, "\tpush\t0\n");
	fprintf(outfile, "\tpush\trbp\n");
	fprintf(outfile, "\tsub\t\trsp, %d\n", 8*(top_table()->num_locals));
	if (GENCODE_DEBUG) fprintf(outfile, "\t# end function header\n");

	if (GENCODE_DEBUG) fprintf(outfile, "\n# main code\n");
}



void main_footer()
{
	if (GENCODE_DEBUG) fprintf(outfile, "\n# main footer\n");
	fprintf(outfile, "\tmov\t\teax, 0\n");
	fprintf(outfile, "\tleave\n");
	fprintf(outfile, "\tret\n");
	fprintf(outfile, "\n\t.size\tmain, .-main\n\n\n");
}



char* ia64(char* opval)
{
	if(!strcmp(opval, "+"))
		return strdup("add ");
	if(!strcmp(opval, "-"))
		return strdup("sub ");
	if(!strcmp(opval, "*"))
		return strdup("imul");
	if(!strcmp(opval, "/"))
		return strdup("idiv");
	return strdup("not_op");
}



char* string_value(tree_t* n)
{
	char str[100];
	switch(n->type)
	{
		case INUM:
			sprintf(str, "%d", n->attribute.ival);
			return strdup(str);
		
		case RNUM:
			sprintf(str, "%f", n->attribute.fval);
			return strdup(str);
		
		case IDENT:
		case STRING:
			grab_nonlocal_var(n->attribute.sval);
			return var_to_assembly(n->attribute.sval);
		case PARENOP: // function call
			return strdup("rax");
		default:
			return strdup("???");
	}
}




void grab_nonlocal_var(char* name)
{
	
	if(get_entry_id(top_table(), name))
		return;
	
	if (GENCODE_DEBUG) fprintf(outfile, "\n# find nonlocal variable\n");

	
	int scopes_back = 0;
	table_t* table = top_table();
	int id = get_entry_id(table, name);
	while(id == 0)
	{
		scopes_back++;
		if(table == head_table)
		{
			fprintf(stderr, "\nERROR, LINE %d: variable '%s' could not be found.\n", 
				yylineno, name);
			exit(0);
		}
		table = table->parent;
		id = get_entry_id(table, name);
	}
 
	fprintf(outfile, "\tmov\t\trcx, rbp\n");
	for(int i = 0; i < scopes_back; i++)
	{
		fprintf(outfile, "\tmov\t\trcx, QWORD PTR [rcx-16]\n");
	}

	if (GENCODE_DEBUG) fprintf(outfile, "\t# end nonlocal variable\n");
}



char* var_to_assembly(char* name)
{
	table_t* table = top_table();
	int id = get_entry_id(table, name);

	char* base_ptr = strdup("rbp"); 
	if(!id)
		base_ptr = strdup("rcx"); 

	
	while(id == 0)
	{
		if(table == head_table)
		{
			fprintf(stderr, "\nERROR, LINE %d: variable '%s' could not be found.\n", 
				yylineno, name);
			exit(0);
		}
		table = table->parent;
		id = get_entry_id(table, name);
	}

	
	int params = table->num_params;
	if(id <= params) 
	{
		char str[150];
		sprintf(str, "QWORD PTR [%s+", base_ptr);
		char num[20];
		sprintf(num, "%d", (params-id+2)*8); 
		strcat(str, num);
		strcat(str, "]");
		return strdup(str);
	}
	else 
	{
		char str[150];
		sprintf(str, "QWORD PTR [%s-", base_ptr);
		char num[20];
		sprintf(num, "%d", (id-params+2)*8); 	
		strcat(str, num);						
		strcat(str, "]");						
		return strdup(str);
	}
}



void set_fn_assembly_label(int l)
{
	top_table()->assembly_label = l;
}



void assignment_gencode(tree_t* n)
{
	if (GENCODE_DEBUG) fprintf(outfile, "\n# evaluate expression\n");
	gencode(n->right);
	if(!strcmp(n->left->attribute.sval, top_table()->table_name))
	{
		if (GENCODE_DEBUG) fprintf(outfile, "\n# return statement\n");
		fprintf(outfile, "\tmov\t\tQWORD PTR [rbp-8], %s\n", reg_string(top(rstack)));
		fprintf(outfile, "\tjmp\t\t.L%d\n", top_table()->assembly_label);
	}
	else
	{
		if (GENCODE_DEBUG) fprintf(outfile, "\n# assignment\n");
		fprintf(outfile, "\tmov\t\t%s, %s\n", 
			string_value(n->left), reg_string(top(rstack)));
	}
}


void start_if_gencode(tree_t* n, int label_num)
{
	if (GENCODE_DEBUG) fprintf(outfile, "\n# start if\n");
	gencode(n); 
	fprintf(outfile, "\tcmp\t\t%s, 0\n", reg_string(top(rstack)));
	fprintf(outfile, "\tje\t\t.L%d\n", label_num);
	if (GENCODE_DEBUG) fprintf(outfile, "\t# end conditional\n");
}


void start_if_else_gencode(tree_t* n, int label_num)
{
	if (GENCODE_DEBUG) fprintf(outfile, "\n# start if-else\n");
	gencode(n); 
	fprintf(outfile, "\tcmp\t\t%s, 0\n", reg_string(top(rstack)));
	fprintf(outfile, "\tje\t\t.L%d\n", label_num);
	if (GENCODE_DEBUG) fprintf(outfile, "\t# end conditional\n");
}


void mid_if_else_gencode(int label_num)
{
	if (GENCODE_DEBUG) fprintf(outfile, "\n# mid if-else\n");
	fprintf(outfile, "\tjmp\t\t.L%d\n", label_num+1);
	fprintf(outfile, ".L%d:\n", label_num);
}


void end_if_gencode(int label_num)
{
	fprintf(outfile, ".L%d:\n", label_num);
	if (GENCODE_DEBUG) fprintf(outfile, "\n# end if\n");
}


void start_while_do_gencode(tree_t* n, int label_num)
{
	if (GENCODE_DEBUG) fprintf(outfile, "\n# start while\n");
	fprintf(outfile, ".L%d:\n", label_num);
	gencode(n); // evaluate conditional
	fprintf(outfile, "\tcmp\t\t%s, 0\n", reg_string(top(rstack)));
	fprintf(outfile, "\tje\t\t.L%d\n", label_num+1);
	if (GENCODE_DEBUG) fprintf(outfile, "\t# end while, start do\n");
}


void end_while_do_gencode(int label_num)
{
	fprintf(outfile, "\tjmp\t\t.L%d\n", label_num);
	fprintf(outfile, ".L%d:\n", label_num+1);
	if (GENCODE_DEBUG) fprintf(outfile, "\t# end do\n");
}


void start_repeat_until_gencode(int label_num)
{
	if (GENCODE_DEBUG) fprintf(outfile, "\n# start repeat\n");
	fprintf(outfile, ".L%d:\n", label_num);
}


void end_repeat_until_gencode(tree_t* n, int label_num)
{
	if (GENCODE_DEBUG) fprintf(outfile, "\t# end repeat, start until\n");
	gencode(n); 
	fprintf(outfile, "\tcmp\t\t%s, 0\n", reg_string(top(rstack)));
	fprintf(outfile, "\tje\t\t.L%d\n", label_num);
	if (GENCODE_DEBUG) fprintf(outfile, "\t# end until\n");
}


void start_for_gencode(int l, tree_t* var, tree_t* e1, char* to_downto, tree_t* e2)
{
	int UP;
	if(!strcmp(to_downto, "to")) UP = 1;
	else UP = 0;

	if (GENCODE_DEBUG) fprintf(outfile, "\n# start for\n");
	gencode(e1);
	fprintf(outfile, "\tmov\t\t%s, %s\n", string_value(var), reg_string(top(rstack)));
	if (GENCODE_DEBUG) fprintf(outfile, "\t# evaluated start position\n");
	
	gencode(e2);
	fprintf(outfile, "\tmov\t\trbx, %s\n", reg_string(top(rstack)));
	if (GENCODE_DEBUG) fprintf(outfile, "\t# evaluated end position\n");

	fprintf(outfile, ".L%d:\n", l);
	if(UP)
	{
		fprintf(outfile, "\tcmp\t\t%s, rbx\n", string_value(var));
		fprintf(outfile, "\tjg\t\t.L%d\n", l+1);
		if (GENCODE_DEBUG) fprintf(outfile, "\t# end for\n\n# start do");
	}
	else
	{
		fprintf(outfile, "\tcmp\t\t%s, rbx\n", string_value(var));
		fprintf(outfile, "\tjl\t\t.L%d\n", l+1);
		if (GENCODE_DEBUG) fprintf(outfile, "\t# end for\n\n# start do");
	}
}


void end_for_gencode(int l, tree_t* var, char* to_downto)
{
	int UP;
	if(!strcmp(to_downto, "to")) UP = 1;
	else UP = 0;

	if(UP)
		fprintf(outfile, "\tinc\t\t%s\n", string_value(var));
	else
		fprintf(outfile, "\tdec\t\t%s\n", string_value(var));

	fprintf(outfile, "\tjmp\t\t.L%d\n", l);
	fprintf(outfile, ".L%d:\n", l+1);
	if (GENCODE_DEBUG) fprintf(outfile, "\t# end for-do\n");
}



void call_procedure(tree_t* n)
{
	if(n->type != PARENOP)
	{	
		char* name = strdup(n->attribute.sval);
		if (GENCODE_DEBUG) fprintf(outfile, "\n# call procedure '%s'\n", name);
		fprintf(outfile, "\tcall\t%s\n\n", name);
		return;
	}

	char* name = strdup(n->left->attribute.sval);
	if(!strcmp(name, "read")) 
	{
		char* var_name = n->right->right->attribute.sval;
		if (GENCODE_DEBUG) fprintf(outfile, "\n# call 'read' using fscanf\n");
		fprintf(outfile, "\tmov\t\trax, QWORD PTR fs:40\n");
		fprintf(outfile, "\txor\t\teax, eax\n");
		fprintf(outfile, "\tmov\t\trax, QWORD PTR stdin[rip]\n");
		grab_nonlocal_var(var_name);
		fprintf(outfile, "\tlea\t\trdx, %s\n", var_to_assembly(var_name));
		fprintf(outfile, "\tmov\t\tesi, OFFSET FLAT:.LC0\n");
		fprintf(outfile, "\tmov\t\trdi, rax\n");
		fprintf(outfile, "\tmov\t\teax, 0\n");
		fprintf(outfile, "\tcall\t__isoc99_fscanf\n\n");
	}
	else if(!strcmp(name, "write")) 
	{
		tree_t* var_ptr = n->right->right;
		if (GENCODE_DEBUG) fprintf(outfile, "\n# evaluate 'write' arguments\n");
		gencode(var_ptr);
		if (GENCODE_DEBUG) fprintf(outfile, "\n# call 'write' using fprintf\n");
		fprintf(outfile, "\tmov\t\trdx, %s\n", reg_string(top(rstack)));
		fprintf(outfile, "\tmov\t\trax, QWORD PTR stderr[rip]\n");
		fprintf(outfile, "\tmov\t\tesi, OFFSET FLAT:.LC1\n");
		fprintf(outfile, "\tmov\t\trdi, rax\n");
		fprintf(outfile, "\tmov\t\teax, 0\n");
		fprintf(outfile, "\tcall\tfprintf\n\n");
	}
	else 
	{
		entry_t* entry_ptr = find_entry(top_table(), name);
		if(entry_ptr != NULL) 
		{
			if(entry_ptr->entry_class != PROCEDURE)
			{
				fprintf(stderr, "\nERROR, LINE %d: '%s' is not a procedure.\n", yylineno, name);
				exit(0);
			}

			if (GENCODE_DEBUG) fprintf(outfile, "\n# evaluate '%s' arguments\n", name);
			tree_t* list_ptr = n->right;
			for(int i = 0; i < entry_ptr->arg_num; i++)
			{
				gencode(list_ptr->right);
				fprintf(outfile,"\tpush %s\n", reg_string(top(rstack)));
				list_ptr = list_ptr->left;
			}
			if (GENCODE_DEBUG) fprintf(outfile, "\n# call procedure '%s'\n", name);
			fprintf(outfile, "\tcall\t%s\n", name);
			fprintf(outfile, "\tadd\t\trsp, %d\n", 8*entry_ptr->arg_num);
		}
	}
}



void call_function(tree_t* n)
{
	
	if(n->type != PARENOP)
	{	
		char* name = strdup(n->attribute.sval);
		if (GENCODE_DEBUG) fprintf(outfile, "\n# call function '%s'\n", name);
		fprintf(outfile, "\tcall\t%s\n\n", name);
		return;
	}

	char* name = strdup(n->left->attribute.sval);

	entry_t* entry_ptr = find_entry(top_table(), name);
	if(entry_ptr != NULL) 
	{
		if(entry_ptr->entry_class != FUNCTION)
		{
			fprintf(stderr, "\nERROR, LINE %d: '%s' is not a function.\n", yylineno, name);
			exit(0);
		}

		if (GENCODE_DEBUG) fprintf(outfile, "\n# evaluate '%s' arguments\n", name);
		tree_t* list_ptr = n->right;
		for(int i = 0; i < entry_ptr->arg_num; i++)
		{
			gencode(list_ptr->right);
			fprintf(outfile,"\tpush %s\n", reg_string(top(rstack)));
			list_ptr = list_ptr->left;
		}
		if (GENCODE_DEBUG) fprintf(outfile, "\n# call function '%s'\n", name);
		fprintf(outfile, "\tcall\t%s\n", name);
		fprintf(outfile, "\tadd\t\trsp, %d\n", 8*entry_ptr->arg_num);
	}

}



void gencode(tree_t* n)
{
	if(empty(n))
		return;

	
	if((leaf_node(n) && n->ershov_num == 1) || n->type == PARENOP)
	{
		if(top(rstack) < 0 && n->type == IDENT) 
			memory_workaround_code("mov", reg_string(top(rstack)), string_value(n));
		else
			print_code("mov", reg_string(top(rstack)), string_value(n));
	}

	
	else if(!empty(n->right) && leaf_node(n->right) && n->right->ershov_num == 0)
	{
		gencode(n->left);
		if(top(rstack) < 0 && n->right->type == IDENT) 
			memory_workaround_code(n->attribute.opval,
				reg_string(top(rstack)), string_value(n->right));
		else
			print_code(n->attribute.opval, 
				reg_string(top(rstack)), string_value(n->right));
	}

	
	else if(n->left->ershov_num <= n->right->ershov_num)
	{
		swap(rstack);
		gencode(n->right);
		int r = pop(rstack);
		gencode(n->left);
		if(r < 0 && top(rstack) < 0) 
			memory_workaround_code(n->attribute.opval, 
				reg_string(top(rstack)), reg_string(r));
		else
			print_code(n->attribute.opval, reg_string(top(rstack)), reg_string(r));
		push(r, rstack);
		swap(rstack);
	}

	
	else if(n->left->ershov_num >= n->right->ershov_num)
	{
		gencode(n->left);
		int r = pop(rstack);
		gencode(n->right);
		if(r < 0 && top(rstack) < 0) 
			memory_workaround_code(n->attribute.opval, reg_string(r), 
				reg_string(top(rstack)));
		else
			print_code(n->attribute.opval, reg_string(r), reg_string(top(rstack)));
		push(r, rstack);
	}
}



void memory_workaround_code(char* opval, char* left, char* right)
{
	fprintf(outfile, "\tmov\t\trdi, %s\n", left);
	fprintf(outfile, "\tmov\t\trsi, %s\n", right);
	print_code(opval, "rdi", "rsi");
	fprintf(outfile, "\tmov\t\t%s, rdi\n", left);
	fprintf(outfile, "\tmov\t\t%s, rsi\n", right);
}



void print_code(char* opval, char* left, char* right)
{
	
	if(!strcmp(opval, "mov"))
		fprintf(outfile, "\tmov\t\t%s, %s\n", left, right);

	
	else if(!strcmp(opval, "+"))
		fprintf(outfile, "\tadd\t\t%s, %s\n", left, right);

	else if(!strcmp(opval, "-"))
		fprintf(outfile, "\tsub\t\t%s, %s\n", left, right);

	else if(!strcmp(opval, "*"))
		fprintf(outfile, "\timul\t%s, %s\n", left, right);

	else if(!strcmp(opval, "/"))
	{
		fprintf(outfile, "\tmov\t\trax, %s\n", left);
		fprintf(outfile, "\tcqo\n");
		fprintf(outfile, "\tidiv\t%s\n", right);
		fprintf(outfile, "\tmov\t\t%s, rax\n", left);
	}

	
	else if(!strcmp(opval, "and"))
		fprintf(outfile, "\tand\t\t%s, %s\n", left, right);

	else if(!strcmp(opval, "or"))
		fprintf(outfile, "\tor\t\t%s, %s\n", left, right);

	else if(!strcmp(opval, "not"))
	{
		fprintf(outfile, "\tcmp\t\t%s, 0\n", left);
		fprintf(outfile, "\tsete\t%s\n", get_end(left));
		fprintf(outfile, "\tmovzx\t%s, %s\n", left, get_end(left));
	}

	
	else 
	{
		char* op;
		if(!strcmp(opval, "=")) 	  op = "sete";
		else if(!strcmp(opval, "<>")) op = "setne";
		else if(!strcmp(opval, "<"))  op = "setl";
		else if(!strcmp(opval, "<=")) op = "setle";
		else if(!strcmp(opval, ">"))  op = "setg";
		else if(!strcmp(opval, ">=")) op = "setge";
		else op = "ERROR";
			
		fprintf(outfile, "\tcmp\t\t%s, %s\n", left, right);
		fprintf(outfile, "\t%s\t%s\n", op, get_end(left));
		fprintf(outfile, "\tmovzx\t%s, %s\n", left, get_end(left));
	}

}



char* get_end(char* reg)
{
	
	if(!strcmp(reg, "rdi")) return strdup("dil");
	if(!strcmp(reg, "rsi")) return strdup("sil");
	if(!strcmp(reg, "rdx")) return strdup("dl");
	if(!strcmp(reg, "rcx")) return strdup("cl");

	
	char new_reg[5];
	strcpy(new_reg, reg);
	if(new_reg[2] == '\0') 
	{
		new_reg[2] = 'b';
		new_reg[3] = '\0';
	}
	else 
	{
		new_reg[3] = 'b';
		new_reg[4] = '\0';
	}
	return strdup(new_reg);
}



void push_static_parent()
{
	if(top_table()->parent == caller) 
		fprintf(outfile, "\tpush\t[rbp]\n");
	else 
	{
		int r = pop(rstack);
		fprintf(outfile, "\tmov\t\t%s, QWORD PTR [rbp]\n", reg_string(r));
		fprintf(outfile, "\tmov\t\t%s, QWORD PTR [%s-16]\n", reg_string(r), reg_string(r));
		fprintf(outfile, "\tpush\t%s\n", reg_string(r));
		push(r, rstack);
	}
}
