/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:00:22 by tle-dieu          #+#    #+#             */
/*   Updated: 2018/11/20 16:17:50 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(const char *str)
{
	int					sign;
	int					i;
	unsigned long long	result;

	result = 0;
	i = 0;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	sign = (*str == '-' ? -1 : 1);
	if (*str == '+' || *str == '-')
		str++;
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + str[i++] - 48;
	if (i > 19 || result > 9223372036854775807)
		return (sign < 0 ? 0 : -1);
	return ((int)result * sign);
}
