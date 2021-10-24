/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brattles <brattles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 01:49:33 by brattles          #+#    #+#             */
/*   Updated: 2021/09/28 01:20:41 by brattles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_party_is_over(t_phil *phil, int num, pthread_mutex_t *forks)
{
	int	i;
	pthread_t		thread;

	i = 0;
	while (i < num)
	{
		thread = *(phil[i].phil);
		pthread_detach(thread);
		pthread_mutex_destroy(&forks[i]);
		++i;
	}
	return (EXIT_SUCCESS);
}
