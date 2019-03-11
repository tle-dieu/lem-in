/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_repart.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:29:00 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/11 16:52:23 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
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

	lmax = 0;
	j = 0;
	if (ac >= 4)
	{
		i = 1;
		ant_max = ft_atoi(av[i++]);
		ft_printf("nb fourmis: %d\n", ant_max);
		nb_path = ft_atoi(av[i++]);
		ft_printf("nb path: %d\n", nb_path);
		if (!(path = (int *)malloc(sizeof(int))))
			return (1);
		while (j < nb_path && i < ac)
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
			ft_printf("chemin %d: %d\n", ++i, ant);
		}
	}
	else
		ft_printf("./a.out [nb_fourmis] [nb_way] lway lway lway...\n");
}
