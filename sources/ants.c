/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 17:50:30 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/20 04:50:32 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

t_queue *next_room(t_lemin *l, t_queue *queue, t_room *room)
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
			if (room != l->end)
				break ;
		}
		i++;
	}
	return (queue);
}

t_queue	*queue_ant(t_lemin *l)
{
	t_queue	*queue;
	t_queue	*actual;
	t_queue	*begin;

	begin = init_queue(l, l->end);
	queue = next_room(l, begin, begin->room);
	actual = begin;
	while ((actual = actual->next))
		queue = next_room(l, queue, actual->room);
	return (begin);
}

void	print_link(t_room *room)
{
	while (room)
	{
		if (room->path)
			ft_printf("%s -> %s -> %s\n", room->links[0]->name, room->name, room->links[1]->name);
		room = room->next;
	}
}


int		*ants_by_path(t_room *start, int tlen, int max_flow, int ant_total)
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
			ant = ((long)ant_total + tlen) / (max_flow - i) - len;
			tlen -= len;
			ant_total -= ant;
			i++;
		}
		send[j++] = ant;
	}
	return (send);
}

void	send_ants(t_lemin *l)
{
	t_queue *queue;
	int		*send;

	queue = queue_ant(l);
	/* print_queue(queue); */
	/* print_link(l->room); */
	send = ants_by_path(l->start, l->tlen, l->flow, l->ant);
	(void)queue;
	(void)send;
}
