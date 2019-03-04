/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 17:36:29 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/02 19:37:13 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

t_queue	*init_queue(t_room *actual, t_room *room)
{
	t_queue	*new;

	if (!(new = (t_queue *)malloc(sizeof(t_queue))))
		return (NULL);
	new->next = NULL;
	new->room = actual;
	while (room)
	{
		room->i = 0;
		room = room->next;
	}
	actual->i = 1;
	return (new);
}

t_queue	*enqueue(t_queue *queue, t_room *room)
{
	t_queue	*new;
	int i;

	i = 0;
	while (i < room->nb_links)
	{
		if (!room->links[i]->i)
		{
			if (!(new = (t_queue *)malloc(sizeof(t_queue))))
				return (NULL);
			queue->next = new;
			new->next = NULL;
			new->room = room->links[i];
			new->room->i = 1;
			queue = queue->next;
		}
		i++;
	}
	return (queue);
}

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
}

int		bfs(t_infos infos, t_room *room)
{
	int		i;
	t_queue *queue;
	t_queue	*begin;
	t_queue	*tmp;

	i = 0;
	begin = init_queue(infos.start, room);
	queue = enqueue(begin, begin->room);
	while (begin)
	{
		print_queue(begin);
		tmp = begin;
		if ((begin = begin->next))
			queue = enqueue(queue, begin->room);
		free(tmp);
	}
	return (0);
}
