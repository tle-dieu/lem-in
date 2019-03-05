/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 12:07:42 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/04 17:22:18 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# define BS_LEMIN 1000

typedef struct	s_room
{
	int				x;
	int				y;
	char			*name;
	int				place;
	int				nb_links;
	int				id;
	int				i;
	int				dist;
	int				lvl;;
	struct s_room	**links;
	struct s_room	*next;
}				t_room;

typedef struct	s_pipe
{
	int				from;
	int				to;
	int				len;
	struct s_pipe	*next;
}				t_pipe;

typedef struct	s_infos
{
	int				ant;
	t_room			*start;
	t_room			*end;
}				t_infos;

typedef struct s_queue
{
	t_room			*room;
	struct	s_queue *next;
}				t_queue;

typedef struct	s_file
{
	char			**split;
	int				size;
	int				len;
	char			*str;
}				t_file;

void			finish(t_file *file, char *message, int error);
int				parse_infos(t_room **room, t_pipe **pipe, int *ant, t_file *file);
int				atoi_parsing(char const *s);
int				bfs(t_infos infos, t_room *room);

#endif
