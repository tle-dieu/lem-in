/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 18:38:13 by tle-dieu          #+#    #+#             */
/*   Updated: 2018/11/11 11:51:22 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[i] && i < size)
		i++;
	while (src[j] && (j + i + 1 < size))
	{
		dest[j + i] = src[j];
		j++;
	}
	if (i != size)
		dest[j + i] = '\0';
	return (i + ft_strlen(src));
}
