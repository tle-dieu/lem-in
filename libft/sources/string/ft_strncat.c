/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 18:14:14 by tle-dieu          #+#    #+#             */
/*   Updated: 2018/11/08 18:17:05 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t i;

	i = 0;
	while (dest[i])
		i++;
	n += i;
	while (*src && i < n)
		dest[i++] = *src++;
	dest[i] = '\0';
	return (dest);
}
