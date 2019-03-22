/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:00:33 by matleroy          #+#    #+#             */
/*   Updated: 2019/03/22 23:26:14 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <fcntl.h>
#include <stdlib.h>

int		get_coord(t_room *new, char *line)
{
	char	x[11];
	int		i;

	if (!line || !*(++line))
		return (0);
	i = 0;
	while (i < 10 && line[i] && line[i] != ' ')
	{
		x[i] = line[i];
		i++;
	}
	x[i] = '\0';
	if ((new->x = atoi_parsing(x)) < 0)
		return (0);
	if (line[i] != ' ' || !line[i + 1] || (new->y = atoi_parsing(line + i + 1)) < 0)
		return (0);
	return (1);
}

void	check_room(t_lemin *l)
{
	t_room *actual;
	t_room *prev;

	prev = l->room;
	while (prev->next)
	{
		actual = prev->next;
		if (!ft_strcmp(actual->name, l->room->name)
		|| (l->room->x == actual->x && l->room->y == actual->y))
		{
			--l->nb_room;
			if (actual == l->start)
				l->start = NULL;
			else if (actual == l->end)
				l->start = NULL;
			prev->next = actual->next;
			free(actual->name);
			free(actual);
		}
		else
			prev = prev->next;
	}
}

int		get_room(t_lemin *l, char *line, int *room_opt)
{
	t_room	*new;

	++l->nb_room;
	if (!(new = (t_room*)malloc(sizeof(t_room))))
		return (1);
	if (!get_coord(new, ft_strchr(line, ' '))
	|| !(new->name = ft_strcdup(line, ' ')))
	{
		free(new);
		return (1);
	}
	if (*room_opt == 1 || *room_opt == 3)
	{
		l->start = new;
		--(*room_opt);
	}
	if (*room_opt == 2)
		l->end = new;
	*room_opt = 0;
	new->id = l->room ? l->room->id + 1 : 0;
	new->i = 0;
	new->path = 0;
	new->nb_links = 0;
	new->flow = 0;
	new->to = NULL;
	new->from = NULL;
	new->next = l->room;
	l->room = new;
	check_room(l);
	return (0);
}

int		check_pipe(t_room *room, t_pipe *pipe, char *from, char *to)
{
	t_pipe *new;
	t_pipe *actual;
	t_pipe *prev;
	t_room *room_from;
	t_room *room_to;

	prev = pipe;
	new = pipe;
	pipe->to = -1;
	pipe->from = -1;
	room_from = NULL;
	room_to = NULL;
	if (!from || !to)
		return (1);
	if (ft_strcmp(from, to))
	{
		while (room)
		{
			if (!ft_strcmp(room->name, from))
			{
				room_from = room;
				pipe->from = room->id;
				room->nb_links++;
			}
			else if (!ft_strcmp(room->name, to))
			{
				room_to = room;
				pipe->to = room->id;
				room->nb_links++;
			}
			room = room->next;
		}
		while (prev->next)
		{
			actual = prev->next;
			if ((new->to == actual->to && new->from == actual->from)
			|| (new->to == actual->from && new->from == actual->to))
			{
				room_to->nb_links--;
				room_from->nb_links--;
				prev->next = actual->next;
				free(actual);
				break ;
			}
			prev = prev->next;
		}
	}
	free(from);
	free(to);
	if (pipe->to == -1 || pipe->from == -1)
	{
		if (room_from)
			room_from->nb_links--;
		if (room_to)
			room_to->nb_links--;
		return (1);
	}
	return (0);
}

void	reorder_room(t_room *room)
{
	int i;

	i = -1;
	while (room)
	{
		room->id = ++i;
		room = room->next;
	}
}

int		get_pipe(t_pipe **pipe, t_room *room, char *line)
{
	t_pipe	*new;
	char	*tmp;
	char	*from;
	char	*to;

	if (!*pipe)
		reorder_room(room);
	if (ft_count_occ(line, '-') != 1 || !(new = (t_pipe*)malloc(sizeof(t_pipe))))
		return (1);
	to = NULL;
	from = ft_strcdup(line, '-');
	if (from && (tmp = ft_strchr(line, '-')))
	{
		new->next = *pipe;
		if ((to = ft_strdup(tmp + 1)))
			*pipe = new;
	}
	if (check_pipe(room, *pipe, from, to))
	{
		*pipe = (*pipe)->next;
		free(new);
	}
	return (0);
}

int		get_room_opt(char *line, int *room_opt)
{
	int new_opt;

	if (!ft_strcmp("##end", line))
		new_opt = 2;
	else if (!ft_strcmp("##start", line))
		new_opt = 1;
	else
		return (1); //peut etre pas une erreur si c'est ni ##start ni ##end
	if (*room_opt != new_opt && *room_opt != 3)
		*room_opt += new_opt;
	return (0);
}

int		add_line(char **line, t_file **actual, t_file **file)
{
	t_file	*new;

	*line = NULL;
	if (get_next_line(0, line) != 1)
		return (1);
	if (!(new = (t_file *)malloc(sizeof(t_file))))
	{
		free(line);
		return (0);
	}
	new->next = NULL;
	new->line = *line;
	if (!*file)
		*file = new;
	else
		(*actual)->next = new;
	*actual = new;
	return (0);
}

int		parse_graph(t_lemin *l, t_pipe **pipe, t_file **file, t_file *actual)
{
	int		error;
	int		room_opt;
	char	*line;

	error = 0;
	room_opt = 0;
	while (!error && !add_line(&line, &actual, file))
	{
		if (line[0] == '#')
		{
			if (line[1] == '#')
				error = get_room_opt(line, &room_opt);
		}
		else if (!ft_strchr(line, '-'))
			error = *pipe || get_room(l, line, &room_opt);
		else
			error = room_opt || line[0] == 'L' || get_pipe(pipe, l->room, line);
	}
	return (error);
}

void	parse_infos(t_lemin *l, t_pipe **pipe, t_file **file)
{
	char	*line;
	int		error;
	t_file	*actual;

	actual = NULL;
	while (!(error = add_line(&line, &actual, file)) && line[0] == '#')
	{
		if (line[1] == '#')
			finish(NULL, "COMMENT ERROR\n", 1); // a changer
	}
	if (error)
		finish(NULL, "NO ANT ERROR\n", 1); // a changer
	if ((l->ant = atoi_parsing(line)) <= 0)
		finish(NULL, "ANT ERROR\n", 1); // a changer
	if (parse_graph(l, pipe, file, actual))
		ft_printf("{#de5453}STOP !{reset}\n");
	print_file(*file);
}
