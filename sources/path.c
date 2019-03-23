/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 14:13:47 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/23 21:21:19 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	assign_path(t_lemin *l, char **flow, t_room *room)
{
	int i;

	while (room != l->end)
	{
		i = 0;
		while (i < room->nb_links)
		{
			if (flow[room->id][room->links[i]->id] == 1)
			{
				room->path = room->flow;
				room->to = room->links[i];
				if (room->links[i] != l->end)
					room->links[i]->from = room;
				room = room->links[i];
				break ;
			}
			i++;
		}
	}
}

static int	assign_graph(t_lemin *l, char **flow)
{
	t_room	*room;
	int		j;

	j = 0;
	room = l->room;
	while (j < l->start->nb_links)
	{
		if (flow[l->start->id][l->start->links[j]->id] == 1)
		{
			l->start->links[j]->from = l->start;
			assign_path(l, flow, l->start->links[j]);
		}
		j++;
	}
	return (1);
}

static int	comp_graph(t_lemin *l, int tlen, int max_flow, char **flow)
{
	int ret;

	if ((ret = get_steps(l, max_flow, tlen)) >= 1)
	{
		l->flow = max_flow;
		l->tlen = tlen;
		l->steps = ret;
		assign_graph(l, flow);
	}
	return (ret != -1);
}

static int	len_path(t_lemin *l, char **flow, int j)
{
	t_room	*room;
	int		i;
	int		len;

	len = 0;
	l->start->links[j]->from = l->start;
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
	return (len);
}

int			new_graph(t_lemin *l, char **flow, int max_flow)
{
	int		j;
	int		tlen;
	t_room	*room;

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
			l->start->links[j]->flow = len_path(l, flow, j);
			tlen += l->start->links[j]->flow;
		}
		j++;
	}
	return (comp_graph(l, tlen, max_flow, flow));
}
