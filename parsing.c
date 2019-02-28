/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:00:33 by matleroy          #+#    #+#             */
/*   Updated: 2019/02/28 13:04:01 by tle-dieu         ###   ########.fr       */
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

void	check_room(t_room *room)
{
	t_room *actual;
	t_room *prev;

	prev = room;
	while (prev->next)
	{
		actual = prev->next;
		if (room->place && ((actual->place == 3 || actual->place == room->place)))
			actual->place -= room->place; 
		if (!ft_strcmp(actual->name, room->name)
				|| (room->x == actual->x && room->y == actual->y))	
		{
			prev->next = actual->next;
			free(actual->name);
			free(actual);
		}
		else
			prev = prev->next;
	}
}

int		get_room(t_room **room, char *line, int *room_opt)
{
	t_room	*new;

	ft_printf("room: %s\n", line);
	if (!(new = (t_room*)malloc(sizeof(t_room))))
		return (1);
	new->place = *room_opt;
	if (*room_opt)
		*room_opt = 0;
	if (!get_coord(new, ft_strchr(line, ' '))
			|| !(new->name = ft_strcdup(line, ' ')))
	{
		ft_printf("coord error\n");
		free(new);
		return (1);
	}
	new->dist = 2147483647;
	new->id = *room ? (*room)->id + 1 : 0;
	new->nb_links = 0;
	new->next = *room;
	new->i = 0;
	*room = new;
	check_room(*room);
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

int		get_pipe(t_pipe **pipe, t_room *room, char *line)
{
	t_pipe	*new;
	char	*tmp;
	char	*from;
	char	*to;

	ft_printf("pipe: %s\n", line);
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

int		parse_infos(t_room **room, t_pipe **pipe, int *ant)
{
	char	*line;
	int		room_opt;
	int		error;

	line = NULL;
	room_opt = 0;
	error = 0;
	if (get_next_line(0, &line) != 1 || ((*ant = atoi_parsing(line)) <= 0))
		finish(line, "ERROR\n", 1);
	free(line);
	while (!error && get_next_line(0, &line) == 1)
	{
		if (*line == '#')
		{
			if (*(line + 1) == '#')
				error = get_room_opt(line, &room_opt);
		}
		else if (!ft_strchr(line, '-'))
			error = *pipe || get_room(room, line, &room_opt);
		else
			error = room_opt || *line == 'L' || get_pipe(pipe, *room, line);
		free(line);
	}
	if (error)
		ft_printf("{#de5453}STOP !\n");
	return (0);
}
