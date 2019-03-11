/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_repart.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:37:47 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/11 18:38:13 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int		main(int ac, char **av)
{
	int i;
	int j;
	int nb_path;
	int *path;
	int lmax;
	int ant_max;
	int ant;
	int k;

	lmax = 0;
	k = 0;
	j = 0;
	if (ac >= 3)
	{
		i = 1;
		ant_max = ft_atoi(av[i++]);
		ft_printf("{rgb(12,231,58)}nb fourmis: {reset}%d\n", ant_max);
		nb_path = ac - 2;
		ft_printf("{rgb(12,231,58)}nb path: {reset}%d\n", nb_path);
		if (!(path = (int *)malloc(sizeof(int) * nb_path)))
			return (1);
		ft_printf("{rgb(12,231,58)}lpath: {reset}");
		while (i < ac)
		{
			path[j] = ft_atoi(av[i]);
			ft_printf("%d ", path[j]);
			lmax += path[j];
			i++;
			j++;
		}
		ft_printf("\n{rgb(12,231,58)}lmax: {reset}%d\n", lmax);
		i = 0;
		while (i < j)
		{
			ant = (ant_max + lmax) / nb_path - path[i];
			if (ant < 0)
			{
				ft_printf("{#ff3333}ERROR PATH UNUSED !{reset}\n");
				return (1);
			}
			lmax -= path[i];
			ant_max -= ant;
			k += ant;
			nb_path--;
			ft_printf("{rgb(0,188,218)}chemin %d: {reset}%d {rgb(0,188,218)}reste: {reset}%d\n", i++, ant, ant_max);
		}
		ft_printf("{rgb(251,196,15)}ants total: {reset}%d\n", k);
		ft_printf("{rgb(251,196,15)}nb instructions: {reset}%d\n", ant + path[i - 1]);
	}
	else
		ft_printf("usage: ./ant_test [ants] [lpath lpath lpath...]\n");
}

/* gcc -o ant_test ants_repart.c -I libft/includes/ -L./libft -lft*/
