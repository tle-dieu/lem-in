/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:22:27 by tle-dieu          #+#    #+#             */
/*   Updated: 2018/11/12 17:25:44 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_count_dec(int nb, size_t *dec)
{
	size_t			len;
	unsigned int	abs;

	len = 1;
	if (nb < 0)
	{
		abs = -nb;
		len++;
	}
	else
		abs = nb;
	while (abs > 9)
	{
		*dec *= 10;
		len++;
		abs /= 10;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	size_t			i;
	size_t			dec;
	unsigned int	abs;
	char			*nbr;

	dec = 1;
	i = 0;
	if (!(nbr = (char *)malloc(sizeof(char) * (ft_count_dec(n, &dec) + 1))))
		return (NULL);
	if (n < 0)
	{
		nbr[i++] = '-';
		abs = -n;
	}
	else
		abs = n;
	while (dec)
	{
		nbr[i++] = abs / dec % 10 + 48;
		dec /= 10;
	}
	nbr[i] = '\0';
	return (nbr);
}
