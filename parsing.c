/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:00:33 by matleroy          #+#    #+#             */
/*   Updated: 2019/02/04 21:08:25 by matleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <fcntl.h>


int	get_start(char *line)
{
	t_room start;

	(void)start;
	if (!strcmp("##start", line))
	{	
		ft_printf("{yellow} good\n");
		if (get_next_line(0, &line) == 1)
		{
			start.name = ft_strcdup(line, ' ');	
		}
		ft_printf("{green} name = %s\n", start.name);
	}
	return (0);
}

int	parse_infos()
{
	char *line;
	int		ant;

	ant = -1;
	while (get_next_line(0, &line) == 1)
	{
		if (ant < 0)
		{
			ant = ft_atoi(line);
		}
		ft_printf("{red}%d\n", ant);
		ft_printf("{cyan}%s\n", line);
		get_start(line);
	}
	return (0);
}
