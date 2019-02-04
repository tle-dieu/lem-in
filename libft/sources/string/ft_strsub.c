/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 21:30:46 by tle-dieu          #+#    #+#             */
/*   Updated: 2018/11/08 18:01:02 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	if (s)
	{
		i = 0;
		if (!(new = (char *)malloc(sizeof(char) * len + 1)))
			return (NULL);
		while (len--)
		{
			new[i] = s[start + i];
			i++;
		}
		new[i] = '\0';
		return (new);
	}
	return (NULL);
}
