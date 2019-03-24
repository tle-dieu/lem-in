/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 16:08:30 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/24 20:13:29 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <unistd.h>
#include <stdlib.h>

int		create_graph(t_lemin *l, t_pipe *pipe) //mettre dans un fichier parsing
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
		{
			free(tab);
			return (0);
		}
		room = room->next;
	}
	while (pipe)
	{
		tab[pipe->from]->links[tab[pipe->from]->i++] = tab[pipe->to];
		tab[pipe->to]->links[tab[pipe->to]->i++] = tab[pipe->from];
		pipe = pipe->next;
	}
	free(tab);
	return (1);
}

int		main(void)
{
	t_pipe	*pipe;
	t_lemin	l;
	t_file	*file;

	pipe = NULL;
	file = NULL;
	l = (t_lemin){-1, 0, 0, 0, 0, NULL, NULL, NULL};
	if (!(parse_infos(&l, &pipe, &file)))
		return (error_finish(file, pipe, l.room, "ERROR\n"));
	if (!(create_graph(&l, pipe)))
		return (error_finish(file, pipe, l.room, "ERROR\n"));
	if (start_to_end(&l, file))
		return (!error_finish(NULL, pipe, l.room, NULL));
	print_room(&l); // a retirer
	if (edmonds_karp(&l))
	{
		if (!(send_ants(&l, file)))
			return (error_finish(file, pipe, l.room, "ERROR\n"));
	}
	else
		return (error_finish(file, pipe, l.room, "ERROR\n"));
	return (!error_finish(NULL, pipe, l.room, NULL));
}
