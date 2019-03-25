/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 03:07:15 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/25 17:06:39 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

int			assign_pipe(t_room *room, t_pipe *pipe, int size)
{
	t_room	**tab;
	int		i;

	if (!(tab = (t_room **)malloc(sizeof(t_room *) * (size))))
		return (0);
	i = 0;
	while (room)
	{
		tab[i++] = room;
		if (size
		&& !(room->links = (t_room**)malloc(sizeof(t_room*) * room->nb_links)))
		{
			free(tab);
			return (0);
		}
		room = room->next;
	}
	while (pipe)
	{
		tab[pipe->from]->links[tab[pipe->from]->i++] = tab[pipe->to];
		tab[pipe->to]->links[tab[pipe->to]->i++] = tab[pipe->from];
		pipe = pipe->next;
	}
	free(tab);
	return (1);
}

static int	comp_pipe(t_pipe *prev, t_room *room_from, t_room *room_to)
{
	t_pipe *actual;
	t_pipe *new;

	new = prev;
	while ((actual = prev->next))
	{
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
	if (room_from && room_to)
	{
		room_from->nb_links++;
		room_to->nb_links++;
		return (0);
	}
	return (1);
}

static int	check_pipe(t_room *room, t_pipe *pipe, char *from, char *to)
{
	t_room *room_from;
	t_room *room_to;

	room_from = NULL;
	room_to = NULL;
	if (!ft_strcmp(from, to))
		return (1);
	while (room)
	{
		if (!ft_strcmp(room->name, from))
		{
			room_from = room;
			pipe->from = room->id;
		}
		else if (!ft_strcmp(room->name, to))
		{
			room_to = room;
			pipe->to = room->id;
		}
		room = room->next;
	}
	return (comp_pipe(pipe, room_from, room_to));
}

int			get_pipe(t_pipe **pipe, t_room *room, char *line)
{
	t_pipe	*new;
	char	*to;

	if (!*pipe)
		reorder_room_id(room);
	if (ft_count_occ(line, '-') != 1 || ft_strchr(line, ' ')
	|| !(new = (t_pipe*)malloc(sizeof(t_pipe))))
	{
		free(line);
		return (1);
	}
	to = ft_strchr(line, '-');
	*to++ = '\0';
	new->next = *pipe;
	*pipe = new;
	new->to = -1;
	new->from = -1;
	if (check_pipe(room, *pipe, line, to))
	{
		*pipe = (*pipe)->next;
		free(new);
	}
	free(line);
	return (0);
}
