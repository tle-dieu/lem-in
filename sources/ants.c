/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 17:50:30 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/20 16:38:21 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

t_queue *end_room(t_queue *queue, t_room *room)
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

t_queue *next_room(t_lemin *l, t_queue *queue, t_room *room)
{
	t_queue *new;

	if (!room->prev_p)
	{
		ft_printf("name: %s path: %d\n", room->name, room->path);
		return (queue);
	}
	if (room->prev_p != l->start)
	{
		if (!(new = (t_queue *)malloc(sizeof(t_queue))))
			return (NULL);
		queue->next = new;
		new->room = room->prev_p;
		new->room->i = 1;
		new->next = NULL;
		return (queue->next);
	}
	return (queue);
}

t_queue	*queue_ant(t_lemin *l)
{
	t_queue	*queue;
	t_queue	*actual;
	t_queue	*begin;

	begin = init_queue(l, l->end);
	queue = end_room(begin, begin->room);
	actual = begin;
	while ((actual = actual->next))
	{
		/* print_queue(begin); */
		queue = next_room(l, queue, actual->room);
	}
	return (begin);
}

void	print_link(t_room *room)
{
	while (room)
	{
		if (room->path)
			ft_printf("%s -> %s -> %s    %d\n", room->prev_p->name, room->name, room->next_p->name, room->path);
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

void	push_ant(t_queue *queue)
{
	while (queue)
	{
		if (queue->room->i)
		{
			queue->room->next_p->i++;
			queue->room->i--;
			queue->room->next_p->id = queue->room->id;
			/* ft_printf("L%d-%s ", queue->room->id, queue->room->next_p->name); */
		}
		queue = queue->next;
	}
}

void	send_ants(t_lemin *l)
{
	t_queue *queue;
	t_room	*room;
	int		*send;
	int		i;
	int		ant;

	verif_path(l);
	queue = queue_ant(l);
	print_queue(queue);
	/* print_link(l->room); */
	send = ants_by_path(l->start, l->tlen, l->flow, l->ant);
	room = l->room;
	while (room)
	{
		room->i = 0;
		room = room->next;
	}
	ant = 0;
	while (l->end->i != l->ant)
	{
		i = 0;
		push_ant(queue->next);
		while (i < l->start->nb_links)
		{
			if (send[i])
			{
				send[i]--; 
				++ant;
				/* ft_printf("L%d-%s ", ant, l->start->links[i]->name); */
				l->start->links[i]->i++;
				l->start->links[i]->id = ant;
			}
			i++;
		}
		/* ft_printf("\n"); */
		/* ft_printf("\nend: %d start: %d ant: %d\n", l->end->i, l->start->i, l->ant); */
	}
}
