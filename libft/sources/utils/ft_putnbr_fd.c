/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 13:11:46 by tle-dieu          #+#    #+#             */
/*   Updated: 2018/11/08 17:38:05 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	unsigned int abs;

	if (nb < 0)
	{
		abs = -nb;
		ft_putchar_fd('-', fd);
	}
	else
		abs = nb;
	if (abs > 9)
		ft_putnbr_fd(abs / 10, fd);
	ft_putchar_fd((abs % 10 + 48), fd);
}
