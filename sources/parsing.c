/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:00:33 by matleroy          #+#    #+#             */
/*   Updated: 2019/03/10 15:42:57 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <fcntl.h>
#include <stdlib.h>

int		get_coord(t_room *new, char *line)
{
	char *tmp_y;

	if (!line || !*(++line))
		return (0);
	if (!(tmp_y = ft_strchr(line, ' ')))
		return (0);
	*tmp_y++ = '\0';
	if (!*tmp_y || ((new->x = atoi_parsing(line)) < 0) || ((new->y = atoi_parsing(tmp_y)) < 0))
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

	/* ft_printf("room: %s\n", line); */
	++l->nb_room;
	if (!(new = (t_room*)malloc(sizeof(t_room))))
		return (1);
	if (!get_coord(new, ft_strchr(line, ' '))
	|| !(new->name = ft_strcdup(line, ' ')))
	{
		ft_printf("coord error\n");
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
	new->next = l->room;
	new->i = 0;
	new->nb_links = 0;
	new->links = NULL;
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
	if (from && to && ft_strcmp(from, to))
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
	return (pipe->to != -1 && pipe->from != -1);
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

	/* ft_printf("pipe: %s\n", line); */
	if (!*pipe)
		reorder_room(room);
	if (!(new = (t_pipe*)malloc(sizeof(t_pipe))))
		return (1);
	to = NULL;
	from = ft_strcdup(line, '-');
	if (from && (tmp = ft_strchr(line, '-')))
	{
		new->next = *pipe;
		if ((to = ft_strdup(tmp + 1)))
			*pipe = new;
	}
	if (!check_pipe(room, *pipe, from, to))
	{
		*pipe = (*pipe)->next;
		free(new);
		return (1);
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

int		parse_infos(t_lemin *l, t_pipe **pipe)
{
	int		room_opt;
	int		error;
	int		i;
	char	*line;

	i = 0;
	room_opt = 0;
	while ((error = get_next_line(0, &line)) == 1 && line[0] == '#' && line[1] != '#')
		free(line);
	if (error != 1)
		finish(NULL, "NO ANT ERROR\n", 1); // a changer
	if ((l->ant = atoi_parsing(line)) <= 0)
		finish(NULL, "ANT ERROR\n", 1); // a changer
	free(line);
	error = 0;
	while (!error && get_next_line(0, &line) == 1)
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
		free(line);
		line = NULL;
	}
	if (error)
		ft_printf("{#de5453}STOP !\n");
	return (0);
}
