/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 17:36:29 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/09 20:53:35 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

void	print_queue(t_queue *print)
{
	while (print)
	{
		if (print->next)
			ft_printf("%s {yellow}-> {reset}", print->room->name);
		else
			ft_printf("%s\n", print->room->name);
		print = print->next;
	}
	ft_printf("\n");
}

t_queue	*init_queue(t_lemin *l)
{
	t_room *room;
	t_queue	*new;

	if (!(new = (t_queue *)malloc(sizeof(t_queue))))
		return (NULL);
	new->next = NULL;
	new->room = l->start;
	room = l->room;
	while (room)
	{
		room->i = 0;
		room->prev = NULL;
		room = room->next;
	}
	l->start->i = 1;
	return (new);
}

t_queue	*enqueue(t_lemin *l, t_room ***matrix, t_queue *queue, t_room *room)
{
	t_queue	*new;
	int i;

	i = 0;
	while (i < l->nb_room)
	{
		if (matrix[room->id][i] && !matrix[room->id][i]->i)
		{
			if (!(new = (t_queue *)malloc(sizeof(t_queue))))
				return (NULL);
			queue->next = new;
			new->next = NULL;
			new->room = matrix[room->id][i];
			new->room->i = 1;
			new->room->prev = room;
			queue = queue->next;
		}
		i++;
	}
	return (queue);
}

void	create_path(t_lemin *l)
{
	t_room *room;

	room = l->end;
	while (room)
	{
		ft_printf("%s", room->name);
		if (room->prev)
			ft_printf(" {#00bfff}=> {reset}");
		room = room->prev;
	}
	ft_printf("\n");
}

int     bfs(t_lemin *l, t_room ***matrix)
{
	t_queue *queue;
	t_queue *begin;
	t_queue *tmp;

	begin = init_queue(l);
	queue = enqueue(l, matrix, begin, begin->room);
	while (begin)
	{
		print_queue(begin);
		tmp = begin;
		if (!(begin = begin->next) || (begin->room == l->end))
		{
			free(tmp);
			break;
		}
		queue = enqueue(l, matrix, queue, begin->room);
		free(tmp);
	}
	if (begin)
		create_path(l);
	return (0);
}
