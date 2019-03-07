/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_di.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 17:58:34 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/07 15:25:21 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	int_len(t_flag *flags, intmax_t nb)
{
	int len;

	len = (flags->plus || flags->space || nb < 0) + 1;
	while (nb /= 10)
		len++;
	return (len);
}

static void	di_plus_space(t_print *buff, t_flag *flags, intmax_t nb)
{
	if (buff->i >= BS_PRINTF)
		empty_buff(buff);
	if (nb >= 0)
	{
		if (flags->plus || flags->space)
			buff->str[buff->i++] = flags->plus ? '+' : ' ';
	}
	else
		buff->str[buff->i++] = '-';
}

static void	di_width(t_print *buff, t_flag *flags, int len, int order)
{
	if (!flags->minus && !order)
	{
		if (flags->prec != -1)
			flags->width -= flags->prec >= len ? flags->prec : len;
		else
			flags->width -= len;
		field_in_buff(buff, flags->width, flags->prec != -1 ? 0 : flags->zero);
	}
	else if (order && flags->minus)
	{
		flags->zero = 0;
		if (flags->prec != -1)
			flags->width -= flags->prec >= len ? flags->prec : len;
		else
			flags->width -= len;
		field_in_buff(buff, flags->width, flags->zero);
	}
}

static int	di_flags(t_print *buff, t_flag *flags, intmax_t nb)
{
	int	len;

	len = 0;
	if (flags->zero && flags->prec == -1)
		di_plus_space(buff, flags, nb);
	if (flags->width || flags->prec != -1)
	{
		if (flags->prec != -1)
			flags->prec += (flags->plus || flags->space || nb < 0);
		len = int_len(flags, nb) - (!nb ?
		!(flags->prec - (flags->plus || flags->space || nb < 0)) : 0);
		di_width(buff, flags, len, 0);
		if (!flags->zero || (flags->prec != -1 && flags->zero))
			di_plus_space(buff, flags, nb);
		field_in_buff(buff, flags->prec - len, 16);
	}
	else if (!flags->zero)
		di_plus_space(buff, flags, nb);
	return (len);
}

void		di_conv(t_print *buff, t_flag *flags, intmax_t nb)
{
	char		*dp;
	char		nbr[19];
	uintmax_t	abs;
	int			len;

	abs = nb < 0 ? -nb : nb;
	len = di_flags(buff, flags, nb);
	if (buff->i + 20 >= BS_PRINTF)
		empty_buff(buff);
	if (!abs && flags->prec - (flags->plus || flags->space || nb < 0))
		buff->str[buff->i++] = '0';
	dp = nbr;
	while (abs)
	{
		*dp++ = abs % 10 + 48;
		abs /= 10;
	}
	while (dp != nbr)
		buff->str[buff->i++] = *--dp;
	if (flags->width)
		di_width(buff, flags, len, 1);
}
