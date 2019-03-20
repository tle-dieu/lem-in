/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 12:07:42 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/20 16:38:39 by tle-dieu         ###   ########.fr       */
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
	char			path;
	int				id;
	struct s_room	*prev_p;
	struct s_room	*next_p;
	struct s_room	*prev;
	int				flow;
	int				i;
	struct s_room	**links;
	int				nb_links;
	struct s_room	*next;
}				t_room;

typedef struct	s_pipe
{
	int				from;
	int				to;
	struct s_pipe	*next;
}				t_pipe;

typedef struct	s_lemin
{
	int				first;
	long 			steps;
	int				flow;
	int				ant;
	int				tlen;
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

void				finish(t_file *file, char *message, int error);
int					atoi_parsing(char const *s);
int					parse_infos(t_lemin *l, t_pipe **pipe);
int					edmonds_karp(t_lemin *l);
void				send_ants(t_lemin *l);
t_queue				*init_queue(t_lemin *l, t_room *begin);


/* DEBUG */
void				print_flow(t_lemin *l, char **tab);
void				print_queue(t_queue *print);
void				print_room(t_lemin *l);
void				print_pipe(t_pipe *pipe);
void				print_graph(t_room **tab, t_lemin *l);
void				verif_path(t_lemin *l);
#endif
