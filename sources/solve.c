/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 19:12:07 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/22 10:57:26 by tle-dieu         ###   ########.fr       */
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

int		assign_paths(t_lemin *l, char **flow)
{
	t_room *room;
	int j;
	int i;

	j = 0;
	room = l->room;
	ft_printf("{rgb(12,231,58)}NEW PATHS{reset}\n");
	while (j < l->start->nb_links)
	{
		if (flow[l->start->id][l->start->links[j]->id] == 1)
		{
			l->start->links[j]->from = l->start;
			room = l->start->links[j];
			while (room != l->end)
			{
				i = 0;
				while (i < room->nb_links && flow[room->id][room->links[i]->id] != 1)
					i++;
				if (i == room->nb_links)
					return (0);
				room->path = room->flow;
				room->to = room->links[i];
				if (room->links[i] != l->end)
					room->links[i]->from = room;
				room = room->links[i];
			}
		}
		j++;
	}
	return (1);
}

int comp_graph(t_lemin *l, int tlen, int max_flow, char **flow)
{
	int len;
	int	tmp;
	int ant_total;
	int ant;
	int i;
	int j;

	j = 0;
	i = 0;
	tmp = tlen;
	ant_total = l->ant;
	ft_printf("{rgb(12,231,58)}len total: %d\n{reset}", tlen);
	while (j < l->start->nb_links)
	{
		if (l->start->links[j]->flow)
		{
			len = l->start->links[j]->flow;
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
		l->flow = max_flow;
		l->tlen = tmp;
		l->steps = (long)ant + len;
		assign_paths(l, flow);
	}
	else
		ft_printf("{#ff3333}BAD PATHS{reset}\n");
	return (1);
}

int		new_paths(t_lemin *l, char **flow, int max_flow)
{
	int i;
	int j;
	int tlen;
	int len;
	t_room *room;

	j = 0;
	tlen = 0;
	room = l->room;
	while (room)
	{
		room->flow = 0;
		room = room->next;
	}
	while (j < l->start->nb_links)
	{
		if (flow[l->start->id][l->start->links[j]->id] == 1)
		{
			l->start->links[j]->from = l->start;
			len = 0;
			room = l->start->links[j];
			while (room != l->end)
			{
				i = 0;
				while (i < room->nb_links)
				{
					if (flow[room->id][room->links[i]->id] == 1)
					{
						len++;
						room->flow = 1;
						room = room->links[i];
						break ;
					}
					i++;
				}

			}
			tlen += len;
			l->start->links[j]->flow = len;
		}
		j++;
	}
	ft_printf("{rgb(251,196,15)}number of path: %d\n{reset}", max_flow);
	return (comp_graph(l, tlen, max_flow, flow));
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
		check_block(l, flow);
		if (!(new_paths(l, flow, max_flow)))
			break ;
		verif_path(l);
		/* print_flow(l, flow); */
	}
	ft_printf("{rgb(251,196,15)}best path: %ld\nnb de bfs: %d\n{reset}", l->steps, max_flow);
	return (1);
}
