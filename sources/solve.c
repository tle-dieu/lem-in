/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 17:36:29 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/18 22:22:36 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

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

t_queue	*enqueue(t_lemin *l, t_queue *queue, t_room *room, char **flow)
{
	int i;
	int change;

	i = 0;
	change = 0;
	while (i < room->nb_links)
	{
		if (!room->links[i]->i && !flow[room->id][room->links[i]->id] && (!room->flow || l->first))
		{
			/* ft_printf("ADD POS | name: %s i: %d flow: %d\n", room->links[i]->name, room->links[i]->i, flow[room->id][room->links[i]->id]); */
			change = 1;
			queue = add_queue(queue, room->links[i], room);
		}
		else
			/* ft_printf("NON ADD | name: %s i: %d flow: %d\n", room->links[i]->name, room->links[i]->i, flow[room->id][room->links[i]->id]); */
		++i;
	}
	i = 0;
	if (!change)
		while (i < room->nb_links)
		{
			if (room->links[i] != l->start && room->prev != room->links[i] && flow[room->id][room->links[i]->id] < 0)
			{
				/* ft_printf(" ADD NEG | name: %s i: %d flow: %d\n", room->links[i]->name, room->links[i]->i, flow[room->id][room->links[i]->id]); */
				l->first = 1;
				queue = add_queue(queue, room->links[i], room);
			}
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
	ft_printf("\n");
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

int     bfs(t_lemin *l, char **flow)
{
	t_queue *queue;
	t_queue *begin;
	t_queue *tmp;

	l->first = 0;
	begin = init_queue(l);
	queue = enqueue(l, begin, begin->room, flow);
	while (begin)
	{
		/* print_queue(begin); */
		tmp = begin;
		if (!(begin = begin->next) || (begin->room == l->end))
		{
			free(tmp);
			break;
		}
		queue = enqueue(l, queue, begin->room, flow);
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
			return (NULL);
		i = 0;
		while (i < l->nb_room)
			flow[j][i++] = 0;
		j++;
	}
	return (flow);
}

int comp_graph(t_lemin *l, int tlen, int max_flow)
{
	int len;
	t_room *room;
	int ant_total;
	int ant;
	int i;
	int j;

	j = 0;
	i = 0;
	ant_total = l->ant;
	ft_printf("{rgb(12,231,58)}len total: %d\n{reset}", tlen);
    while (j < l->start->nb_links)
    {
		/* ft_printf("path: %s i: %d\n", l->start->links[j]->name, l->start->links[j]->i); */
        if (l->start->links[j]->i)
        {
			len = l->start->links[j]->i;
			if ((ant = ((long)ant_total + tlen) / (max_flow - i) - len) <= 0)
			{
				ft_printf("{#ff3333}ERROR PATH UNUSED !{reset}\n");
				return (0);
			}
			tlen -= len;
			ant_total -= ant;
			ft_printf("{rgb(0,188,218)}--chemin %s--\n{rgb(0,188,218)}len: {reset}%d {rgb(0,188,218)}ant: {reset}%d {rgb(0,188,218)}reste: {reset}%d\n", l->start->links[j]->name, len, ant, ant_total);
			i++;
        }
        j++;
    }
	ft_printf("{rgb(251,196,15)}nb instructions: {reset}%ld old: %ld\n", (long)ant + len, l->steps);
	if (l->steps == -1 || (long)ant + len < l->steps)
	{
		ft_printf("{rgb(12,231,58)}NEW PATHS{reset}\n");
		l->flow = max_flow;
		room = l->room;
		l->steps = (long)ant + len;
		while (room)
		{
			room->path = room->i;
			room = room->next;
		}
	}
	else
		ft_printf("{#ff3333}BAD PATHS{reset}\n");
	return (1);
}

int		get_new_paths(t_lemin *l, char **flow, int max_flow)
{
	t_room *room;
	int j;
	int i;
	int tlen;
	int len;

	j = 0;
	tlen = 0;
	room = l->room;
	while (room)
	{
		room->i = 0;
		room->flow = 0;
		room = room->next;
	}
	while (j < l->start->nb_links)
	{
		if (flow[l->start->id][l->start->links[j]->id] == 1)
		{
			len = 0;
			room = l->start->links[j];
			ft_printf("{#ff3333}${reset}%s {#00ffbf}=> {reset}", l->start->name);
			while (room != l->end)
			{
				i = 0;
				ft_printf("%s {#00ffbf}=> {reset}", room->name);
				while (i < room->nb_links)
				{
					if (flow[room->id][room->links[i]->id] == 1)
					{
						len++;
						room->links[i]->i = 1;
						room->flow = 1;
						room = room->links[i];
						break ;
					}
					i++;
				}
			}
			tlen += len;
			l->start->links[j]->i = len;
			room->flow = 1;
			ft_printf("%s\n", l->end->name);
		}
		j++;
	}
	ft_printf("{rgb(251,196,15)}number of path: %d\n{reset}", max_flow);
	return (comp_graph(l, tlen, max_flow));
}

int		edmonds_karp(t_lemin *l)
{
	char	**flow;
	int		max_flow;

	l->flow = 0;
	l->steps = -1;
	max_flow = 0;
	flow = init_flow(l);
	while (bfs(l, flow))
	{
		max_flow++;
		if (!get_new_paths(l, flow, max_flow))
			break ;
		/* print_flow(l, flow); */
	}
	ft_printf("{rgb(251,196,15)}best path: %ld\nnb de bfs: %d\n{reset}", l->steps, max_flow);
	return (1);
}
