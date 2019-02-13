/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ways.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 16:13:02 by matleroy          #+#    #+#             */
/*   Updated: 2019/02/13 20:46:29 by matleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

t_ways *create_way(t_matrice *matrice, int i, int j)
{
	t_ways *ways;
	int tmp;
	int k;

	tmp = i;
	i = j;
	j = tmp;
	k = 0;
	ways = NULL;
	if (!(ways = (t_ways*)malloc(sizeof(t_ways))))
		return (NULL);
	ways->way = NULL;
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
			//si plus d un occurence copier la chaine le nombres de fois qu il y a occurence en k != i dans la liste ways
			//et push k i a la fin de la nouvelle chaine
			ft_printf("{white}copy lst k occur -1 times and adding of {yellow}%s{white} and same thing again !\n", ((t_room*)matrice->content[k][i])->name);
		}
		k++;
	}
	return (ways);
}

int get_ways(t_matrice *matrice, t_ways **ways)
{
	int i;
	int j;
	(void)ways;
	i = 0;
	while (i <=  matrice->size)
	{
		j = 0;
		while (j <= matrice->size)
		{
			if (matrice->content[i][j] && ((t_room*)matrice->content[i][j])->place &&!strcmp(((t_room*)matrice->content[i][j])->place, "##start"))
			{
				create_way(matrice, i, j);
			}
			j++;
		}
		i++;
	}
	return (0);
}
