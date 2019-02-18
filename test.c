/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 19:11:53 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/02/18 19:48:16 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include <string.h>
#include <time.h>
#include <stdio.h>

int ft_strcmp3(const char *p1, const char *p2)
{
  register const unsigned char *s1 = (const unsigned char *) p1;
  register const unsigned char *s2 = (const unsigned char *) p2;
  unsigned c1, c2;

  do
    {
      c1 = (unsigned char) *s1++;
      c2 = (unsigned char) *s2++;
      if (c1 == '\0')
	return c1 - c2;
    }
  while (c1 == c2);

  return c1 - c2;
}
int ft_strcmp2(const char *s1, const char *s2)
{
	while (*s1 == *s2++)
		if (*s1++ == '\0')
	    	return (0);
    return ((*(unsigned char *)s1 < *(unsigned char *)(s2 - 1)) ? -1 : +1);
}

int		main(int ac, char **av)
{
     clock_t start, end;
     double cpu_time_used;
	 int i;

	if (ac >= 3)
	{
		i = 0;
     	start = clock();
		while (i++ < 100000)
			if (!strcmp(av[1], av[2]))
				break ;
     	end = clock();
     	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("time strcmp:     %lf\n", cpu_time_used);
		i = 0;
     	start = clock();
		while (i++ < 100000)
			if (!ft_strcmp(av[1], av[2]))
				break ;
     	end = clock();
     	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("time ft_strcmp:  %lf\n", cpu_time_used);
		i = 0;
     	start = clock();
		while (i++ < 100000)
			if (!ft_strcmp2(av[1], av[2]))
				break ;
     	end = clock();
     	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("time ft_strcmp2: %lf\n", cpu_time_used);
		i = 0;
     	start = clock();
		while (i++ < 100000)
			if (!ft_strcmp3(av[1], av[2]))
				break ;
     	end = clock();
     	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("time ft_strcmp3: %lf\n", cpu_time_used);
	}
}
