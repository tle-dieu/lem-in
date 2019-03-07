/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 20:04:11 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/07 15:26:35 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static int	more_conv(va_list args, t_print *buff, t_flag *flags, char **format)
{
	if (**format == 'b')
		oux_conv(buff, flags, get_unsigned(args, flags), "01\0");
	else if (**format == 'C' || **format == 'c')
		lc_conv(buff, flags, format, va_arg(args, wint_t));
	else if (**format == 'S' || **format == 's')
		ls_conv(buff, flags, format, va_arg(args, wchar_t *));
	else if (flags->width)
		c_conv(buff, flags, **format);
	else
		return (0);
	return (1);
}

static int	get_conv(va_list args, t_print *buff, t_flag *flags, char **format)
{
	if (**format == 's' && !flags->l)
		s_conv(buff, flags, va_arg(args, char *));
	else if (**format == 'd' || **format == 'i' || **format == 'D')
		di_conv(buff, flags, get_signed(args, flags));
	else if (**format == 'c' && !flags->l)
		c_conv(buff, flags, va_arg(args, int));
	else if (**format == '%')
		c_conv(buff, flags, '%');
	else if (**format == 'u' || **format == 'U')
		oux_conv(buff, flags, get_unsigned(args, flags), "0123456789\0");
	else if (**format == 'x')
		oux_conv(buff, flags, get_unsigned(args, flags), "0123456789abcdef\0");
	else if (**format == 'X')
		oux_conv(buff, flags, get_unsigned(args, flags), "0123456789ABCDEF\0");
	else if (**format == 'p')
		p_conv(buff, flags, va_arg(args, uintmax_t));
	else if (**format == 'o' || **format == 'O')
		oux_conv(buff, flags, get_unsigned(args, flags), "01234567\0");
	else if (**format == 'f' || **format == 'F')
		f_conv(args, buff, flags, **format);
	else
		return (more_conv(args, buff, flags, format));
	return (1);
}

static int	check_color(t_print *buff, char **format)
{
	char	*s;
	char	col[22];
	char	rgb[20];
	int		i;

	i = 0;
	s = *format;
	while (i < 20 && *s != '}' && *s)
		col[i++] = *s++;
	if (!(*s == '}'))
		return (0);
	col[i++] = *s;
	col[i] = '\0';
	s = NULL;
	if (!ft_strncmp(col, "{rgb(", 5) || !ft_strncmp(col, "{#", 2))
		s = (col[1] == '#' ? hex_color(col + 2, rgb) : dec_color(col, rgb));
	else
		s = get_style(col);
	if (s)
	{
		*format += i;
		color_in_buff(buff, get_bg(col, s));
	}
	return (s ? 1 : 0);
}

static void	apply_format(va_list args, t_print *buff, char const *format)
{
	int		color;
	t_flag	flags;

	while (*format)
	{
		color = 0;
		if (*format == '{')
			color = check_color(buff, (char **)&format);
		if (*format == '%' && init_flags(&flags))
		{
			while (*++format && !get_flags(args, &flags, (char **)&format))
				;
			if (get_conv(args, buff, &flags, (char **)&format))
				format++;
		}
		else if (!color)
		{
			if (buff->i >= BS_PRINTF)
				empty_buff(buff);
			buff->str[buff->i++] = *format++;
		}
	}
}

int			ft_printf(char const *format, ...)
{
	va_list	args;
	t_print	buff;

	if (!format)
		return (-1);
	va_start(args, format);
	buff.i = 0;
	buff.total = 0;
	buff.error = 0;
	buff.fd = 1;
	apply_format(args, &buff, format);
	empty_buff(&buff);
	va_end(args);
	return (buff.error ? -1 : buff.total);
}
