/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 18:16:13 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/02/22 18:18:43 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include <stdlib.h>

int		main(void)
{
	char *line;

	while (get_next_line(0, &line) == 1)
		free(line);
	ft_printf("FIN\n");
}
