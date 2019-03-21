/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 19:12:07 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/21 16:08:57 by tle-dieu         ###   ########.fr       */
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

void	flow_paths(t_lemin *l, char **flow)
{
	int i;
	int j;
	t_room *room;

	j = 0;
	while (j < l->start->nb_links)
	{
		if (flow[l->start->id][l->start->links[j]->id])
		{
			room = l->start->links[j];
			while (room != l->end)
			{
				i = 0;
				while (i < room->nb_links && (flow[room->id][room->links[i]->id] != 1))
					++i;
				room->flow = 1;
				room = room->links[i];
			}
		}
		j++;
	}
}

void	check_block(t_lemin *l, char **flow)
{
	int i;
	int j;
	t_room *room;


	room = l->room;
	while (room)
	{
		/* ft_printf("{#32ee03}name: {reset}%s {#32ee03}flow: {reset}%d\n", room->name, room->flow); */
		room->i = 0;
		room = room->next;
	}
	room = l->start;
	j = 0;
	while (j < l->start->nb_links)
	{
		if (flow[l->start->id][l->start->links[j]->id])
		{
			room = l->start->links[j];
			while (room != l->end)
			{
				i = 0;
				while (i < room->nb_links)
				{
					if (flow[room->id][room->links[i]->id] == 1)
					{
						if (room->i)
						{
							ft_printf("{#ff3333}BLOCK {reset}%s\n", room->name);
							exit(1);
						}
						room->i = 1;
						room = room->links[i];
						break ;
					}
					++i;
				}
			}
		}
		j++;
	}
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
		flow_paths(l, flow);
		check_block(l, flow);
		/* print_flow(l, flow); */
	}
	ft_printf("{rgb(251,196,15)}best path: %ld\nnb de bfs: %d\n{reset}", l->steps, max_flow);
	return (1);
}
