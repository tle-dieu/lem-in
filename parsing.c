/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:00:33 by matleroy          #+#    #+#             */
/*   Updated: 2019/02/17 22:09:00 by tle-dieu         ###   ########.fr       */
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

int		get_room(t_room **room, t_pipe **pipe, char *line, int *room_opt)
{
	t_room	*new;

	ft_printf("room: %s\n", line);
	if (*pipe || !(new = (t_room*)malloc(sizeof(t_room))))
		return (1);
	new->place = *room_opt;
	if (*room_opt)
		*room_opt = 0;
	if (!get_coord(new, ft_strchr(line, ' ')))
	{
		ft_printf("coord error\n");
		free(new);
		return (1);
	}
	new->name = ft_strcdup(line, ' '); //protection
	new->next = *room;
	*room = new;
	return (0);
}

int		get_pipe(t_pipe **pipe, char *line)
{
	t_pipe	*new;
	char	*tmp;

	ft_printf("pipe: %s\n", line);
	if (!(new = (t_pipe*)malloc(sizeof(t_pipe))))
		return (1);
	new->begin = ft_strcdup(line, '-');
	tmp = ft_strchr(line, '-');
	if (*tmp == '-')
		tmp++;
	new->end = ft_strdup(tmp);
	new->next = *pipe ? *pipe : NULL;
	*pipe = new;
	return (0);
}

int		get_room_opt(char *line, int *room_opt)
{
	if (*room_opt)
		return (1);
	if (!ft_strcmp("##end", line))
		*room_opt = 2;
	else if (!ft_strcmp("##start", line))
		*room_opt = 1;
	else
		return (1);
	return (0);
}

void	check_room(t_room *room)
{
	t_room *actual;
	t_room *next;

	while (room->next)
	{
		actual = room;
		next = actual->next;
		while (next)
		{
			if (!ft_strcmp(next->name, actual->name)
			|| (actual->x == next->x && actual->y == next->y))	
			{
				ft_printf("RM: {#de3030}%s X: %d Y: %d{reset}\n", next->name, next->x, next->y);
				actual->next = next->next;
				free(next->name);
				free(next);
			}
			else
				actual = actual->next;
			next = actual->next;
		}
		room = room->next;
	}
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
		else if (ft_strchr(line, ' '))
			error = get_room(room, pipe, line, &room_opt);
		else if (room_opt || *line == 'L' || !*line)
			error = 1;
		else
			error = get_pipe(pipe, line);
		free(line);
	}
	if (error)
		ft_printf("{#de5453}STOP !\n");
	return (0);
}
