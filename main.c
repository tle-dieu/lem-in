/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 16:08:30 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/02/22 21:08:13 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_room(t_room *room)
{
	ft_printf("{red}::::ROOM::::\n");
	while (room)
	{
		ft_printf("{purple} room = {yellow} %s id: %d nb_links: %d X: %d Y: %d", room->name, room->id, room->nb_links, room->x, room->y);
		if (room->place)
		{
			if (room->place == 3)
				ft_printf(" ERROR");
			else
				ft_printf(room->place == 1 ? " START" : " END");
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

int		enough_data(t_room *room, t_pipe *pipe)
{
	int start;

	(void)pipe;
	start = 0;
	while (room)
	{
		if (room->place)
		{
			if (room->place == 3)
				return (0);
			start += room->place;
		}
		room = room->next;
	}
	return (start == 3);
}

#include <stdlib.h>

t_room **create_graph(t_room *room, t_pipe *pipe)
{
	t_room **tab;
	int i;

	tab = (t_room **)malloc(sizeof(t_room *) * (room->id + 2));
	i = room->id;
	tab[i + 1] = NULL;
	while (room)
	{
		tab[i--] = room;
		if (room->nb_links && !(room->links = (t_room**)malloc(sizeof(t_room*) * room->nb_links)))
			return (NULL);
		room = room->next;
	}
	i = 0;
	while (tab[i])
		ft_printf("name: %s\n", tab[i++]->name);
	ft_printf("debut boucle\n");
	while (pipe)
	{
		ft_printf("{#80f00d}%s : %d to %s : %d\n{reset}", tab[pipe->from]->name, pipe->from, tab[pipe->to]->name, pipe->to);
		ft_printf("tab[%d]->links[tab[%d]->%d++] = tab[%d]\n", pipe->from, pipe->from, tab[pipe->from]->i, pipe->to);
		tab[pipe->from]->links[tab[pipe->from]->i++] = tab[pipe->to];
		ft_printf("tab[%d]->links[tab[%d]->%d++] = tab[%d]\n", pipe->to, pipe->to, tab[pipe->to]->i, pipe->from);
		tab[pipe->to]->links[tab[pipe->to]->i++] = tab[pipe->from];
		pipe = pipe->next;
	}
	return (tab);
}

void	print_graph(t_room **tab)
{
	int i;
	int j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		ft_printf("\n-----ROOM-----\nname: %s id: %d nb_links: %d\n", tab[i]->name, tab[i]->id, tab[i]->nb_links);
		while (j < tab[i]->nb_links)
		{
			ft_printf("  -> nb: %d name: %s id: %d\n", j, tab[i]->links[j]->name, tab[i]->links[j]->id);
			j++;
		}
		i++;
	}
}

int		main(void)
{
	t_room *room;
	t_room **tab;
	t_pipe *pipe;
	int ant;

	pipe = NULL;
	room = NULL;
	ft_printf("{green}debut\n{reset}");
	parse_infos(&room, &pipe, &ant);
	ft_printf("{yellow}::::::::::PARSING RESULT::::::::::\n");
	ft_printf("{green}number of ants %d\n", ant);
	print_room(room);
	print_pipe(pipe);
	tab = create_graph(room, pipe);
	print_graph(tab);
	if (!enough_data(room, pipe))
	{
		ft_printf("ERROR\n");
		return (1);
	}
	return (0);
}
