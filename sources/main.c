/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 16:08:30 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/21 11:31:07 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <unistd.h>
#include <stdlib.h>

int	create_graph(t_lemin *l, t_pipe *pipe)
{
	t_room *room;
	t_room **tab;
	int i;

	room = l->room;
	if (!(tab = (t_room **)malloc(sizeof(t_room *) * (l->nb_room))))
		return (0);
	i = 0;
	while (room)
	{
		tab[i++] = room;
		if (room->nb_links && !(room->links = (t_room**)malloc(sizeof(t_room*) * room->nb_links)))
			return (0);
		room = room->next;
	}
	while (pipe)
	{
		tab[pipe->from]->links[tab[pipe->from]->i++] = tab[pipe->to];
		tab[pipe->to]->links[tab[pipe->to]->i++] = tab[pipe->from];
		pipe = pipe->next;
	}
	print_graph(tab, l);
	return (1);
}

int		main(void)
{
	t_pipe *pipe;
	t_lemin l;

	l = (t_lemin){-1,0,0,0,0,NULL,NULL,NULL};
	pipe = NULL;
	ft_printf("{green}debut\n{reset}");
	parse_infos(&l, &pipe);
	ft_printf("{yellow}::::::::::PARSING RESULT::::::::::\n");
	ft_printf("{green}number of ants %d\n", l.ant);
	if (pipe && l.room)
	{
		print_room(&l);
		print_pipe(pipe);
		create_graph(&l, pipe);
		edmonds_karp(&l);
	}
	/* send_ants(&l); */
	return (0);
}
