/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 00:25:41 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/10 01:21:06 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_bint	*ret_floatpart(t_bint *nb)
{
	t_bint	*begin;
	t_bint	*prev;
	int		restart;

	begin = nb;
	restart = 1;
	while (restart--)
	{
		nb = begin;
		prev = nb;
		nb = nb->next;
		while (nb)
		{
			if (nb->digit >= 10)
			{
				nb->digit -= 10;
				prev->digit += 1;
				restart = 1;
			}
			nb = nb->next;
			prev = prev->next;
		}
	}
	return (begin);
}

t_bint	*ret_intpart(t_bint *nb)
{
	t_bint	*begin;

	begin = nb;
	while (nb)
	{
		if (nb->digit >= 10)
		{
			if (!nb->next)
				if (!(nb->next = init_bint(0)))
					return (NULL);
			nb->digit -= 10;
			nb->next->digit += 1;
		}
		nb = nb->next;
	}
	return (begin);
}

t_bint	*add_bin_exp(t_bint *nb, t_bint *bin_exp)
{
	t_bint	*begin;

	begin = nb;
	while (bin_exp)
	{
		nb->digit += bin_exp->digit;
		if (!nb->next && bin_exp->next)
			if (!(nb->next = init_bint(0)))
				return (NULL);
		nb = nb->next;
		bin_exp = bin_exp->next;
	}
	return (begin);
}

t_bint	*divide_bin_exp(t_bint *bin_exp)
{
	t_bint	*lst;
	int		ret;
	int		tmp;

	ret = 0;
	lst = bin_exp;
	while (lst)
	{
		tmp = lst->digit;
		lst->digit = tmp / 2 + ret;
		ret = (tmp % 2) * 5;
		if (!lst->next && ret)
			if (!(lst->next = init_bint(0)))
				return (NULL);
		lst = lst->next;
	}
	return (bin_exp);
}

t_bint	*double_bin_exp(t_bint *bin_exp)
{
	t_bint	*lst;

	lst = bin_exp;
	while (lst)
	{
		lst->digit *= 2;
		lst = lst->next;
	}
	return (ret_intpart(bin_exp));
}
