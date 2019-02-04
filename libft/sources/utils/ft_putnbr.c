/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 13:11:46 by tle-dieu          #+#    #+#             */
/*   Updated: 2018/11/08 17:33:01 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int nb)
{
	unsigned int abs;

	if (nb < 0)
	{
		abs = -nb;
		ft_putchar('-');
	}
	else
		abs = nb;
	if (abs > 9)
		ft_putnbr(abs / 10);
	ft_putchar(abs % 10 + 48);
}
