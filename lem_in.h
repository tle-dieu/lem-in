#ifndef LEM_IN_H
# define LEM_IN_H
#include "libft.h"

typedef struct		s_room
{
	int				x;
	int				y;
	char			*name;
	char			*place;
	int				status;
	int				id;
	struct s_room	*next;
}					t_room;

typedef struct 		s_matrice
{
	void			***content;
	int				size;
}					t_matrice;

typedef struct		s_pipe
{
	char			*begin;
	char			*end;
	int				len;
	struct s_pipe	*next;
}					t_pipe;

typedef struct		s_way
{
	t_room			*room;
	struct s_way	*next;
}					t_way;

typedef struct		s_ways
{
	t_way			*way;
	struct s_way	*next;
}					t_ways;

t_matrice *parse_infos(t_room **room, t_pipe **pipe, int *ant, t_matrice *matrice);
int get_ways(t_matrice *matrice, t_ways **ways);

#endif
