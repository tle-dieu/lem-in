/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 16:08:30 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/25 03:25:18 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_pipe	*pipe;
	t_lemin	l;
	t_file	*file;

	pipe = NULL;
	file = NULL;
	l = (t_lemin){-1, 0, 0, 0, 0, NULL, NULL, NULL};
	if (!(parse(&l, &pipe, &file)))
		return (error_finish(file, pipe, l.room, "ERROR\n"));
	if (!(assign_pipe(l.room, pipe, l.nb_room)))
		return (error_finish(file, pipe, l.room, "ERROR\n"));
	if (start_to_end(&l, file))
		return (!error_finish(NULL, pipe, l.room, NULL));
	if (edmonds_karp(&l))
	{
		if (!(send_ants(&l, file)))
			return (error_finish(file, pipe, l.room, "ERROR\n"));
	}
	else
		return (error_finish(file, pipe, l.room, "ERROR\n"));
	return (!error_finish(NULL, pipe, l.room, NULL));
}
