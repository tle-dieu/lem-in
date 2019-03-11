/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 17:36:29 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/11 14:35:26 by tle-dieu         ###   ########.fr       */
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

t_queue	*enqueue(t_queue *queue, t_room *room, char **flow)
{
	int i;
	int change;

	i = 0;
	change = 0;
	while (i < room->nb_links)
	{
		if (!room->links[i]->i && !flow[room->id][room->links[i]->id])
		{
			change = 1;
			queue = add_queue(queue, room->links[i], room);
		}
		++i;
	}
	i = 0;
	if (!change)
		while (i < room->nb_links)
		{
			if (!room->links[i]->i && flow[room->id][room->links[i]->id] < 0)
				queue = add_queue(queue, room->links[i], room);
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

	begin = init_queue(l);
	queue = enqueue(begin, begin->room, flow);
	while (begin)
	{
		/* print_queue(begin); */
		tmp = begin;
		if (!(begin = begin->next) || (begin->room == l->end))
		{
			free(tmp);
			break;
		}
		queue = enqueue(queue, begin->room, flow);
		free(tmp);
	}
	return (get_path(l, flow));
}

void	print_flow(t_lemin *l, char **tab)
{
	int j;
	int i;

	j = 0;
	while (j < l->nb_room)
	{
		i = 0;
		while (i < l->nb_room)
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

void	print_path(t_lemin *l, char **flow)
{
	int i;
	int j;
	int	nb_path;
	t_room *room;

	j = 0;
	nb_path = 0;
	while (j < l->start->nb_links)
	{
		if (flow[l->start->id][l->start->links[j]->id])
		{
			nb_path++;
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
						room = room->links[i];
						break ;
					}
					i++;
				}
			}
			ft_printf("%s\n", l->end->name);
		}
		j++;
	}
	ft_printf("{rgb(251,196,15)}number of path: %d\n{reset}", nb_path);
}

t_path *new_path(t_lemin *l, char **flow, int max_flow)
{
	t_ek *new;

	if (!(new = (t_ek *)malloc(sizeof(t_ek))))
		return (NULL);
	if (!(new->len = (int *)malloc(sizeof(int) * max_flow)))
		return (NULL);
	if (!(new->path = (t_path **)malloc(sizeof(t_path) * max_flow)))
		return (NULL);
	new->max_flow = max_flow;
	j = 0;
	while (j < l->start->nb_links)
	{
		if (flow[l->start->id][l->start->links[j]->id])
		{
			new->nb_way++;
			room = l->start->links[j];
			while (room != l->end)
			{
				i = 0;
				while (i < room->nb_links)
				{
					if (flow[room->id][room->links[i]->id] == 1)
					{
						room = room->links[i];
						break ;
					}
					i++;
				}
			}
		}
		j++;
	}
	return (NULL);
}

t_path *comp_paths(t_lemin *l, t_path *path, t_path *new)
{
	(void)l;
	(void)way;
	(void)new;
	return (NULL);
}

int		edmonds_karp(t_lemin *l)
{

	t_ek	*ek;
	char	**flow;
	int		max_flow;

	max_flow = 0;
	/* ek = NULL; */
	flow = init_ek(l);
	while (bfs(l, flow))
	{
		max_flow++;
		print_path(l, flow);
		/* ek = comp_paths(l, way, new_path(l, flow, max_flow)); */
		/* print_flow(l, flow); */
	}
	ft_printf("bfs: %d\n", max_flow);
	return (1);
}
