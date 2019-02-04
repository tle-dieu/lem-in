/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:49:25 by tle-dieu          #+#    #+#             */
/*   Updated: 2018/11/10 15:23:18 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*fcpy;
	size_t	i;

	i = 0;
	if (s && f)
	{
		if (!(fcpy = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
			return (NULL);
		while (s[i])
		{
			fcpy[i] = (*f)(s[i]);
			i++;
		}
		fcpy[i] = '\0';
		return (fcpy);
	}
	return (NULL);
}
