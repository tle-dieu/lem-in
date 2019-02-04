/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 16:20:24 by tle-dieu          #+#    #+#             */
/*   Updated: 2018/11/16 15:39:26 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strndup(const char *s, size_t len)
{
	char	*new;
	size_t	i;

	if (!(new = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = 0;
	while (i < len && s[i])
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
