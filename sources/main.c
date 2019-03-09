/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 16:08:30 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/09 20:53:37 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <unistd.h>
#include <stdlib.h>

void	print_room(t_lemin *l)
{
	t_room *room;

	room = l->room;
	ft_printf("{red}::::ROOM::::\n");
	ft_printf("nb_room: %d\n", l->nb_room);
	while (room)
	{
		ft_printf("{purple} room = {yellow} %s id: %d X: %d Y: %d", room->name, room->id, room->x, room->y);
		if (room == l->start && room == l->end)
			ft_printf(" ERROR");
		else if (room == l->start)
			ft_printf(" START");
		else if (room == l->end)
			ft_printf(" END");
		ft_printf("\n");
		room = room->next;
	}
	ft_printf("{reset}");
}

void	print_pipe(t_pipe *pipe)
{
	ft_printf("{cyan}::::PIPE::::\n");
	while (pipe)
	{
		ft_printf("{purple} pipe = {cyan} %d to %d\n", pipe->from, pipe->to);
		pipe = pipe->next;
	}
	ft_printf("{reset}");
}

int		enough_data(t_lemin *l, t_pipe *pipe)
{
	if (!pipe)
		return (0);
	if (!l->end || !l->start || l->end == l->start)
		return (0);
	return (1);
}

int			create_tab(t_lemin *l)
{
	t_room *room;

	room = l->room;
	if (!(l->tab = (t_room**)malloc(sizeof(t_room*) * l->nb_room)))
		return (0);
	while (room)
	{
		l->tab[room->id] = room;
		room = room->next;
	}
	return (1);
}

void		print_matrix(t_lemin *l, t_room ***matrix)
{
	t_room *room;
	int max;
	int j;
	int i;
	int tmp;

	j = 0;
	room = l->room;
	max = 0;
	while (room)
	{
		if ((tmp = (int)ft_strlen(room->name)) > max)
			max = tmp;
		room = room->next;
	}
	while (j < l->nb_room)
	{
		i = 0;
		while (i < l->nb_room)
		{
			if (matrix[j][i])
				ft_printf("{#ff3333}%-*s", max + 1, matrix[j][i]->name);
			else
				ft_printf("{reset}%-*s", max + 1, "*");
			++i;
		}
		++j;
		i = max / 2 + 1;
		while (i--)
			ft_printf("\n");
	}
}

t_room		***init_matrix_adj(t_lemin *l)
{
	t_room ***matrix_adj;
	int j;
	int i;

	j = 0;
	if (!(matrix_adj = (t_room***)malloc(sizeof(t_room**) * l->nb_room)))
		return (NULL);
	while (j < l->nb_room)
	{
		i = 0;
		if (!(matrix_adj[j] = (t_room**)malloc(sizeof(t_room*) * l->nb_room)))
			return (NULL);
		while (i < l->nb_room)
			matrix_adj[j][i++] = NULL;
		j++;
	}
	return (matrix_adj);
}

void	print_graph(t_room **tab, t_lemin *l)
{
	int i;

	i = 0;
	ft_printf("{#de4343}");
	while (i < l->nb_room)
	{
		ft_printf("\n-----%s-----\nid: %d {#f0ab68}\n{#de4343}", tab[i]->name, tab[i]->id);
		i++;
	}
	ft_printf("{reset}");
}

t_room		***create_matrix_adj(t_lemin *l, t_pipe *pipe)
{
	t_room ***matrix_adj;
	t_room *room;
	t_pipe *tmp;
	int j;	

	j = 0;
	room = l->room;
	matrix_adj = init_matrix_adj(l);
	while (j < l->nb_room)
	{
		tmp = pipe;
		while (tmp)
		{
			if (room->id == tmp->to)
				matrix_adj[j][tmp->from] = l->tab[tmp->from];
			else if (room->id == tmp->from)
				matrix_adj[j][tmp->to] = l->tab[tmp->to];
			tmp = tmp->next;
		}
		room = room->next;
		j++;
	}
	return (matrix_adj);
}

int		main(void)
{
	t_room ***matrix_adj;
	t_pipe *pipe;
	t_lemin l;

	l.start = NULL;
	l.end = NULL;
	l.room = NULL;
	l.nb_room = 0;
	pipe = NULL;
	ft_printf("{green}debut\n{reset}");
	parse_infos(&l, &pipe);
	ft_printf("{yellow}::::::::::PARSING RESULT::::::::::\n");
	ft_printf("{green}number of ants %d\n", l.ant);
	if (pipe && l.room)
	{
		print_room(&l);
		print_pipe(pipe);
		create_tab(&l); //revoir la protection du malloc
		print_graph(l.tab, &l);
		matrix_adj = create_matrix_adj(&l, pipe);
		print_matrix(&l, matrix_adj);
		/* int i; */
		/* i = 3; */
		/* while (--i) */
		bfs(&l, matrix_adj);
		/* edmond_karp(infos, room); */
	}
	if (!enough_data(&l, pipe))
	{
		ft_printf("NOT ENOUGH DATA ERROR\n");
		return (1);
	}
	return (0);
}
