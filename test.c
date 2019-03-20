/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 20:55:27 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/18 22:50:40 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"

int		main(void)
{
	t_list *lst;
	t_list *new;
	int i;

	i = 0;
	while (i++ < 2000)
	{
		if (i == 1)
			lst = ft_lstnew("bonjour\0", 8);
		else
		{
			new = ft_lstnew("bonjour\0", 8);
			new->next = lst;
			lst = new;
		}
	}
	ft_printf("fait\n");
	i = 0;
	while (i++ < 18970)
	{
		new = lst;
		while (new)
			new = new->next;
		ft_printf("\r%d", i);
	}
	ft_printf("\rfin\n");
}
