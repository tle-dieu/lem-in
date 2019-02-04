/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_lcls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 11:16:18 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/16 18:19:00 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static int	wchar_in_buff(t_print *buff, wint_t c, int len)
{
	if (buff->i + len >= BS_PRINTF)
		empty_buff(buff);
	if (len == 1 || (MB_CUR_MAX == 1 && c <= 255))
	{
		buff->str[buff->i++] = (char)c;
		return (len);
	}
	else if (len == 2)
		buff->str[buff->i++] = 0xc0 | (c >> 6);
	else
		buff->str[buff->i++] = len == 3 ? 0xe0 | (c >> 12) : 0xf0 | (c >> 18);
	if (len == 4)
		buff->str[buff->i++] = 0x80 | ((c >> 12) & ~0xc0);
	if (len >= 3)
		buff->str[buff->i++] = 0x80 | ((c >> 6) & ~0xc0);
	buff->str[buff->i++] = 0x80 | (c & ~0xc0);
	return (len);
}

static int	check_wchar(t_print *buff, t_flag *flags, char **format, wchar_t *s)
{
	int len;
	int k;
	int i;

	len = 0;
	i = 0;
	while (*s)
	{
		k = (*s >> 16 != 0) + (*s >> 11 != 0) + (*s >> 7 != 0) + 1;
		if ((MB_CUR_MAX == 1 && *s > 255) || *s < 0 || *s > 0x110000)
		{
			while (*(*format + 1))
				++(*format);
			buff->error = 1;
			return (-1);
		}
		if (!i && flags->prec != -1 && len + k > flags->prec)
			return (len);
		len += k;
		s++;
	}
	return (len);
}

void		ls_conv(t_print *buff, t_flag *flags, char **format, wchar_t *s)
{
	int k;
	int len;
	int tmp;

	if (!s)
		return (s_conv(buff, flags, NULL));
	if ((len = check_wchar(buff, flags, format, s)) == -1)
		return ;
	if (flags->width)
	{
		tmp = len;
		if (flags->prec != -1)
			len = (len > flags->prec ? flags->prec : len);
		if (!flags->minus)
			field_in_buff(buff, flags->width - len, flags->zero);
	}
	while (*s && (k = (*s >> 16 != 0) + (*s >> 11 != 0) + (*s >> 7 != 0) + 1))
	{
		if (flags->prec != -1 && (flags->prec -= k) < 0)
			break ;
		len -= wchar_in_buff(buff, (wint_t)*s++, k);
	}
	if (flags->width && flags->minus)
		field_in_buff(buff, flags->width - tmp, 0);
}

void		lc_conv(t_print *buff, t_flag *flags, char **format, wint_t c)
{
	int len;

	len = (c >> 16 != 0) + (c >> 11 != 0) + (c >> 7 != 0) + 1;
	if ((MB_CUR_MAX == 1 && c > 255) || c < 0 || c > 0x110000)
	{
		while (*(*format + 1))
			++(*format);
		buff->error = 1;
		return ;
	}
	if (len == 1 || (MB_CUR_MAX == 1 && c <= 255))
		return (c_conv(buff, flags, (int)c));
	if (flags->width > len && !flags->minus)
		field_in_buff(buff, flags->width - len, flags->zero);
	wchar_in_buff(buff, c, len);
	if (flags->width && flags->minus)
		field_in_buff(buff, flags->width - len, 0);
}
