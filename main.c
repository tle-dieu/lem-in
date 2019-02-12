/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 16:08:30 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/02/12 12:03:41 by matleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_room(t_room *room)
{
	ft_printf("{red}::::ROOM::::\n");
	while (room)
	{
		ft_printf("{purple} room = {red} %s place = %s\n", room->name, room->place);
		room = room->next;
	}
}

void	print_pipe(t_pipe *pipe)
{
	ft_printf("{cyan}::::PIPE::::\n");
	while (pipe)
	{
		ft_printf("{purple} pipe = {cyan} %s to %s\n", pipe->begin, pipe->end);
		pipe = pipe->next;
	}
}

int		main(void)
{
	t_room *room;
	t_pipe *pipe;
	int ant;

	pipe = NULL;
	room = NULL;
	ft_printf("{green}debut{reset}");
	parse_infos(&room, &pipe, &ant);
	ft_printf("{green} number of ants %d\n", ant);
	print_room(room);
	print_pipe(pipe);
	return (0);
}
