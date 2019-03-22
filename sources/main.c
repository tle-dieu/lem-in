/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 16:08:30 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/22 23:35:57 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <unistd.h>
#include <stdlib.h>

int		create_graph(t_lemin *l, t_pipe *pipe)
{
	t_room	*room;
	t_room	**tab;
	int		i;

	room = l->room;
	if (!(tab = (t_room **)malloc(sizeof(t_room *) * (l->nb_room))))
		return (0);
	i = 0;
	while (room)
	{
		tab[i++] = room;
		if (room->nb_links
		&& !(room->links = (t_room**)malloc(sizeof(t_room*) * room->nb_links)))
			return (0);
		room = room->next;
	}
	while (pipe)
	{
		tab[pipe->from]->links[tab[pipe->from]->i++] = tab[pipe->to];
		tab[pipe->to]->links[tab[pipe->to]->i++] = tab[pipe->from];
		pipe = pipe->next;
	}
	return (1);
}

int		main(void)
{
	t_pipe	*pipe;
	t_lemin	l;
	t_file	*file;

	l = (t_lemin){-1, 0, 0, 0, 0, NULL, NULL, NULL};
	pipe = NULL;
	file = NULL;
	parse_infos(&l, &pipe, &file);
	if (pipe && l.room)
	{
		create_graph(&l, pipe);
		if (start_to_end(&l))
			return (0);
		/* print_room(&l); */
		/* print_pipe(pipe); */
		if (edmonds_karp(&l))
			send_ants(&l);
	}
	return (0);
}
