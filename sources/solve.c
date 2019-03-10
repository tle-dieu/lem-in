/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 17:36:29 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/10 13:58:31 by tle-dieu         ###   ########.fr       */
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

t_queue *add_queue(t_queue *queue, t_room *actual, t_room *room)
{
	t_queue *new;

	if (!(new = (t_queue *)malloc(sizeof(t_queue))))
		return (NULL);
	queue->next = new;
	new->next = NULL;
	new->room = actual;
	new->room->i = 1;
	new->room->prev = room;
	return (queue->next);
}

t_queue	*enqueue(t_lemin *l, t_room ***matrix, t_queue *queue, t_room *room, char **flow)
{
	int i;
	int change;

	i = 0;
	change = 0;
	while (i < l->nb_room)
	{
		if (matrix[room->id][i] && !matrix[room->id][i]->i && !flow[room->id][i])
		{
			change = 1;
			queue = add_queue(queue, matrix[room->id][i], room);
		}
		++i;
	}
	i = 0;
	if (!change)
		while (i < l->nb_room)
		{
			if (matrix[room->id][i] && !matrix[room->id][i]->i && flow[room->id][i] < 0)
				queue = add_queue(queue, matrix[room->id][i], room);
			++i;
		}
	return (queue);
}

int get_path(t_lemin *l, char **flow)
{
	int		new_flow;
	t_room	*room;

	room = l->end;
	new_flow = 0;
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
		++new_flow;
	}
	ft_printf("\n");
	return (new_flow);
}

int     bfs(t_lemin *l, t_room ***matrix, char **flow)
{
	t_queue *queue;
	t_queue *begin;
	t_queue *tmp;

	begin = init_queue(l);
	queue = enqueue(l, matrix, begin, begin->room, flow);
	while (begin)
	{
		/* print_queue(begin); */
		tmp = begin;
		if (!(begin = begin->next) || (begin->room == l->end))
		{
			free(tmp);
			break;
		}
		queue = enqueue(l, matrix, queue, begin->room, flow);
		free(tmp);
	}
	return (get_path(l, flow));
}

void	print_flow(char **tab)
{
	int j;
	int i;

	j = 0;
	while (j < 8)
	{
		i = 0;
		while (i < 8)
			ft_printf("%2d ", (int)tab[j][i++]);
		ft_printf("\n");
		j++;
	}
}

char	**init_ek(t_lemin *l)
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
			return (NULL);
		i = 0;
		while (i < l->nb_room)
			flow[j][i++] = 0;
		j++;
	}
	return (flow);
}

int		edmonds_karp(t_lemin *l, t_room ***matrix __attribute__((unused)))
{
	char **flow;
	int		i;

	flow = init_ek(l);
	i = 0;
	while (bfs(l, matrix, flow))
	{
		i++;
		/* print_flow(flow); */
	}
	ft_printf("bfs: %d\n", i);
	return (1);
}
