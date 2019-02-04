/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 23:21:42 by tle-dieu          #+#    #+#             */
/*   Updated: 2018/11/30 12:28:00 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char			**ft_strsplit(char const *s, char c)
{
	char	**split;
	size_t	words;
	size_t	i;
	size_t	j;
	size_t	occ;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	if (!(split = (char **)malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	j = 0;
	i = 0;
	while (j < words)
	{
		while (s[i] && s[i] == c)
			i++;
		occ = i;
		while (s[i] != c && s[i])
			i++;
		split[j++] = ft_strsub(s, occ, i - occ);
	}
	split[j] = NULL;
	return (split);
}
