#ifndef LEM_IN_H
# define LEM_IN_H

#include "libft.h"

typedef struct		s_room
{
	int				x;
	int				y;
	char			*name;
	int				place;
	int				status;
	struct s_room	*next;
}					t_room;

typedef struct		s_pipe
{
	char			*begin;
	char			*end;
	int				len;
	struct s_pipe	*next;
}					t_pipe;

void    finish(char *line, char *message, int error);
int		parse_infos(t_room **room, t_pipe **pipe, int *ant);
int		atoi_parsing(char const *s);

#endif
