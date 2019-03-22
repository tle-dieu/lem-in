/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:57:45 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/22 11:02:33 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

void    print_link(t_room *room)
{
    while (room)
    {
        if (room->path)
		{
			if (room->from && room->to)
				ft_printf("%s -> %s -> %s    %d\n", room->from->name, room->name, room->to->name, room->path);
			else
				ft_printf("NULL: %s path: %d\n", room->name, room->path);
		}	
        room = room->next;
    }
}

void    verif_path(t_lemin *l)
{
    t_room *room;
    int j;
	int error;

    j = 0;
    room = l->room;
	error = 0;
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
                if (!room->to->i)
                    room->i = 1;
				else if (room->to != l->end)
                {
					error = 1;
                    ft_printf("{#ff3333}BLOQUE name: %s\n\n\n\n", room->to->name);
                    /* break ; */
                }
                room = room->to;
            }
        }
        j++;
    }
	if (!error)
		ft_printf("{#33de56}NO ERROR\n{reset}");
}

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

void    check_block(t_lemin *l, char **flow)
{
    int i;
    int j;
    t_room *room;


    room = l->room;
    while (room)
    {
        /* ft_printf("{#32ee03}name: {reset}%s {#32ee03}flow: {reset}%d\n", room->name, room->flow); */
        room->i = 0;
        room = room->next;
    }
    room = l->start;
    j = 0;
    while (j < l->start->nb_links)
    {
        if (flow[l->start->id][l->start->links[j]->id])
        {
            room = l->start->links[j];
            while (room != l->end)
            {
                i = 0;
                while (i < room->nb_links)
                {
                    if (flow[room->id][room->links[i]->id] == 1)
                    {
                        if (room->i)
                        {
                            ft_printf("{#ff3333}BLOCK {reset}%s\n", room->name);
                            exit(1);
                        }
                        room->i = 1;
                        room = room->links[i];
                        break ;
                    }
                    ++i;
                }
            }
        }
        j++;
    }
}

void	print_paths(t_lemin *l, char **flow)
{
	t_room *room;
	int j;
	int i;

	j = 0;
	while (j < l->start->nb_links)
	{
		if (flow[l->start->id][l->start->links[j]->id] == 1)
		{
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
