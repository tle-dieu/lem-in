/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ways.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 16:13:02 by matleroy          #+#    #+#             */
/*   Updated: 2019/02/15 00:21:20 by matleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>
//init ways
// si start init way in ways 
// push reverse
// while reverse different des maillon precedents
//	si plusieurs occur copy list * (nombres d occur - 1) dans ways
// 	push tous les reverses
//
t_ways *create_waay(t_matrice *matrice, int i, int j)
{
	t_ways *ways;
	int tmp;
	int k;

	tmp = i;
	i = j;
	j = tmp;
	k = 0;
	ways = NULL;
	if (!(ways->way = (t_way*)malloc(sizeof(t_way))))
		return (NULL);
	ways->way->room = matrice->content[i][j];
	ft_printf("{red}%s\n{white}", ways->way->room->name);
	while (k <= matrice->size)
	{
		if (k != j && matrice->content[i][k] && matrice->content[k][i])
		{
			ft_printf("{green}i => %d k => %d =>%s\n{white}", i, k, ((t_room*)matrice->content[i][k])->name);
			ft_printf("{green}k => %d i => %d =>%s\n{white}", k, i, ((t_room*)matrice->content[k][i])->name);
			ft_printf("{white}copy lst k occur -1 times and adding of {yellow}%s{white} and same thing again !\n", ((t_room*)matrice->content[k][i])->name);
		}
		k++;
	}
	return (ways);
}

int push_cp_way()
{
	ft_printf("copy of a way\n");
	return (0);
}


t_room *get_next_room(t_matrice *matrice, t_way *way, int *i,int *j)
{
	int k;

	while (way)
	{
		if (way->room == matrice->content[*i][*j])
		{
			ft_printf("{green}wrong way!\n");
			return (NULL);
		}
		way = way->next;
	}
	while (*j <= matrice->size)
	{
		(*j)++;
		if (matrice->content[*i][*j] && matrice->content[*j][*i])
		{
			ft_printf("\n1) {red}[i:%d,j:%d] %s ->",*i, *j, ((t_room*)matrice->content[*i][*j])->name);
			ft_printf("2) {red}[j:%d,i:%d] %s\n", *j, *i, ((t_room*)matrice->content[*j][*i])->name);
			ft_printf("4) {cyan}i = %d: j = %d:\n", *i, *j);
			k = *i;
			*i = *j;
			*j = k;
			return (matrice->content[*j][*i]);
		}
	}
	return (NULL);
}

t_way *push_room(t_way *way, t_room *room, t_way **begin)
{
	t_way *new;
	
	new = NULL;
	if (!(new = (t_way*)malloc(sizeof(t_way))))
		return (NULL);
	if (*begin)
		way->next = new;
	else
		*begin = new;
	new->room = room;
	new->next = NULL;
	ft_printf("{background}%s{reset}\n\n", new->room->name);
	return (new);
}

void print_way(t_way *way)
{	
	while (way)
	{
		ft_printf("%p to\n", way->room->name);
		way = way->next;
	}
}

t_ways *create_way(t_ways **ways, t_matrice *matrice, int i, int j)
{
	t_way *begin;
	t_way *way;
	t_room *ret;

	way = NULL;
	begin = NULL;
	while ((ret = get_next_room(matrice, begin, &i, &j)))
	{
		ft_printf("{yellow} i = %d j = %d\n", i, j);
		ft_printf("%s\n", (way = push_room(way, ret, &begin))->room->name);
	}
	print_way(begin);
	(void)(*ways)->way;
	return (NULL);
}

int get_ways(t_matrice *matrice, t_ways **ways)
{
	int i;
	int j;
	i = 0;
	if (!(*ways = (t_ways*)malloc(sizeof(t_ways))))
		return (1);
	ways = NULL;
	while (i <= matrice->size)
	{
		j = 0;
		while (j <= matrice->size)
		{
			if (matrice->content[i][j] && ((t_room*)matrice->content[i][j])->place &&!strcmp(((t_room*)matrice->content[i][j])->place, "##start"))
			{
				ft_printf("\n");
				create_way(ways, matrice, i, j);
			}
			j++;
		}
		i++;
	}
	return (0);
}
