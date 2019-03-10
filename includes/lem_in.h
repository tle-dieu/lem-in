/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 12:07:42 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/10 19:30:30 by tle-dieu         ###   ########.fr       */
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
	struct s_room	*prev;
	int				id;
	int				i;
	struct s_room	**links;
	int				nb_links;
	struct s_room	*next;
}				t_room;

typedef struct	s_way
{
	int				len;
	t_room			**rooms;
	struct s_way	*next;

}				t_way;

typedef struct	s_pipe
{
	int				from;
	int				to;
	struct s_pipe	*next;
}				t_pipe;

typedef struct	s_lemin
{
	int				ant;
	t_room			*start;
	t_room			*end;
	t_room			*room;
	t_room			**tab;
	int				nb_room;
}				t_lemin;

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
int				atoi_parsing(char const *s);
int				parse_infos(t_lemin *l, t_pipe **pipe);
int				edmonds_karp(t_lemin *l);
#endif
