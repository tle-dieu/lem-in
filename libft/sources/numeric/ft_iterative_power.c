/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 10:03:41 by tle-dieu          #+#    #+#             */
/*   Updated: 2018/11/12 12:27:35 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_iterative_power(int nb, int power)
{
	int i;
	int result;

	i = 1;
	result = nb;
	if (power == 0)
		return (1);
	if (nb == 0 || power < 0)
		return (0);
	while (i != power)
	{
		result = result * nb;
		i++;
	}
	return (result);
}
