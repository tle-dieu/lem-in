/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 19:12:07 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/22 22:08:52 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

int		augmenting_path(t_lemin *l, char **flow)
{
	t_room *room;

	room = l->end;
	if (!room->prev)
		return (0);
	while (room->prev)
	{
		flow[room->id][room->prev->id]--;
		flow[room->prev->id][room->id]++;
		room = room->prev;
	}
	return (1);
}

char	**init_flow(t_lemin *l)
{
	char	**flow;
	int		i;
	int		j;

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
			flow[j][i++] = 0;
		j++;
	}
	return (flow);
}

long	get_steps(t_lemin *l, int max_flow, int tlen)
{
	int len;
	int ant_total;
	int ant;
	int i;
	int j;

	j = 0;
	i = 0;
	ant_total = l->ant;
	while (j < l->start->nb_links)
	{
		if (l->start->links[j]->flow)
		{
			len = l->start->links[j]->flow;
			if ((ant = ((long)ant_total + tlen) / (max_flow - i) - len) <= 0)
				return (-1);
			tlen -= len;
			ant_total -= ant;
			i++;
		}
		j++;
	}
	if (l->steps == -1 || (long)ant + len < l->steps)
		return ((long)ant + len);
	return (0);
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
		print_paths(l, flow);
		max_flow++;
		if (!(new_graph(l, flow, max_flow)))
			break ;
	}
	return (max_flow);
}
