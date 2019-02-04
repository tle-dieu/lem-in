/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 17:27:49 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/01/17 15:14:11 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# define BS_GNL 100

int					get_next_line(const int fd, char **line);

typedef struct		s_gnl
{
	char			*str;
	int				fd;
	struct s_gnl	*next;
}					t_gnl;

#endif
