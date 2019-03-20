/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:57:45 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/20 16:37:52 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void    print_flow(t_lemin *l, char **tab)
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

void    print_queue(t_queue *print)
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

void	verif_path(t_lemin *l)
{
	t_room *room;
	int j;

	j = 0;
	room = l->room;
	while (room)
	{
		room->i = 0;
		room = room->next;
	}
	while (j < l->start->nb_links)
	{
		if (l->start->links[j]->path)
		{
			room = l->start->links[j];
			while (room != l->end)
			{
				if (!room->next_p->i)
				{
					room = room->next_p;
					room->i = 1;
				}
				else
				{
					ft_printf("{#ff3333}BLOQUE name: %s\n\n\n\n", room->next_p->name);
					break ;
				}
			}
		}
		j++;
	}
}
