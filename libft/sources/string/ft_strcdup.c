/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 16:23:40 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/02/01 19:18:29 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strcdup(const char *s, char c)
{
	char	*new;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] != c && s[i])
		i++;
	if (!(new = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	while (j < i)
	{
		new[j] = s[j];
		j++;
	}
	new[j] = '\0';
	return (new);
}
