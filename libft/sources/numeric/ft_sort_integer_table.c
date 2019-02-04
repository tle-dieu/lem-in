/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_integer_table.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 18:41:51 by tle-dieu          #+#    #+#             */
/*   Updated: 2018/11/12 12:28:59 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_sort_integer_table(int *tab, int size)
{
	int		i;
	char	temp;

	i = 0;
	while (i < size)
	{
		if (tab[i] <= tab[i + 1])
			i++;
		else
		{
			temp = tab[i + 1];
			tab[i + 1] = tab[i];
			tab[i] = tab[i + 1];
			i = 0;
		}
	}
}
