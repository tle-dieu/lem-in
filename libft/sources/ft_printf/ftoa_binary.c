/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 00:25:11 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/16 18:17:02 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		special_case(char *mantissa)
{
	int		inf;

	inf = 2;
	while (*++mantissa)
	{
		if (*mantissa == '1')
		{
			inf = 1;
			break ;
		}
	}
	return (inf);
}

char	*get_specialf(int sign, int inf, char conv)
{
	char *str;

	if (inf == 2)
	{
		if (!sign)
			str = (conv != 'f' ? "INF\0" : "inf\0");
		else
			str = (conv != 'f' ? "-INF\0" : "-inf\0");
	}
	else
		str = (conv != 'f' ? "NAN\0" : "nan\0");
	return (str);
}

void	get_fbinary(t_float *f, unsigned char *c)
{
	int i;
	int j;
	int k;

	j = 6;
	i = 0;
	k = 4;
	f->sign = *(c + 7) & 0x80 ? 1 : 0;
	f->exp = (*(c + 7) & ~0x80) << 4 | (*(c + 6) >> 4);
	f->mantissa[i++] = f->exp ? '1' : '0';
	while (k--)
		f->mantissa[i++] = (*(c + 6) & 1 << k ? '1' : '0');
	while (j--)
	{
		k = 8;
		while (k--)
			f->mantissa[i++] = (*(c + j) & 1 << k ? '1' : '0');
	}
	f->mantissa[i] = '\0';
	f->size = (f->exp ? i : i - 1);
}

void	get_lfbinary(t_float *f, unsigned char *c)
{
	int i;
	int j;
	int k;

	j = 8;
	i = 0;
	f->sign = *(c + 9) & 0x80 ? 1 : 0;
	f->exp = (*(c + 9) & ~0x80) << 8 | *(c + 8);
	while (j--)
	{
		k = 8;
		while (k--)
			f->mantissa[i++] = (*(c + j) & 1 << k ? '1' : '0');
	}
	f->mantissa[i] = '\0';
	f->size = i;
}
