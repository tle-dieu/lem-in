/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:00:33 by matleroy          #+#    #+#             */
/*   Updated: 2019/03/25 14:13:07 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

static int	get_room_opt(char *line, int *room_opt)
{
	int new_opt;

	new_opt = 0;
	if (line[2] == '#' && line[3] == '#')
		return (1);
	if (!ft_strcmp("##end", line))
		new_opt = 2;
	else if (!ft_strcmp("##start", line))
		new_opt = 1;
	if (*room_opt != new_opt && *room_opt != 3)
		*room_opt += new_opt;
	return (0);
}

static int	add_line(char **line, t_file **actual, t_file **file)
{
	t_file	*new;

	*line = NULL;
	if (get_next_line(0, line) != 1)
		return (1);
	if (!(new = (t_file *)malloc(sizeof(t_file))))
	{
		free(*line);
		return (1);
	}
	new->next = NULL;
	new->line = *line;
	if (!*file)
		*file = new;
	else
		(*actual)->next = new;
	*actual = new;
	return (0);
}

static void	parse_graph(t_lemin *l, t_pipe **pipe,
t_file **file, t_file **actual)
{
	int		error;
	int		room_opt;
	char	*line;

	error = 0;
	room_opt = 0;
	while (!error && !add_line(&line, actual, file))
	{
		if (*line == '#')
			error = get_room_opt(line, &room_opt);
		else if (!ft_strchr(line, '-'))
			error = *pipe || line[0] == 'L' || get_room(l, line, &room_opt);
		else
		{
			error = room_opt || line[0] == 'L';
			if (!error)
				error = get_pipe(pipe, l->room, ft_strdup(line));
		}
	}
}

int			parse(t_lemin *l, t_pipe **pipe, t_file **file)
{
	char	*line;
	int		error;
	t_file	*actual;

	actual = NULL;
	while (!(error = add_line(&line, &actual, file)) && line[0] == '#')
	{
		if (line[1] == '#')
			return (0);
	}
	if (error || (l->ant = atoi_parsing(line)) <= 0)
		return (0);
	parse_graph(l, pipe, file, &actual);
	return (*pipe && l->room && l->start && l->end);
}
