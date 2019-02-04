/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 12:17:31 by tle-dieu          #+#    #+#             */
/*   Updated: 2018/11/08 17:33:01 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t i;

	i = 0;
	while (n-- > 0)
	{
		((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
		if (((unsigned char*)dest)[i] == (unsigned char)c)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
