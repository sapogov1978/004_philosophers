/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lifecycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brattles <brattles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 01:55:35 by brattles          #+#    #+#             */
/*   Updated: 2021/10/27 22:47:45 by brattles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_sleep(t_phil *diogenes, t_settings *settings)
{
	printf("%10lu   %5d   is sleeping\n", \
		ft_chronometer() - settings->start_time, diogenes->phil_id);
	usleep(settings->time_to_sleep);
}

static void	ft_eat(t_phil *diogenes, t_settings *settings)
{
	printf("%10lu   %5d   is eating\n", \
		ft_chronometer() - settings->start_time, diogenes->phil_id);
	diogenes->eat_last_time = ft_chronometer();
	usleep(settings->time_to_eat);
}

static void	ft_take_fork(t_phil *diogenes, t_settings *settings)
{
	if (diogenes->phil_id % 2 == 0)
	{
		pthread_mutex_lock(diogenes->r_fork);
		printf("%10lu   %5d   has taken a fork\n", \
			ft_chronometer() - settings->start_time, diogenes->phil_id);
		pthread_mutex_lock(diogenes->l_fork);
		printf("%10lu   %5d   has taken a fork\n", \
			ft_chronometer() - settings->start_time, diogenes->phil_id);
	}
	else
	{
		pthread_mutex_lock(diogenes->l_fork);
		printf("%10lu   %5d   has taken a fork\n", \
			ft_chronometer() - settings->start_time, diogenes->phil_id);
		pthread_mutex_lock(diogenes->r_fork);
		printf("%10lu   %5d   has taken a fork\n", \
			ft_chronometer() - settings->start_time, diogenes->phil_id);
	}
}

void	*lifecycle(void *phil)
{
	t_phil	*ph;

	ph = (t_phil *)phil;
	while (1)
	{
		ft_take_fork(phil, ph->settings);
		ft_eat(ph, ph->settings);
//		ph->eat_last_time = ft_chronometer();
		pthread_mutex_unlock(ph->r_fork);
		pthread_mutex_unlock(ph->l_fork);
		ft_sleep(ph, ph->settings);
		printf("%10lu   %5d   is thinking\n", \
			ft_chronometer() - ph->settings->start_time, ph->phil_id);
		++ph->eat_complete_counter;
		if (ph->eat_complete_counter == ph->settings->n_times_to_eat)
		{
			ph->well_fed = true;
			return (NULL);
		}
	}
	return (NULL);
}
