/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 16:08:30 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/06 19:23:49 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <unistd.h>
#include <stdlib.h>

void	print_room(t_room *room)
{
	ft_printf("{red}::::ROOM::::\n");
	while (room)
	{
		ft_printf("{purple} room = {yellow} %s id: %d nb_links: %d X: %d Y: %d", room->name, room->id, room->nb_links, room->x, room->y);
		if (room->place)
		{
			if (room->place == 3)
				ft_printf(" ERROR");
			else
				ft_printf(room->place == 1 ? " START" : " END");
		}
		ft_printf("\n");
		room = room->next;
	}
	ft_printf("{reset}");
}

void	print_pipe(t_pipe *pipe)
{
	ft_printf("{cyan}::::PIPE::::\n");
	while (pipe)
	{
		ft_printf("{purple} pipe = {cyan} %d to %d\n", pipe->from, pipe->to);
		pipe = pipe->next;
	}
	ft_printf("{reset}");
}

int		enough_data(t_room *room, t_pipe *pipe)
{
	int start;

	start = 0;
	if (!pipe)
		return (0);
	while (room)
	{
		if (room->place)
		{
			if (room->place == 3)
				return (0);
			start += room->place;
		}
		room = room->next;
	}
	return (start == 3);
}

t_room **create_graph(t_room *room, t_pipe *pipe, t_infos *infos)
{
	t_room **tab;
	int i;

	tab = (t_room **)malloc(sizeof(t_room *) * (room->id + 2));
	i = room->id;
	tab[i + 1] = NULL;
	while (room)
	{
		tab[i--] = room;
		if (room->place == 1)
			infos->start = room;
		else if (room->place == 2)
			infos->end = room;
		if (room->nb_links && !(room->links = (t_room**)malloc(sizeof(t_room*) * room->nb_links)))
			return (NULL);
		room = room->next;
	}
	while (pipe)
	{
		/* ft_printf("{#80f00d}%s : %d to %s : %d\n{reset}", tab[pipe->from]->name, pipe->from, tab[pipe->to]->name, pipe->to); */
		/* ft_printf("tab[%d]->links[tab[%d]->%d++] = tab[%d]\n", pipe->from, pipe->from, tab[pipe->from]->i, pipe->to); */
		tab[pipe->from]->links[tab[pipe->from]->i++] = tab[pipe->to];
		/* ft_printf("tab[%d]->links[tab[%d]->%d++] = tab[%d]\n", pipe->to, pipe->to, tab[pipe->to]->i, pipe->from); */
		tab[pipe->to]->links[tab[pipe->to]->i++] = tab[pipe->from];
		pipe = pipe->next;
	}
	return (tab);
}

void	print_graph(t_room **tab, t_infos infos)
{
	int i;
	int j;
	int k;

	i = 0;
	ft_printf("{#de4343}");
	ft_printf("\nSTART: %s\nEND: %s\n", infos.start->name, infos.end->name);
	while (tab[i])
	{
		j = 0;
		ft_printf("\n-----%s-----\nid: %d lvl: %d nb_links: %d {#f0ab68}dist: %d\n{#de4343}", tab[i]->name, tab[i]->id, tab[i]->lvl, tab[i]->nb_links, tab[i]->dist);
		while (j < tab[i]->nb_links)
		{
			k = j;
			if (tab[i]->id == tab[i]->links[j]->id)
				ft_printf("{blue}ERROR room vers elle mm\n{reset}");
			while (++k < tab[i]->nb_links)
				if (tab[i]->links[j]->id == tab[i]->links[k]->id)
					ft_printf("{blue}ERROR deux fois mm room\n{reset}");
			ft_printf("{#de4343}  -> nb: %d name: %s id: %d lvl: %d\n", j, tab[i]->links[j]->name, tab[i]->links[j]->id, tab[i]->links[j]->lvl);
			j++;
		}
		i++;
	}
	ft_printf("{reset}");
}

void	get_flow(t_room *room, t_infos infos, int dist)
{
	int i;

	i = 0;
	if (room->dist >= dist)
		room->dist = dist;
	else 
		return ;
	while (i < room->nb_links)
		get_flow(room->links[i++], infos, dist + 1);
	return ;
}

int		split_file(t_file *file)
{
	int i;
	int j;
	int occ;

	file->size = ft_count_words(file->str, '\n');
	if (!(file->split = (char **)malloc(sizeof(char *) * file->size)))
		return (1);
	j = 0;
	i = 0;
	while (j < file->size)
	{
		while (file->str[i] && file->str[i] == '\n')
			i++;
		occ = i;
		while (file->str[i] != '\n' && file->str[i])
			i++;
		file->split[j++] = ft_strsub(file->str, occ, i - occ);
	}
	return (0);
}

int		get_file(t_file *file)
{
	char	*tmp;
	char	buff[BS_LEMIN + 1];
	int		ret;
	int		total_ret;

	total_ret = 0;
	file->str = ft_strnew(0);
	while ((ret = read(0, buff, BS_LEMIN)) && ret != -1)
	{
		buff[ret] = '\0';
		tmp = buff;
		total_ret += ret;
		tmp = file->str;
		if (!(file->str = ft_strjoin(file->str, buff)))
			return (1);
		free(tmp);
	}
	file->len = total_ret;
	return (split_file(file));
}

int		main(void)
{
	t_room *room;
	t_room **tab;
	t_pipe *pipe;
	t_infos infos;
	t_file	file;

	pipe = NULL;
	room = NULL;
	ft_printf("{green}debut\n{reset}");
	if (get_file(&file))
		finish(NULL, "GET FILE ERROR\n", 1);
	ft_printf("fin get_file\n");
	parse_infos(&room, &pipe, &infos.ant, &file);
	ft_printf("{yellow}::::::::::PARSING RESULT::::::::::\n");
	ft_printf("{green}number of ants %d\n", infos.ant);
	if (pipe && room)
	{
		/* print_room(room); */
		/* print_pipe(pipe); */
		tab = create_graph(room, pipe, &infos);
		get_flow(infos.end, infos, 0);
		bfs(infos, room);
		print_graph(tab, infos);
		if (dfs(infos, tab))
			ft_printf("UI\n");
		else
			ft_printf("PAS UI\n");
	}
	if (!enough_data(room, pipe))
	{
		ft_printf("NOT ENOUGH DATA ERROR\n");
		return (1);
	}
	return (0);
}
