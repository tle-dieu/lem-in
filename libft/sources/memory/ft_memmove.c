/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 12:22:51 by tle-dieu          #+#    #+#             */
/*   Updated: 2018/11/13 17:41:09 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*c_dest;
	unsigned char	*c_src;
	size_t			i;

	c_dest = (unsigned char *)dest;
	c_src = (unsigned char *)src;
	i = 0;
	if (c_dest > c_src)
		while (n-- > 0)
			c_dest[n] = c_src[n];
	else
		while (i < n)
		{
			c_dest[i] = c_src[i];
			i++;
		}
	return (dest);
}
