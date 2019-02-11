#ifndef LEM_IN_H
# define LEM_IN_H
#include "libft.h"

typedef struct	s_room
{
	int			x;
	int			y;
	char		*name;
}				t_room;

typedef struct s_pipe
{
	char *name;
	int len;
}				t_pipe;
int		parse_infos();
#endif
