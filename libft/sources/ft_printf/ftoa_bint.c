/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa_bint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 00:25:32 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/14 12:46:20 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

t_bint	*apply_prec(t_bint *intpart, t_bint *floatpart, int p)
{
	int		len;
	t_bint	*lst;
	t_bint	*cut;

	len = 0;
	lst = floatpart;
	while (++len < p)
	{
		if (!floatpart->next && !(floatpart->next = init_bint(0)))
			return (NULL);
		floatpart = floatpart->next;
	}
	if (!p || (p == len && floatpart->next))
	{
		cut = p ? floatpart->next : floatpart;
		if (cut->digit > 5 || (cut->digit == 5 &&
		(((p ? floatpart->digit : intpart->digit) % 2)
		|| (cut->next && (cut->next->digit || cut->next->next)))))
			floatpart->digit = p ? floatpart->digit + 1 : 10;
		if (ret_floatpart(lst) && lst->digit > 9 && (intpart->digit += 1))
			lst->digit -= 10;
		ret_intpart(intpart);
		free_bint(p ? &(floatpart->next) : &lst);
	}
	return (lst);
}

t_bint	*get_floatpart(char *mantissa, int size, int exp)
{
	t_bint *floatpart;
	t_bint *bin_exp;

	if (!(bin_exp = init_bint(5)))
		return (NULL);
	if (!(floatpart = init_bint(0)))
		return (NULL);
	if (*mantissa != '1')
		mantissa++;
	while (exp < size)
	{
		if (exp >= 0 && mantissa[exp] == '1')
		{
			if (!add_bin_exp(floatpart, bin_exp) || !ret_floatpart(floatpart))
				break ;
		}
		if (!divide_bin_exp(bin_exp))
			break ;
		exp++;
	}
	free_bint(&bin_exp);
	return (floatpart);
}

t_bint	*get_intpart(char *mantissa, int size, int exp)
{
	t_bint	*intpart;
	t_bint	*bin_exp;

	if (!(bin_exp = init_bint(1)))
		return (NULL);
	if (!(intpart = init_bint(0)))
		return (NULL);
	while (exp-- > 0)
	{
		if (exp < size && mantissa[exp] == '1')
			if (!add_bin_exp(intpart, bin_exp) || !ret_intpart(intpart))
				break ;
		if (!double_bin_exp(bin_exp))
			break ;
	}
	free_bint(&bin_exp);
	return (intpart);
}
