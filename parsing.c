/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:00:33 by matleroy          #+#    #+#             */
/*   Updated: 2019/02/18 19:55:08 by tle-dieu         ###   ########.fr       */
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

int		get_room(t_room **room, t_pipe **pipe, char *line, int *room_opt)
{
	t_room	*new;

	/* ft_printf("room: %s\n", line); */
	if (*pipe || !(new = (t_room*)malloc(sizeof(t_room))))
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
	new->next = *room;
	*room = new;
	check_room(*room);
	return (0);
}

/* int		check_pipe_name(t_room *room, t_pipe *pipe) */
/* { */
/* 	int cmp; */
/* 	t_room *begin; */

/* 	cmp = 0; */
/* 	begin = room; */
/* 	while (room) */
/* 	{ */
/* 		if (ft_strcmp(room->name, pipe->begin) || ft_strcmp */
/* 	} */
/* } */

int		get_pipe(t_pipe **pipe, char *line)
{
	t_pipe	*new;
	char	*tmp;

	/* ft_printf("pipe: %s\n", line); */
	if (!(new = (t_pipe*)malloc(sizeof(t_pipe))))
		return (1);
	new->end = NULL;
	new->begin = ft_strcdup(line, '-');
	if (new->begin && (tmp = ft_strchr(line, '-')))
	{
		new->next = *pipe;
		if ((new->end = ft_strdup(tmp + 1)))
			*pipe = new;
	}
	if (!new->end || !new->begin) //|| !check_pipe_name(*room, new))
	{
		free(new->end);
		free(new->begin);
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
	int		i;

	i = 0;
	line = NULL;
	room_opt = 0;
	error = 0;
	if (get_next_line(0, &line) != 1 || ((*ant = atoi_parsing(line)) <= 0))
		finish(line, "ERROR\n", 1);
	free(line);
	while (!error && get_next_line(0, &line) == 1)
	{
		if (!(i++ % 10000))
			ft_printf("+1\n");
		if (*line == '#')
		{
			if (*(line + 1) == '#')
				error = get_room_opt(line, &room_opt);
		}
		else if (!ft_strchr(line, '-'))
			error = get_room(room, pipe, line, &room_opt);
		else
			error = room_opt || *line == 'L' || get_pipe(pipe, line);
		free(line);
	}
	if (error)
		ft_printf("{#de5453}STOP !\n");
	return (0);
}
