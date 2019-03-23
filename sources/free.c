/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:59:46 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/23 21:07:02 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

int	free_queue(t_queue *queue)
{
	t_queue *next;

	while (queue)
	{
		next = queue->next;
		free(queue);
		queue = next;
	}
	return (1);
}

int	free_pipe(t_pipe *pipe)
{
	t_pipe *next;

	while (pipe)
	{
		next = pipe->next;
		free(pipe);
		pipe = next;
	}
	return (1);
}

int	free_room(t_room *room)
{
	t_room *next;

	while (room)
	{
		next = room->next;
		free(room->name);
		free(room->links);
		free(room);
		room = next;
	}
	return (1);
}

int	free_tab(void **tab, int size)
{
	int i;

	i = 0;
	while (i < size)
		free(tab[i++]);
	free(tab);
	return (1);
}

int	free_file(t_file *file)
{
	t_file *next;

	while (file)
	{
		next = file->next;
		free(file->line);
		free(file);
		file = next;
	}
	return (1);
}
