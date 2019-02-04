/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 18:08:20 by tle-dieu          #+#    #+#             */
/*   Updated: 2018/11/13 17:58:02 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	ft_atoll(const char *nptr)
{
	int					i;
	unsigned long long	result;
	int					sign;

	sign = 1;
	result = 0;
	i = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		result = result * 10 + nptr[i++] - 48;
	if (i > 19 || result >= 9223372036854775808ULL)
		return (sign == 1 ? 9223372036854775807 : -9223372036854775808ull);
	return ((long long)(result * sign));
}
