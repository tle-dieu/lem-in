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

typedef struct		s_pipe
{
	char			*begin;
	char			*end;
	int				len;
	struct s_pipe	*next;
}					t_pipe;

int parse_infos(t_room **room, t_pipe **pipe, int *ant);
#endif
