/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 13:30:06 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/02/14 16:56:56 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

void	finish(char *line, char *message, int error)
{
	ft_printf("%s", message);
	free(line);
	exit(error);
}

int		atoi_parsing(char const *s)
{
	long int	nb;
	int			i;

	nb = 0;
	i = 0;
	if (*s == '+')
		i++;
	while (s[i])
		if (!(s[i] >= '0' && s[i] <= '9') || (nb = nb * 10 + s[i++] - 48) > 2147483647)
			return (-1);
	return (nb);
}
