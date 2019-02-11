/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:00:33 by matleroy          #+#    #+#             */
/*   Updated: 2019/02/11 16:57:19 by matleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <fcntl.h>

// deplacemnent diagonales autorise ?
// listes des chemins les plus courts ?
// liste chaine avec tableau de pointeur pour les next ?
//	ou tableau a 2d ?
//
//
int	get_room(char *line)
{
	t_room room;
	int len;
	char *tmp;

	if (!strchr(line, '-'))
	{	
		if (!strcmp("##start", line) || !strcmp("##end", line))
		{
			if (get_next_line(0, &line) == 1)
				room.name = ft_strcdup(line, ' ');	
		}
		else
			room.name = ft_strcdup(line, ' ');	
		ft_printf("{yellow}%s\n", room.name);
		len = ft_strlen(room.name);
		if (len && line + len)
			ft_printf("{blue} %d", ft_atoi(line + len));
		if ((tmp = ft_strrchr(line, ' ')))
			ft_printf("{blue} %d\n", ft_atoi(tmp));
	}
	return (0);
}

int get_pipe(char *line)
{
	t_pipe pipe;

	pipe.name = strdup(line);
	ft_printf("{green} new pipe ::: %s\n", pipe.name);
	
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
		if (!strchr(line, '-'))
			get_room(line);
		else
			get_pipe(line);
	}
	return (0);
}
