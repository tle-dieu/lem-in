/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 22:06:39 by tle-dieu          #+#    #+#             */
/*   Updated: 2018/11/09 18:31:41 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s)
{
	int		i;
	int		j;

	if (s)
	{
		i = 0;
		j = ft_strlen(s) - 1;
		while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			i++;
		if (!s[i])
			return (ft_strdup(""));
		while (s[j] == ' ' || s[j] == '\t' || s[j] == '\n')
			j--;
		return (ft_strsub(s, i, (j - i + 1)));
	}
	return (NULL);
}
