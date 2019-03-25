/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 03:27:16 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/25 04:00:29 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

int		start_to_end(t_lemin *l, t_file *file)
{
	int i;

	i = 0;
	while (i < l->start->nb_links)
	{
		if (l->start->links[i] == l->end)
		{
			i = 1;
			print_file(file);
			while (i <= l->ant)
			{
				ft_printf("L%d-%s", i, l->end->name);
				if (i++ != l->ant)
					ft_printf(" ");
			}
			ft_printf("\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int		init_send(t_lemin *l, t_queue **queue, int **send, t_file *file)
{
	t_room	*room;

	if (!(*queue = create_queue_ant(l)))
		return (0);
	if (!(*send = ants_by_path(l->start, l->tlen, l->flow, l->ant)))
	{
		free_queue(*queue);
		return (0);
	}
	print_file(file);
	room = l->room;
	while (room)
	{
		room->i = 0;
		room = room->next;
	}
	return (1);
}

static void	push_ant(t_lemin *l, t_queue *queue, int *ant, int *send)
{
	int i;

	i = 0;
	while (queue)
	{
		if (queue->room->i)
		{
			queue->room->to->i++;
			queue->room->i--;
			queue->room->to->id = queue->room->id;
			ft_printf("L%d-%s ", queue->room->id, queue->room->to->name);
		}
		queue = queue->next;
	}
	while (i < l->start->nb_links)
	{
		if (send[i])
		{
			send[i]--;
			ft_printf("L%d-%s ", ++(*ant), l->start->links[i]->name); // retirer espace a la fin des lignes
			l->start->links[i]->i++;
			l->start->links[i]->id = *ant;
		}
		i++;
	}
}

int		send_ants(t_lemin *l, t_file *file)
{
	t_queue *queue;
	int		*send;
	int		ant;

	ant = 0;
	if (!(init_send(l, &queue, &send, file)))
		return (0);
	while (l->end->i != l->ant)
	{
		push_ant(l, queue->next, &ant, send);
		ft_printf("\n");
	}
	free(send);
	return (free_queue(queue));
}
