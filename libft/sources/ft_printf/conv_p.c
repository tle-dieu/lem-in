/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 17:59:27 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/16 18:16:36 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	p_width(t_print *buff, t_flag *flags, int len, int order)
{
	if (!flags->minus && !order && (!flags->zero || flags->prec != -1))
	{
		if (flags->prec != -1)
		{
			flags->zero = 0;
			flags->width -= (flags->prec > len ? flags->prec : len) + 2;
		}
		else
			flags->width -= len + 2;
		field_in_buff(buff, flags->width, flags->zero);
	}
	else if (order && flags->minus)
	{
		flags->zero = 0;
		if (flags->prec != -1)
			flags->width -= (flags->prec > len ? flags->prec : len) + 2;
		else
			flags->width -= len + 2;
		field_in_buff(buff, flags->width, flags->zero);
	}
}

static int	p_flags(t_print *buff, t_flag *flags, uintmax_t nb)
{
	int len;

	len = 0;
	if (flags->width || flags->prec != -1)
	{
		len = base_len(nb, 16) - (!nb && !flags->prec);
		p_width(buff, flags, len, 0);
	}
	if (buff->i + 3 >= BS_PRINTF)
		empty_buff(buff);
	buff->str[buff->i++] = '0';
	buff->str[buff->i++] = 'x';
	if (flags->width && flags->zero && !flags->minus)
		if (!(flags->prec += flags->width + (flags->prec == -1 ? 1 : 0) - 2))
			flags->prec = -1;
	if (flags->prec != -1)
		field_in_buff(buff, flags->prec - len, 16);
	return (len);
}

void		p_conv(t_print *buff, t_flag *flags, uintmax_t nb)
{
	char		*dp;
	char		nbr[16];
	const char	base[] = "0123456789abcdef\0";
	int			len;

	len = p_flags(buff, flags, nb);
	if (buff->i + 18 >= BS_PRINTF)
		empty_buff(buff);
	if (!nb && flags->prec)
		buff->str[buff->i++] = '0';
	dp = nbr;
	while (nb)
	{
		*dp++ = base[nb % 16];
		nb /= 16;
	}
	while (dp != nbr)
		buff->str[buff->i++] = *--dp;
	if (flags->width)
		p_width(buff, flags, len, 1);
}
