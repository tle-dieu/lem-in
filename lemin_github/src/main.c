/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 08:41:56 by cpireyre          #+#    #+#             */
/*   Updated: 2018/12/18 11:08:53 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_listarray		metakarp(t_lemin *lemin)
{
	t_listarray	g;
	int			steps;
	t_lemin		cpy;

	ft_memcpy(&cpy, lemin, sizeof(t_lemin));
	g = build_graph(&cpy);
	steps = edmonds_karp(g, &cpy, -1);
	if (!steps)
	{
		free_graph(g, cpy.map_size);
		return (NULL);
	}
	free_graph(g, cpy.map_size);
	g = build_graph(lemin);
	edmonds_karp(g, lemin, steps);
	return (g);
}

void			solve(t_lemin *lemin)
{
	t_list		**s;

	s = metakarp(lemin);
	if (s && lemin->flow > 0)
	{
		ft_putchar('\n');
		ft_lstdel(&lemin->path_lengths, &ft_free_node);
		send_ants(s, lemin);
	}
	else
		ft_putendl("ERROR");
	free_graph(s, lemin->map_size);
}

int				main(int argc, char **argv)
{
	t_list		*usr_in;
	t_list		*tmp;
	t_lemin		lemin;

	ft_bzero(&lemin, sizeof(t_lemin));
	if (!(ft_options(argc, argv) ^ 21264))
		lemin.ant_display = ANT_DISPLAY;
	else
		lemin.ant_display = "L";
	usr_in = ft_stdin_to_list();
	tmp = usr_in;
	parse(&usr_in, &tmp, &lemin);
	buf_print_list(tmp);
	solve(&lemin);
	quit_lem_in(&tmp, &lemin, "", EXIT_SUCCESS);
}
