#ifndef LEM_IN_H
# define LEM_IN_H
#include "libft.h"

typedef struct		s_room
{
	int				x;
	int				y;
	char			*name;
	struct s_room	*next;
}					t_room;

typedef struct		s_pipe
{
	char			*name;
	int				len;
	struct s_pipe	*next;
}					t_pipe;
int		parse_infos();
#endif
