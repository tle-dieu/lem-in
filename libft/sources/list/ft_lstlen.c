/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 12:28:27 by tle-dieu          #+#    #+#             */
/*   Updated: 2018/11/12 12:28:33 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstlen(t_list *begin_list)
{
	int		i;

	i = 0;
	if (begin_list)
	{
		while (begin_list->next)
		{
			begin_list = begin_list->next;
			i++;
		}
		i++;
	}
	return (i);
}
