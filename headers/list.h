#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include "cell.h"

typedef struct s_list
{
    t_cell **heads;
    int max_levels;
} t_list; 

t_list* create_list(int max_levels);

void insert_cell(t_list* list, t_cell* cell);

void display_list(t_list* list, int level);

void display_all(t_list* list);

void display_list_aligned(t_list* list, int level);

void sorted_insert(t_list* list);

#endif