/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 17:50:30 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/25 03:38:06 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

static t_queue	*add_paths(t_queue *queue, t_room *room)
{
	int		i;
	t_queue *new;

	i = 0;
	while (i < room->nb_links)
	{
		if (!room->links[i]->i && room->links[i]->path)
		{
			if (!(new = (t_queue *)malloc(sizeof(t_queue))))
				return (NULL);
			queue->next = new;
			new->room = room->links[i];
			new->room->i = 1;
			new->next = NULL;
			queue = queue->next;
		}
		i++;
	}
	return (queue);
}

static t_queue	*add_room_ant(t_lemin *l, t_queue *queue, t_room *room)
{
	t_queue *new;

	if (!room->from)
		return (queue);
	if (room->from != l->start)
	{
		if (!(new = (t_queue *)malloc(sizeof(t_queue))))
			return (NULL);
		queue->next = new;
		new->room = room->from;
		new->room->i = 1;
		new->next = NULL;
		return (queue->next);
	}
	return (queue);
}

t_queue			*create_queue_ant(t_lemin *l)
{
	t_queue	*queue;
	t_queue	*actual;
	t_queue	*begin;

	queue = NULL;
	if (!(begin = init_queue(l, l->end)))
		return (NULL);
	if (!(queue = add_paths(begin, begin->room)))
	{
		free_queue(begin);
		return (NULL);
	}
	actual = begin;
	while ((actual = actual->next))
		if (!(queue = add_room_ant(l, queue, actual->room)))
		{
			free_queue(begin);
			return (NULL);
		}
	return (begin);
}

int				*ants_by_path(t_room *start, int tlen, int max_flow, int tt_ant)
{
	int len;
	int ant;
	int *send;
	int i;
	int j;

	j = 0;
	i = 0;
	if (!(send = (int*)malloc(sizeof(int) * start->nb_links)))
		return (NULL);
	while (j < start->nb_links)
	{
		ant = 0;
		if (start->links[j]->path)
		{
			len = start->links[j]->path;
			ant = ((long)tt_ant + tlen) / (max_flow - i) - len;
			tlen -= len;
			tt_ant -= ant;
			i++;
		}
		send[j++] = ant;
	}
	return (send);
}
