/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <tle-dieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:59:46 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/21 13:00:38 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

int     free_queue(t_queue *queue)
{
    t_queue *next;

    while (queue)
    {
        next = queue->next;
        free(queue);
        queue = next;
    }
    return (0);
}
