/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_repart.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:29:00 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/11 18:15:32 by tle-dieu         ###   ########.fr       */
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
		ft_printf("nb fourmis: %d\n", ant_max);
		nb_path = ac - 2;
		ft_printf("nb path: %d\n", nb_path);
		if (!(path = (int *)malloc(sizeof(int) * nb_path)))
			return (1);
		while (i < ac)
		{
			path[j] = ft_atoi(av[i]);
			ft_printf("chemin: %d\n", path[j]);
			lmax += path[j];
			i++;
			j++;
		}
		ft_printf("lmax: %d\n", lmax);
		i = 0;
		while (i < j)
		{
			ant = (ant_max + lmax) / nb_path - path[i];
			if (ant < 0)
				ant = 0;
			lmax -= path[i];
			ant_max -= ant;
			k += ant;
			nb_path--;
			ft_printf("chemin %d: %d reste: %d\n", i++, ant, ant_max);
		}
		ft_printf("ant: %d\n", k);
	}
	else
		ft_printf("usage: ./ant_test [ants] [lpath lpath lpath...]\n");
}

/* gcc -o ant_test ants_repart.c -I libft/includes/ -L./libft -lft*/
