#pragma once

//initialises the list module (sets
//the global pointer pFirst to NULL.
void stack_init();

//Check if the list is emty or not.
//return value:
//	1 ... list is emty
//	0 ... list is not emty
int stack_emty();

//Delivers the number of list nodes.
int stack_size();

//Allocates a new list node in the
//memory and inserts the new list node.
//(with the given data) in the list,
//sorted by name.
//	1 ... new data successfully inserted
//	0 ... no memory available
int stack_push(void* p, int size);
//get data from first stack node
void* stack_front();

//Searches for the list node, given by the
//name and removes this list node.
//Parameter:	pName ... pointer to name
//return value:
//	1 ... data found, list node removed
//	0 ... data not found
int stack_pop();

//Removes all list nodes
int stack_remove();
void* stack_num(int num);

