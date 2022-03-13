#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "reg_stack.h"
#include "hash.h"
#include "externs.h"

stack_t* rstack;
FILE* outfile;

void print_regs(stack_t* stack)
{
	fprintf(stderr, "\n\nREGISTER STACK\n____________________\n");
	fprintf(stderr, "POS\tID\tNAME\n");
	for(int i = stack->top_idx; i >= -5; i--)
	{
		if(i >= 0)
			fprintf(stderr, "%d:\treg %d\t%s\n", 
				i, stack->reg[i], reg_string(stack->reg[i]));
		else
			fprintf(stderr, "%d:\treg %d\t%s\n", 
				i, stack->temp[-i], reg_string(stack->temp[-i]));
	}
	fprintf(stderr, "\n\n");
}


int top(stack_t* stack)
{
	if(stack->top_idx >= 0)
		return stack->reg[ stack->top_idx ];
	else
		return stack->temp[ -stack->top_idx ];
}



void swap(stack_t* stack)
{
	int old_top, new_top;

	
	if(stack->top_idx > 0)
	{
		old_top = stack->reg[ stack->top_idx ];
		new_top = stack->reg[ stack->top_idx-1 ];
		stack->reg[ stack->top_idx ] = new_top;
		stack->reg[ stack->top_idx-1] = old_top;
	}

	
	else if(stack->top_idx == 0)
	{
		old_top = stack->reg[0];
		new_top = stack->temp[1];
		stack->reg[0] = new_top;
		stack->temp[1] = old_top;
	}

	
	else
	{
		old_top = stack->temp[ -stack->top_idx ];
		new_top = stack->temp[ -(stack->top_idx)+1 ];
		stack->temp[ -stack->top_idx ] = new_top;
		stack->temp[ -(stack->top_idx)+1 ] = old_top;
	}
}



char* reg_string(int reg_id)
{
	
	static char illegal_reg[] = {"rERROR"};
	if(reg_id >= MAX_REGS)
		return illegal_reg;

	
	static char* regs[] = {"r15", "r14", "r13", "r12", "r11", "r10", "r9", "r8"};
	if(reg_id >= 0)
		return regs[reg_id];
	
	
	else
	{
		char temp_name[100] = "";
		sprintf(temp_name, "QWORD PTR [rbp-%d]", top_table()->temp_offset-8*reg_id);
		return strdup(temp_name);
	}
}



int pop(stack_t* stack)
{
	int top_val = top(stack);
	stack->top_idx--;
	return top_val;
}



void push(int new_reg, stack_t* stack)
{
	stack->top_idx++;
	if(stack->top_idx >= 0)
		stack->reg[ stack->top_idx ] = new_reg;
	else
		stack->temp[ -stack->top_idx ] = new_reg;
}
