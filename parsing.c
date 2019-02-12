/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:00:33 by matleroy          #+#    #+#             */
/*   Updated: 2019/02/12 15:32:20 by matleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <fcntl.h>
#include <stdlib.h>

int	get_room(t_room **room, char *line)
{
	int len;
	char *tmp;
	t_room *new;

	if (!(new = (t_room*)malloc(sizeof(t_room))))
		return (1);
	if (!strcmp("##start", line) || !strcmp("##end", line))
	{
		new->place = line;
		if (get_next_line(0, &line) == 1)
			new->name = ft_strcdup(line, ' ');
	}
	else
	{
		new->place = NULL;
		new->name = ft_strcdup(line, ' ');	
	}
	len = ft_strlen(new->name);
	if (len && line + len)
		ft_printf("{blue} %d", ft_atoi(line + len));
	if ((tmp = ft_strrchr(line, ' ')))
		ft_printf("{blue} %d\n", ft_atoi(tmp));
	new->next = *room ? *room : NULL;
	*room = new;
	return (0);
}

int get_pipe(t_pipe **pipe, char *line)
{
	t_pipe *new;
	char *tmp;

	if (!(new = (t_pipe*)malloc(sizeof(t_pipe))))
		return (1);
	new->begin = ft_strcdup(line, '-');
	tmp = ft_strchr(line, '-');
	if (*tmp == '-')
		tmp++;
	new->end = ft_strdup(tmp);
	new->next = *pipe ? *pipe : NULL;
	*pipe = new;
	return (0);
}

int	parse_infos(t_room **room, t_pipe **pipe, int *ant)
{
	char *line;

	*ant = -1;
	while (get_next_line(0, &line) == 1)
	{
		if (*ant < 0)
			*ant = ft_atoi(line);
		else if (!strchr(line, '-'))
			get_room(room, line);
		else
			get_pipe(pipe, line);
	}
	return (0);
}
