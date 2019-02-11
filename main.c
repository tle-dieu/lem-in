/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 16:08:30 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/02/11 23:33:32 by matleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_room(t_room *room)
{
	ft_printf("{red}::::ROOM::::\n");
	while (room)
	{
		ft_printf("{purple} room = {red} %s\n", room->name);
		room = room->next;
	}
}

void	print_pipe(t_pipe *pipe)
{
	ft_printf("{cyan}::::PIPE::::\n");
	while (pipe)
	{
		ft_printf("{purple} room = {cyan} %s\n", pipe->name);
		pipe = pipe->next;
	}
}

int		main(void)
{
	t_room *room;
	t_pipe *pipe;

	pipe = NULL;
	room = NULL;
	ft_printf("{green}debut{reset}");
	parse_infos(&room, &pipe);
	print_room(room);
	print_pipe(pipe);
	return (0);
}
