/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 18:13:59 by tle-dieu          #+#    #+#             */
/*   Updated: 2018/11/08 18:14:07 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t i;
	size_t j;

	i = 0;
	if (!*little)
		return ((char *)big);
	while (big[i] && i < n)
	{
		j = 0;
		while (big[i + j] == little[j] && little[j] && i + j < n)
			j++;
		if (!little[j])
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
