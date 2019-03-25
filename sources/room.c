/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 03:03:29 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/25 03:12:27 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

void		reorder_room_id(t_room *room)
{
	int i;

	i = -1;
	while (room)
	{
		room->id = ++i;
		room = room->next;
	}
}

static int	get_coord(t_room *new, char *line)
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

static void	check_room(t_lemin *l)
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

static void	init_room(t_lemin *l, t_room *new)
{
	new->id = l->room ? l->room->id + 1 : 0;
	new->i = 0;
	new->path = 0;
	new->nb_links = 0;
	new->flow = 0;
	new->to = NULL;
	new->from = NULL;
	new->links = NULL;
	new->next = l->room;
	l->room = new;
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
	init_room(l, new);
	check_room(l);
	return (0);
}
