/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 13:30:06 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/25 17:00:24 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

int		error_finish(t_file *file, t_pipe *pipe, t_room *room, char *message)
{
	free_pipe(pipe);
	free_file(file);
	free_room(room);
	if (message)
		ft_printf("%s\n", message);
	return (1);
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
		if (!(s[i] >= '0' && s[i] <= '9')
		|| (nb = nb * 10 + s[i++] - 48) > 2147483647)
			return (-1);
	return (nb);
}

void	print_file(t_file *file)
{
	t_file *next;

	while (file)
	{
		ft_printf("%s\n", file->line);
		next = file->next;
		free(file->line);
		free(file);
		file = next;
	}
	ft_printf("\n");
}
