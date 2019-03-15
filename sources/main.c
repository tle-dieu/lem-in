/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 16:08:30 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/16 00:15:28 by tle-dieu         ###   ########.fr       */
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
	while (room)
	{
		ft_printf("{purple} room = {yellow} %s id: %d nb_links: %d X: %d Y: %d", room->name, room->id, room->nb_links, room->x, room->y);
		if (room == l->end || room == l->start)
		{
			if (l->end == l->start)
				ft_printf(" ERROR");
			else
				ft_printf(room == l->start ? " START" : " END");
		}
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

t_room **create_graph(t_lemin *l, t_pipe *pipe)
{
	t_room *room;
	t_room **tab;
	int i;

	room = l->room;
	tab = (t_room **)malloc(sizeof(t_room *) * (l->nb_room));
	i = 0;
	while (room)
	{
		tab[i++] = room;
		if (room->nb_links && !(room->links = (t_room**)malloc(sizeof(t_room*) * room->nb_links)))
			return (NULL);
		room = room->next;
	}
	while (pipe)
	{
		tab[pipe->from]->links[tab[pipe->from]->i++] = tab[pipe->to];
		tab[pipe->to]->links[tab[pipe->to]->i++] = tab[pipe->from];
		pipe = pipe->next;
	}
	return (tab);
}

void	print_graph(t_room **tab, t_lemin *l)
{
	int i;
	int j;

	i = 0;
	ft_printf("{#de4343}");
	while (i < l->nb_room)
	{
		j = 0;
		ft_printf("\n-----%s-----\nid: %d nb_links: %d {#f0ab68}\n{#de4343}", tab[i]->name, tab[i]->id, tab[i]->nb_links);
		while (j < tab[i]->nb_links)
		{
			ft_printf("  -> nb: %d name: %s id: %d\n", j, tab[i]->links[j]->name, tab[i]->links[j]->id);
			j++;
		}
		i++;
	}
	ft_printf("{reset}");
}

void	test(t_lemin *l)
{
	int i;
	int j;
	t_room *room;

	j = 0;
	while (j < 75)
	{
		room = l->room;
		while (room)
		{
			i = 0;
			while (i < room->nb_links)
				i++;
			room = room->next;
		}
		j++;
	}
}

int		main(void)
{
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
		l.tab = create_graph(&l, pipe);
		print_graph(l.tab, &l);
		edmonds_karp(&l);
	}
	if (!enough_data(&l, pipe))
	{
		ft_printf("NOT ENOUGH DATA ERROR\n");
		return (1);
	}
	return (0);
}
