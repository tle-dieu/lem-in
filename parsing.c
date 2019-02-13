/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:00:33 by matleroy          #+#    #+#             */
/*   Updated: 2019/02/13 16:11:59 by matleroy         ###   ########.fr       */
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
	if (*room)
	{
		new->id = (*room)->id + 1;
		new->next = *room;
	}
	else
	{
		new->id = 0;
		new->next = NULL;
	}
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

t_matrice *init_matrice(t_matrice *matrice, int nb)
{
	int i;
	int j;

	matrice->size = nb;
	if (!(matrice->content = (void ***)malloc(sizeof(void**) * (nb + 1))))
		return (NULL);
	i = 0;
	while (i <= nb)
	{
		j = 0;
		if (!(matrice->content[i] = (void **)malloc(sizeof(void*) * (nb + 1))))
			return (NULL);
		while (j <= nb)
		{
			matrice->content[i][j++] = NULL;	
		}
		i++;
	}
	return (matrice);
}

t_matrice *check_room(t_room *room, t_pipe *pipe, t_matrice *matrice)
{
	t_room *tmp;
	int begin;
	int end;
	void *first;
	void *second;

	first = NULL;
	second = NULL;
	matrice = init_matrice(matrice, room->id);
	while (pipe)
	{
		begin = -1;
		end = -1;
		tmp = room;
		while (tmp)
		{
			if (!ft_strcmp(tmp->name, pipe->begin))
			{	
				begin = tmp->id;
				first = tmp;
			}
			if (!ft_strcmp(tmp->name, pipe->end))
			{
				end = tmp->id;
				second = tmp;
			}
			if (end >= 0 && begin >= 0)
				break ;
			tmp = tmp->next;
		}
		if (begin > -1 && end > -1)
		{
			ft_printf("{red} [%d][%d]\n", begin, end);
			matrice->content[begin][end] = first;
			matrice->content[end][begin] = second;
			ft_printf("{green}THIS PIPE IS GOOD!!!! ;)\n");

		}
		else 
			ft_printf("{yellow}THIS PIPE IS BAD!!!!! ;)\n");
		pipe = pipe->next;
	}
	return (matrice);
}


t_matrice *parse_infos(t_room **room, t_pipe **pipe, int *ant, t_matrice *matrice)
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
	return (check_room(*room, *pipe, matrice));
}
