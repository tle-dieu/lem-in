/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 13:01:09 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/16 18:16:46 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			init_flags(t_flag *flags)
{
	flags->prec = -1;
	flags->space = 0;
	flags->llf = 0;
	flags->l = 0;
	flags->h = 0;
	flags->hashtag = 0;
	flags->j = 0;
	flags->zero = 0;
	flags->minus = 0;
	flags->plus = 0;
	flags->width = 0;
	flags->z = 0;
	return (1);
}

static int	more_flags(va_list args, t_flag *flags, char **format)
{
	int	nb;

	if (**format == '#')
		flags->hashtag = 1;
	else if (**format == '*')
	{
		nb = va_arg(args, int);
		if (*(*format - 1) == '.')
			flags->prec = nb < 0 ? -1 : nb;
		else if (nb < 0)
		{
			flags->minus = 1;
			flags->width = -nb;
		}
		else
			flags->width = nb;
	}
	else if (**format == 'D' || **format == 'O' || **format == 'U')
		return (flags->l += 2);
	else
		return (1);
	return (0);
}

int			get_flags(va_list args, t_flag *flags, char **format)
{
	if (**format == ' ')
		flags->space = 1;
	else if (**format == 'l' || (**format == 'q' && ++(flags->l)))
		flags->l++;
	else if (**format == '.')
		*format = atoi_jr(*format + 1, &flags->prec);
	else if (**format == 'h')
		flags->h++;
	else if (**format > '0' && **format <= '9')
		*format = atoi_jr(*format, &flags->width);
	else if (**format == 'z')
		flags->z++;
	else if (**format == '-')
		flags->minus = 1;
	else if (**format == '+')
		flags->plus = 1;
	else if (**format == 'L')
		flags->llf = 1;
	else if (**format == 'j')
		flags->j = 1;
	else if (**format == '0')
		flags->zero = 16;
	else
		return (more_flags(args, flags, format));
	return (0);
}
