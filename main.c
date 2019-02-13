/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 16:08:30 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/02/13 15:15:53 by matleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_room(t_room *room)
{
	ft_printf("{yellow}::::ROOM::::\n");
	while (room)
	{
		ft_printf("{purple} room = {yellow} %s place = %s => %d\n", room->name, room->place, room->id);
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

void print_matrice(void ***matrice, int nb)
{
	int i;
	int j;

	i = 0;
	while (i <= nb)
	{
		j = 0;
		while (j <= nb)
		{
			if (matrice[i][j])
				ft_printf("{yellow}%15s", ((t_room*)matrice[i][j])->name);
			else
				ft_printf("{cyan}%15p", matrice[i][j]);
			j++;
		}
		ft_printf("\n\n\n");
		i++;
	}

}
int		main(void)
{
	t_room *room;
	t_pipe *pipe;
	int ant;
	void ***matrice;

	matrice = NULL;
	pipe = NULL;
	room = NULL;
	ft_printf("{green}debut{reset}");
	matrice = parse_infos(&room, &pipe, &ant, matrice);
	ft_printf("{green} number of ants %d\n", ant);
	print_room(room);
	print_pipe(pipe);
	print_matrice(matrice, room->id);
	return (0);
}
