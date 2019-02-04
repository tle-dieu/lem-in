/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 18:37:48 by tle-dieu          #+#    #+#             */
/*   Updated: 2018/11/08 18:38:01 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n)
	{
		while (s1[i] && s1[i] == s2[i] && i + 1 < n)
			i++;
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}
