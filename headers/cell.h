#ifndef CELL_H
#define CELL_H

typedef struct s_cell
{
	int value;
	int nb_levels;
	struct s_cell **levels;
} t_cell; 

t_cell* create_cell(int val, int  nb_level);
#endif