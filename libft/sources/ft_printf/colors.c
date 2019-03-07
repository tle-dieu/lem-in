/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 00:24:00 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/07 15:24:38 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static char	*more_style(char *color)
{
	if (!ft_strcmp("{underline}", color))
		return (ft_strdup("\x1b[4m\0"));
	if (!ft_strcmp("{background}", color))
		return (ft_strdup("\x1b[7m\0"));
	if (!ft_strcmp("{clear}", color))
		return (ft_strdup("\x1b[2J"));
	if (!ft_strcmp("{cursor_home}", color))
		return (ft_strdup("\x1b[H"));
	if (!ft_strcmp("{cursor_save}", color))
		return (ft_strdup("\x1b[s"));
	if (!ft_strcmp("{cursor_restore}", color))
		return (ft_strdup("\x1b[u"));
	if (!ft_strcmp("{cursor_hide}", color))
		return (ft_strdup("\x1b[?25l"));
	if (!ft_strcmp("{cursor_show}", color))
		return (ft_strdup("\x1b[?25h"));
	if (!ft_strcmp("{remove_line}", color))
		return (ft_strdup("\x1b[2K"));
	return (NULL);
}

char		*get_style(char *color)
{
	if (!ft_strcmp("{black}", color) || !ft_strcmp("{black:bg}", color))
		return (ft_strdup("\x1b[30m"));
	if (!ft_strcmp("{red}", color) || !ft_strcmp("{red:bg}", color))
		return (ft_strdup("\x1b[31m"));
	if (!ft_strcmp("{green}", color) || !ft_strcmp("{green:bg}", color))
		return (ft_strdup("\x1b[32m"));
	if (!ft_strcmp("{yellow}", color) || !ft_strcmp("{yellow:bg}", color))
		return (ft_strdup("\x1b[33m"));
	if (!ft_strcmp("{blue}", color) || !ft_strcmp("{blue:bg}", color))
		return (ft_strdup("\x1b[34m"));
	if (!ft_strcmp("{purple}", color) || !ft_strcmp("{purple:bg}", color))
		return (ft_strdup("\x1b[35m"));
	if (!ft_strcmp("{cyan}", color) || !ft_strcmp("{cyan:bg}", color))
		return (ft_strdup("\x1b[36m"));
	if (!ft_strcmp("{white}", color) || !ft_strcmp("{white:bg}", color))
		return (ft_strdup("\x1b[37m"));
	if (!ft_strcmp("{reset}", color))
		return (ft_strdup("\x1b[0m"));
	if (!ft_strcmp("{bold}", color))
		return (ft_strdup("\x1b[1m"));
	if (!ft_strcmp("{low}", color))
		return (ft_strdup("\x1b[2m"));
	if (!ft_strcmp("{italic}", color))
		return (ft_strdup("\x1b[3m"));
	return (more_style(color));
}

static char	*init_rgb(char *str, int r, int g, int b)
{
	const char	*seq = "\x1b[38;2;\0";
	int			rgb[4];
	int			i;
	int			j;
	int			len;

	j = 0;
	i = 0;
	rgb[0] = r;
	rgb[1] = g;
	rgb[2] = b;
	while (*seq)
		str[i++] = *seq++;
	while (j < 3)
	{
		len = 3 - !(rgb[j] / 100) - !(rgb[j] / 10);
		rgb[3] = len;
		while (len && (str[i + --len] = rgb[j] % 10 + 48))
			rgb[j] /= 10;
		i += rgb[3];
		str[i++] = j++ != 2 ? ';' : 'm';
	}
	str[i] = '\0';
	return (ft_strdup(str));
}

char		*hex_color(char *s, char *rgb)
{
	int i;
	int	r;
	int g;
	int b;

	r = 0;
	g = 0;
	b = 0;
	i = 0;
	while (*s && *s != '}' && *s != ':')
	{
		if (i > 6 || (!(*s >= '0' && *s <= '9') && !(*s >= 'a' && *s <= 'f')))
			return (NULL);
		if (i < 2)
			r = r * 16 + (*s >= 'a' && *s <= 'f' ? *s - 'a' + 10 : *s - 48);
		else if (i < 4)
			g = g * 16 + (*s >= 'a' && *s <= 'f' ? *s - 'a' + 10 : *s - 48);
		else
			b = b * 16 + (*s >= 'a' && *s <= 'f' ? *s - 'a' + 10 : *s - 48);
		s++;
		i++;
	}
	if ((*s != '}' && ft_strcmp(s, ":bg}")) || i != 6)
		return (NULL);
	return (init_rgb(rgb, r, g, b));
}

char		*dec_color(char *color, char *rgb)
{
	int r;
	int g;
	int b;

	if (*(color = atoi_jr(color + 5, &r) + 1) != ',')
		return (NULL);
	if (*(color = atoi_jr(color + 1, &g) + 1) != ',')
		return (NULL);
	if ((*(color = atoi_jr(color + 1, &b) + 1) != ')')
	|| (*(color + 1) != '}' && ft_strcmp(color + 1, ":bg}")))
		return (NULL);
	if (r > 255 || b > 255 || g > 255)
		return (NULL);
	return (init_rgb(rgb, r, g, b));
}
