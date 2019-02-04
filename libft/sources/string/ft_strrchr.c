/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 18:14:44 by tle-dieu          #+#    #+#             */
/*   Updated: 2018/11/09 19:26:05 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	char *temp;

	temp = ft_strchr(s, '\0');
	while (temp >= s)
	{
		if (*temp == (unsigned char)c)
			return ((char *)temp);
		temp--;
	}
	return (NULL);
}
