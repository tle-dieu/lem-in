/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 12:07:42 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/25 03:38:13 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

typedef struct	s_room
{
	int				i;
	int				nb_links;
	int				path;
	int				id;
	int				flow;
	int				x;
	int				y;
	char			back;
	char			*name;
	struct s_room	*to;
	struct s_room	*from;
	struct s_room	*prev;
	struct s_room	**links;
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
	long			steps;
	int				flow;
	int				ant;
	int				tlen;
	int				nb_room;
	t_room			*start;
	t_room			*end;
	t_room			*room;
}				t_lemin;

typedef struct	s_queue
{
	t_room			*room;
	struct s_queue	*next;
}				t_queue;

typedef struct	s_file
{
	char			*line;
	struct s_file	*next;
}				t_file;

/*
** --------- PARSING ---------
*/

int					parse(t_lemin *l, t_pipe **pipe, t_file **file);

/*
** ---------- ROOM -----------
*/

int					get_room(t_lemin *l, char *line, int *room_opt);
void				reorder_room_id(t_room *room);

/*
** ---------- PIPE -----------
*/

int					get_pipe(t_pipe **pipe, t_room *room, char *line);
int					assign_pipe(t_room *room, t_pipe *pipe, int size);


/*
** ----------- BFS -----------
*/

int					bfs(t_lemin *l, char **flow);
t_queue				*init_queue(t_lemin *l, t_room *begin);

/*
** ----------- EK ------------
*/

int					edmonds_karp(t_lemin *l);
int					augmenting_path(t_lemin *l, char **flow);
long				get_steps(t_lemin *l, int max_flow, int tlen);

/*
** ---------- PATH -----------
*/

int					new_graph(t_lemin *l, char **flow, int max_flow);

/*
** ---------- FREE -----------
*/

int					free_pipe(t_pipe *pipe);
int					free_queue(t_queue *queue);
int					free_room(t_room *room);
int					free_tab(void **tab, int size);
int					free_file(t_file *file);

/*
** ---------- ANTS -----------
*/

t_queue				*create_queue_ant(t_lemin *l);
int					*ants_by_path(t_room *start, int tlen, int max_flow, int tt_ant);

/*
** ---------- SEND -----------
*/

int					send_ants(t_lemin *l, t_file *file);
int					start_to_end(t_lemin *l, t_file *file);

/*
** ---------- UTILS ----------
*/

int					error_finish(t_file *file, t_pipe *pipe,
t_room *room, char *message);
int					atoi_parsing(char const *s);
void				print_file(t_file *file);

/* DEBUG */
void				print_flow(t_lemin *l, char **tab);
void				print_queue(t_queue *print);
void				print_room(t_lemin *l);
void				print_pipe(t_pipe *pipe);
void				print_graph(t_room **tab, t_lemin *l);
void				verif_path(t_lemin *l);
void				print_paths(t_lemin *l, char **flow);
void				check_block(t_lemin *l, char **flow);
void				print_link(t_room *room);

//fichier debug a retirer
//verifier print a la fin et faire test lemin
#endif
