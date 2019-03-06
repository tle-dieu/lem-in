/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 17:36:29 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/06 15:29:49 by matleroy         ###   ########.fr       */
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
	new->room->lvl = 0;
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
			new->room->lvl = room->lvl + 1;
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
	ft_printf("\n");
}

int		bfs(t_infos infos, t_room *room)
{
	int		lvl;
	t_queue *queue;
	t_queue	*begin;
	t_queue	*tmp;

	lvl = 0;
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

int get_ways(t_room *room, t_infos infos, int *way)
{
	int i;

	i = 0;
	ft_printf("{blue}=> {reset}%s ", room->name);
	room->i = 1;
	if (room->place == 2)
	{
		(*way)++;
		return (1);
	}
	while (i < room->nb_links)
	{
		if (room->links[i]->place == 2 || (!room->links[i]->i && (room->links[i]->lvl > room->lvl ||  room->links[i]->dist < room->dist)))
		{
			if (get_ways(room->links[i], infos, way))
				ft_printf("\n");
		}
		i++;
	}
	return (0);
}

int dfs(t_infos infos, t_room **tab)
{
	int way;
	int i;
	int j;

	i = 0;
	way = 0;
	while (i < infos.start->nb_links)
	{
		j = 0;
		while (tab[j])
			tab[j++]->i = 0;
		get_ways(infos.start->links[i], infos, &way);
		i++;
		ft_printf("\n");
	}
	ft_printf("{#ff3333}%d", way);
	return (42);
}










