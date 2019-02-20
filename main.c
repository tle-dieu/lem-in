/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 16:08:30 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/02/20 18:06:36 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_room(t_room *room)
{
	ft_printf("{red}::::ROOM::::\n");
	while (room)
	{
		ft_printf("{purple} room = {red} %s X: %d Y: %d", room->name, room->x, room->y);
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
		ft_printf("{purple} pipe = {cyan} %s to %s\n", pipe->begin, pipe->end);
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

int		main(void)
{
	t_room *room;
	t_pipe *pipe;
	int ant;

	pipe = NULL;
	room = NULL;
	/* ft_printf("{green}debut\n{reset}"); */
	parse_infos(&room, &pipe, &ant);
	/* ft_printf("{yellow}::::::::::PARSING RESULT::::::::::\n"); */
	/* ft_printf("{green}number of ants %d\n", ant); */
	/* print_room(room); */
	/* print_pipe(pipe); */
	if (!enough_data(room, pipe))
	{
		ft_printf("ERROR\n");
		return (1);
	}
	return (0);
}
