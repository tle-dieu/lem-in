/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 12:30:29 by tle-dieu          #+#    #+#             */
/*   Updated: 2018/11/12 12:30:30 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind(t_list *begin_list, void *data_ref, int (*cmp)())
{
	t_list *list;

	list = begin_list;
	if (!begin_list)
		return (NULL);
	while (list)
	{
		if (cmp(list->content, data_ref) == 0)
			return (list);
		list = list->next;
	}
	return (0);
}
