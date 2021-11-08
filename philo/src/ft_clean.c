/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brattles <brattles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 01:49:33 by brattles          #+#    #+#             */
/*   Updated: 2021/11/07 13:50:24 by brattles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_phil(t_phil *phils, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		free(phils[i].phil);
		++i;
	}
}

void	ft_free_run(t_table **table, t_settings **settings, \
			pthread_mutex_t **forks, t_phil **phils)
{
	free_phil(*phils, (*settings)->num_of_phil);
	free(*forks);
	*forks = NULL;
	free(*phils);
	*phils = NULL;
	free(*settings);
	*settings = NULL;
	free(*table);
	*table = NULL;
}

int	ft_party_is_over(t_phil *phil, int num, pthread_mutex_t *forks)
{
	int			i;
	pthread_t	thread;

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
