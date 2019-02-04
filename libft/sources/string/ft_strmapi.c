/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:57:48 by tle-dieu          #+#    #+#             */
/*   Updated: 2018/11/10 15:24:17 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*fcpy;
	unsigned int	i;

	if (s && f)
	{
		if (!(fcpy = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
			return (NULL);
		i = 0;
		while (s[i])
		{
			fcpy[i] = (*f)(i, s[i]);
			i++;
		}
		fcpy[i] = '\0';
		return (fcpy);
	}
	return (NULL);
}
