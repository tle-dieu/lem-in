/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:58:45 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/22 14:19:04 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lem_in.h"

t_queue			*init_queue(t_lemin *l, t_room *begin)
{
	t_room	*room;
	t_queue	*new;

	if (!(new = (t_queue *)malloc(sizeof(t_queue))))
		return (NULL);
	new->next = NULL;
	new->room = begin;
	room = l->room;
	while (room)
	{
		room->i = 0;
		room->prev = NULL;
		room->back = 0;
		room = room->next;
	}
	begin->i = 1;
	return (new);
}

static t_queue	*add_queue(t_queue *queue, t_room *actual, t_room *room)
{
	t_queue *new;

	if (!(new = (t_queue *)malloc(sizeof(t_queue))))
		return (NULL);
	queue->next = new;
	new->next = NULL;
	new->room = actual;
	new->room->i = 1;
	actual->prev = room;
	return (queue->next);
}

static int		get_back(t_room *room, char **flow)
{
	int i;

	i = 0;
	while (i < room->nb_links)
	{
		if (flow[room->id][room->links[i]->id] == -1)
			return (1);
		i++;
	}
	return (0);
}

static t_queue	*enqueue(t_queue *queue, t_room *room, char **flow)
{
	int i;

	i = 0;
	while (i < room->nb_links)
	{
		if (!room->links[i]->i && !flow[room->id][room->links[i]->id]
		&& (!room->links[i]->flow || get_back(room->links[i], flow))
		&& (!room->flow || room->back))
		{
			if (!(queue = add_queue(queue, room->links[i], room)))
				return (NULL);
		}
		else if (!room->links[i]->i && flow[room->id][room->links[i]->id] == -1)
		{
			room->links[i]->back = 1;
			if (!(queue = add_queue(queue, room->links[i], room)))
				return (NULL);
		}
		++i;
	}
	return (queue);
}

int				bfs(t_lemin *l, char **flow)
{
	t_queue *queue;
	t_queue *begin;
	t_queue *tmp;

	if (!(begin = init_queue(l, l->start)))
		return (0);
	if (!(queue = enqueue(begin, begin->room, flow)))
		return (free_queue(begin));
	while (begin)
	{
		tmp = begin;
		if (!(begin = begin->next) || (begin->room == l->end))
		{
			free(tmp);
			break ;
		}
		if (!(queue = enqueue(queue, begin->room, flow)))
			return (free_queue(begin));
		free(tmp);
	}
	return (augmenting_path(l, flow));
}
