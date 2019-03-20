/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 16:08:30 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/20 12:47:27 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <unistd.h>
#include <stdlib.h>

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
		l.tab = create_graph(&l, pipe); //l.tab pour print, a ne creer seulement dans fonction
		print_graph(l.tab, &l);
		edmonds_karp(&l);
	}
	if (!enough_data(&l, pipe))
	{
		ft_printf("NOT ENOUGH DATA ERROR\n");
		return (1);
	}
	send_ants(&l);
	return (0);
}
