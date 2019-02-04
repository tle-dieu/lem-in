/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:29:52 by tle-dieu          #+#    #+#             */
/*   Updated: 2018/11/08 17:40:40 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char *new;

	if (!(new = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	ft_bzero(new, size + 1);
	return (new);
}
