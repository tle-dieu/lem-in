/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 16:43:49 by tle-dieu          #+#    #+#             */
/*   Updated: 2018/11/26 14:09:49 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_count_words(char const *s, char c)
{
	size_t words;

	words = 0;
	while (*s)
	{
		if (*s != c)
			words++;
		while (*s != c && *s)
			s++;
		while (*s && *s == c)
			s++;
	}
	return (words);
}
