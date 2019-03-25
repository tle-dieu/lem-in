/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_oux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 17:58:57 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/07 15:26:43 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	oux_width(t_print *buff, t_flag *flags, int len, int order)
{
	if (!flags->minus && !order)
	{
		if (flags->prec >= 0)
		{
			flags->zero = 0;
			flags->width -= flags->prec > len ? flags->prec : len;
		}
		else
			flags->width -= len;
		field_in_buff(buff, flags->width, flags->zero);
	}
	else if (order && flags->minus)
	{
		flags->zero = 0;
		if (flags->prec >= 0)
			flags->width -= flags->prec > len ? flags->prec : len;
		else
			flags->width -= len;
		field_in_buff(buff, flags->width, flags->zero);
	}
}

static void	oux_hashtag(t_print *buff, t_flag *flags, char base, int order)
{
	if (base != '9')
	{
		if (!order)
		{
			if (flags->zero && flags->prec < 0)
			{
				buff->str[buff->i++] = '0';
				if (base == 'f' || base == 'F')
					buff->str[buff->i++] = base + 18;
			}
			else if (flags->prec != -1 && flags->prec)
				flags->prec -= base == '7' ? 1 : 0;
			flags->width -= base == '7' ? 1 : 2;
		}
		else if (order == 2 || !flags->zero || flags->prec >= 0)
		{
			buff->str[buff->i++] = '0';
			if (base == 'f' || base == 'F')
				buff->str[buff->i++] = base + 18;
		}
	}
}

static int	oux_flags(t_print *buff, t_flag *flags, uintmax_t nb, char *base)
{
	int	len;
	int	b_len;

	len = 0;
	b_len = !base[2] ? 2 : 8;
	if (b_len != 2 && base[8])
		b_len = !base[10] ? 10 : 16;
	if (flags->width || flags->prec != -1)
	{
		if (flags->hashtag && nb)
			oux_hashtag(buff, flags, base[b_len - 1], 0);
		else if (flags->hashtag && b_len == 8 && !flags->prec)
		{
			flags->prec -= 1;
			flags->zero = 0;
		}
		len = base_len(nb, b_len) - (!nb && !flags->prec);
		oux_width(buff, flags, len, 0);
		if (flags->hashtag && nb)
			oux_hashtag(buff, flags, base[b_len - 1], 1);
		field_in_buff(buff, flags->prec - len, 16);
	}
	else if (flags->hashtag && nb)
		oux_hashtag(buff, flags, base[b_len - 1], 2);
	return (len);
}

void		oux_conv(t_print *buff, t_flag *flags, uintmax_t nb, char *base)
{
	char	*dp;
	char	nbr[64];
	int		len;
	int		b_len;

	len = oux_flags(buff, flags, nb, base);
	if (buff->i + 24 >= BS_PRINTF)
		empty_buff(buff);
	b_len = !base[2] ? 2 : 8;
	if (b_len != 2 && base[8])
		b_len = !base[10] ? 10 : 16;
	if (!nb && (flags->prec || (flags->hashtag && !flags->prec && b_len == 8)))
		buff->str[buff->i++] = '0';
	dp = nbr;
	while (nb)
	{
		*dp++ = base[nb % b_len];
		nb /= b_len;
	}
	b_len = dp - nbr;
	while (dp != nbr)
		buff->str[buff->i++] = *--dp;
	if (flags->width)
		oux_width(buff, flags, len, 1);
}
