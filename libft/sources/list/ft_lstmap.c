/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 13:50:31 by tle-dieu          #+#    #+#             */
/*   Updated: 2018/11/12 14:02:00 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *fcpy;

	if (lst)
	{
		if (!(fcpy = (t_list *)malloc(sizeof(t_list))))
			return (NULL);
		fcpy = f(lst);
		if (lst->next)
			fcpy->next = ft_lstmap(lst->next, f);
		return (fcpy);
	}
	return (NULL);
}
