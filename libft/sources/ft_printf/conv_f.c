/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 00:24:58 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/16 18:15:42 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ftoa(t_float *f, double d, int prec)
{
	get_fbinary(f, ((unsigned char *)&d));
	if (f->exp == 2047)
		return (special_case(f->mantissa));
	f->intpart = get_intpart(f->mantissa, f->size, f->exp - 1022);
	if ((f->floatpart = get_floatpart(f->mantissa, f->size, f->exp - 1022)))
		f->floatpart = apply_prec(f->intpart, f->floatpart, prec);
	return (0);
}

static int	lftoa(t_float *f, long double ld, int prec)
{
	get_lfbinary(f, ((unsigned char *)&ld));
	if (f->exp == 32767)
		return (special_case(f->mantissa));
	f->intpart = get_intpart(f->mantissa, f->size, f->exp - 16382);
	if ((f->floatpart = get_floatpart(f->mantissa, f->size, f->exp - 16382)))
		f->floatpart = apply_prec(f->intpart, f->floatpart, prec);
	return (0);
}

static void	f_plus_space(t_print *buff, t_flag *flags, int sign)
{
	if (buff->i >= BS_PRINTF)
		empty_buff(buff);
	if (!sign)
	{
		if (flags->plus || flags->space)
			buff->str[buff->i++] = flags->plus ? '+' : ' ';
	}
	else
		buff->str[buff->i++] = '-';
}

static void	f_in_buff(t_print *buff, t_flag *flags, t_float *f, int i)
{
	t_bint *lst;

	if ((lst = f->intpart) && !flags->zero)
		f_plus_space(buff, flags, f->sign);
	buff->i += i;
	if (f->floatpart || flags->hashtag)
		buff->str[--buff->i] = '.';
	while (f->intpart)
	{
		buff->str[--buff->i] = f->intpart->digit + 48;
		f->intpart = f->intpart->next;
	}
	free_bint(&lst);
	buff->i += i;
	lst = f->floatpart;
	while (f->floatpart)
	{
		if (buff->i >= BS_PRINTF)
			empty_buff(buff);
		buff->str[buff->i++] = f->floatpart->digit + 48;
		f->floatpart = f->floatpart->next;
	}
	free_bint(&lst);
	if (flags->width && flags->minus)
		field_in_buff(buff, flags->width, flags->zero);
}

void		f_conv(va_list args, t_print *buff, t_flag *flags, char conv)
{
	t_float		f;
	int			i;

	flags->prec = (flags->prec == -1 ? 6 : flags->prec);
	i = flags->llf ? lftoa(&f, va_arg(args, long double), flags->prec)
	: ftoa(&f, va_arg(args, double), flags->prec);
	if (i && (flags->prec = -1))
	{
		flags->zero = 0;
		s_conv(buff, flags, get_specialf(f.sign, i, conv));
		return ;
	}
	i = bint_len(f.intpart) + ((f.floatpart || flags->hashtag) ? 1 : 0);
	if (flags->zero)
		f_plus_space(buff, flags, f.sign);
	if (flags->width)
	{
		flags->width -= i + flags->prec;
		flags->width -= (f.sign || flags->space || flags->plus);
		if (!flags->minus)
			field_in_buff(buff, flags->width, flags->zero);
	}
	if (buff->i + i >= BS_PRINTF)
		empty_buff(buff);
	f_in_buff(buff, flags, &f, i);
}
