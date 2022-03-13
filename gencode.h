#ifndef CODE_H
#define CODE_H

#include "tree.h"

/* STRUCTURES */

typedef struct record_s {

	struct record_s *parent;
} record_t;


/* GLOBALS */
extern FILE* outfile;
#define GENCODE_DEBUG 1


/* FUNCTIONS */
void file_header(char* filename);
void file_footer();
void main_header();
void add_io_code();
void main_footer();
void function_header(tree_t* n);
void function_footer(tree_t* n);
void set_fn_assembly_label(int l);
char* ia64(char* opval);
void print_code(char* opval, char* left, char* right);
void memory_workaround_code(char* opval, char* left, char* right);
char* string_value(tree_t* n);
char* get_end(char* r);
void push_static_parent();

void start_if_gencode(tree_t* n, int l);
void start_if_else_gencode(tree_t* n, int l);
void mid_if_else_gencode(int l);
void end_if_gencode(int l);
void start_while_do_gencode(tree_t* n, int l);
void end_while_do_gencode(int l);
void start_repeat_until_gencode(int l);
void end_repeat_until_gencode(tree_t* , int l);
void start_for_gencode(int l, tree_t* var, tree_t* e1, char* to_downto, tree_t* e2);
void end_for_gencode(int l, tree_t* var, char* to_downto);

void assignment_gencode(tree_t* n);
void call_procedure(tree_t* n);
void call_function(tree_t* n);
char* var_to_assembly(char* name);
void grab_nonlocal_var(char* name);
void gencode(tree_t* n);

#endif
