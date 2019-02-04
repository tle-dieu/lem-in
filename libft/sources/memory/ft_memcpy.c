/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 10:55:52 by tle-dieu          #+#    #+#             */
/*   Updated: 2018/11/27 18:48:20 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	if (!dest && !src)
		return (NULL);
	while (n-- > 0)
	{
		((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
	}
	return (dest);
}
