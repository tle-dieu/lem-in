/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 17:50:30 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/24 15:33:16 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

t_queue *end_room(t_queue *queue, t_room *room)
{
	int		i;
	t_queue *new;

	i = 0;
	while (i < room->nb_links)
	{
		if (!room->links[i]->i && room->links[i]->path)
		{
			if (!(new = (t_queue *)malloc(sizeof(t_queue))))
				return (NULL);
			queue->next = new;
			new->room = room->links[i];
			new->room->i = 1;
			new->next = NULL;
			queue = queue->next;
		}
		i++;
	}
	return (queue);
}

t_queue *next_room(t_lemin *l, t_queue *queue, t_room *room)
{
	t_queue *new;

	if (!room->from)
		return (queue);
	if (room->from != l->start)
	{
		if (!(new = (t_queue *)malloc(sizeof(t_queue))))
			return (NULL);
		queue->next = new;
		new->room = room->from;
		new->room->i = 1;
		new->next = NULL;
		return (queue->next);
	}
	return (queue);
}

t_queue	*queue_ant(t_lemin *l)
{
	t_queue	*queue;
	t_queue	*actual;
	t_queue	*begin;

	queue = NULL;
	if (!(begin = init_queue(l, l->end)))
		return (NULL);
	if (!(queue = end_room(begin, begin->room)))
	{
		free_queue(begin);
		return (NULL);
	}
	actual = begin;
	while ((actual = actual->next))
		if (!(queue = next_room(l, queue, actual->room)))
		{
			free_queue(begin);
			return (NULL);
		}
	return (begin);
}

int		*ants_by_path(t_room *start, int tlen, int max_flow, int ant_total)
{
	int len;
	int ant;
	int *send;
	int i;
	int j;
	int tt;

	j = 0;
	i = 0;
	tt = 0;
	if (!(send = (int*)malloc(sizeof(int) * start->nb_links)))
		return (NULL);
	while (j < start->nb_links)
	{
		ant = 0;
		if (start->links[j]->path)
		{
			len = start->links[j]->path;
			ant = ((long)ant_total + tlen) / (max_flow - i) - len;
			tlen -= len;
			ant_total -= ant;
			i++;
		}
		tt += ant;
		send[j++] = ant;
	}
	return (send);
}

void	push_ant(t_queue *queue)
{
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
}

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

int		send_ants(t_lemin *l, t_file *file)
{
	t_queue *queue;
	t_room	*room;
	int		*send;
	int		i;
	int		ant;

	if (!(queue = queue_ant(l)))
		return (0);
	if (!(send = ants_by_path(l->start, l->tlen, l->flow, l->ant)))
	{
		free_queue(queue);
		return (0);
	}
	print_file(file);
	room = l->room;
	while (room)
	{
		room->i = 0;
		room = room->next;
	}
	ant = 0;
	while (l->end->i != l->ant)
	{
		i = 0;
		push_ant(queue->next);
		while (i < l->start->nb_links)
		{
			if (send[i])
			{
				send[i]--; 
				++ant;
				ft_printf("L%d-%s ", ant, l->start->links[i]->name);
				l->start->links[i]->i++;
				l->start->links[i]->id = ant;
			}
			i++;
		}
		ft_printf("\n");
	}
	free(send);
	return (free_queue(queue));
}

/* int		put_instruction(char *buff, int nb, int i, char *room) */
/* { */
/* 	char	*dp; */
/* 	char	nbr[10]; */

/* 	buff[i++] = 'L'; */
/* 	dp = nbr; */
/* 	while (nb) */
/* 	{ */
/* 		*dp++ = nb % 10 + 48; */
/* 		nb /= 10; */
/* 	} */
/* 	while (dp != nbr) */
/* 		buff[i++] = *--dp; */
/* 	buff[i++] = '-'; */
/* 	while (*room) */
/* 		buff[i++] = *room++; */
/* 	return (i); */
/* } */

/* int		start_to_end(t_lemin *l, t_file *file) */
/* { */
/* 	char buff[BS_LEMIN]; */
/* 	int i; */
/* 	size_t len; */
/* 	int j; */

/* 	i = 0; */
/* 	j = 0; */
/* 	while (i < l->start->nb_links) */
/* 	{ */
/* 		if (l->start->links[i] == l->end) */
/* 		{ */
/* 			i = 1; */
/* 			len = ft_strlen(l->end->name); */
/* 			print_file(file); */
/* 			while (i <= l->ant) */
/* 			{ */
/* 				if (j + 14 + len >= BS_LEMIN) */
/* 				{ */
/* 					write(1, buff, j); */
/* 					j = 0; */
/* 				} */
/* 				j = put_instruction(buff, i, j, l->end->name); */
/* 				if (i++ != l->ant) */
/* 					buff[j++] = ' '; */
/* 			} */
/* 			buff[j++] = '\n'; */
/* 			write(1, buff, j); */
/* 			return (1); */
/* 		} */
/* 		i++; */
/* 	} */
/* 	return (0); */
/* } */
