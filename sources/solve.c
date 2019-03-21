/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 19:12:07 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/21 12:41:08 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

int get_path(t_lemin *l, char **flow)
{
	t_room	*room;

	room = l->end;
	ft_printf("\n");
	ft_printf("PATH\n");
	if (!room->prev)
		return (0); //a enlever
	ft_printf("end  {#00bfff}=> {reset}");
	while (room->prev)
	{
		flow[room->id][room->prev->id]--;
		flow[room->prev->id][room->id]++;
		ft_printf("%s", room->prev->name);
		if (room->prev->prev)
			ft_printf(" {#00bfff}=> {reset}");
		room = room->prev;
	}
	ft_printf("\n");
	return (1);
}

t_queue	*init_queue(t_lemin *l, t_room *begin)
{
	t_room *room;
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
		room = room->next;
	}
	begin->i = 1;
	return (new);
}

t_queue *add_queue(t_queue *queue, t_room *actual, t_room *room)
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

t_queue *enqueue(t_queue *queue, t_room *room, char **flow)
{
	int i;

	i = 0;
	while (i < room->nb_links)
	{
		if (!room->links[i]->i && flow[room->id][room->links[i]->id] < 1)
		{
			if (!(queue = add_queue(queue, room->links[i], room)))
				return (NULL);// rendre les if plus propres
		}
		++i;
	}
	return (queue);
}

int		free_queue(t_queue *queue)
{
	t_queue *next;

	while (queue)
	{
		next = queue->next;
		free(queue);
		queue = next;
	}
	return (0);
}

int     bfs(t_lemin *l, char **flow)
{
	t_queue *queue;
	t_queue *begin;
	t_queue *tmp;

	if (!(begin = init_queue(l, l->start)))
	{
		ft_printf("error init queue\n");
		return (0);
	}
	if (!(queue = enqueue(begin, begin->room, flow)))
	{
		ft_printf("error start enqueue\n");
		return (free_queue(begin));
	}
	while (begin)
	{
		/* print_queue(begin); */
		tmp = begin;
		if (!(begin = begin->next) || (begin->room == l->end))
		{
			free(tmp);
			break;
		}
		if (!(queue = enqueue(queue, begin->room, flow)))
		{
			ft_printf("error enqueue\n");
			return (free_queue(begin));
		}
		free(tmp);
	}
	return (get_path(l, flow));
}

char	**init_flow(t_lemin *l)
{
	char **flow;
	int	i;
	int j;

	j = 0;
	if (!(flow = (char **)malloc(sizeof(char*) * l->nb_room)))
		return (NULL);
	while (j < l->nb_room)
	{
		if (!(flow[j] = (char *)malloc(sizeof(char) * l->nb_room)))
		{
			while (j--)
				free(flow[j]);
			free(flow);
			return (NULL);
		}
		i = 0;
		while (i < l->nb_room)
			flow[j][i++] = 0; //memset
		j++;
	}
	return (flow);
}
int		edmonds_karp(t_lemin *l)
{
	char	**flow;
	int		max_flow;

	max_flow = 0;
	if (!(flow = init_flow(l)))
		return (0);
	while (bfs(l, flow))
	{
		max_flow++;
		print_paths(l, flow);
		/* if (!get_new_paths(l, flow, max_flow)) */
		/* break ; */
		/* print_flow(l, flow); */
	}
	ft_printf("{rgb(251,196,15)}best path: %ld\nnb de bfs: %d\n{reset}", l->steps, max_flow);
	return (1);
}
