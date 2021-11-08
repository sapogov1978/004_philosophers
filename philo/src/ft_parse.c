/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brattles <brattles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 01:53:27 by brattles          #+#    #+#             */
/*   Updated: 2021/11/07 13:48:43 by brattles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_horde_is_coming(t_table *table, t_phil *phils, \
	pthread_mutex_t *forks, t_settings *settings)
{
	int				i;

	i = -1;
	table->phil = phils;
	table->settings = settings;
	table->forks = forks;
	settings->start_time = ft_chronometer();
	table->finished = 0;
	while (++i < settings->num_of_phil)
	{
		phils[i].eat_last_time = settings->start_time;
		phils[i].settings = settings;
		phils[i].well_fed = false;
		pthread_create(phils[i].phil, NULL, (void *)lifecycle, &phils[i]);
	}
	ft_heartbeat_monitor(table);
	return (0);
}

static t_phil	*ft_init_phils(int num_of_phil, pthread_mutex_t *forks)
{
	t_phil			*phils;
	int				i;

	i = -1;
	phils = (t_phil *)malloc(sizeof(t_phil) * num_of_phil);
	if (!phils)
		return (NULL);
	while (++i < num_of_phil)
	{
		phils[i].need_check = true;
		phils[i].phil_numb = i + 1;
		phils[i].eat_complete_counter = 0;
		phils[i].phil = (pthread_t *)malloc(sizeof(pthread_t));
		if (!phils[i].phil)
			return (NULL);
		phils[i].r_fork = &forks[i - 1];
		if (i == 0)
		{
			phils[i].l_fork = &forks[0];
			phils[i].r_fork = &forks[num_of_phil - 1];
		}
		else
			phils[i].l_fork = &forks[i];
	}
	return (phils);
}

static	pthread_mutex_t	*ft_init_forks(int num_of_phil)
{
	pthread_mutex_t	*forks;
	int				i;

	i = -1;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num_of_phil);
	if (!forks)
		return (NULL);
	while (++i < num_of_phil)
		pthread_mutex_init(&forks[i], NULL);
	return (forks);
}

static t_settings	*ft_parse(t_settings *settings, int argc, char **argv)
{
	settings = (t_settings *)malloc(sizeof(t_settings));
	if (!settings)
		return (NULL);
	settings->num_of_phil = ft_atoi(argv[1]);
	settings->time_to_die = ft_atoi(argv[2]);
	settings->time_to_eat = ft_atoi(argv[3]) * 1000;
	settings->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		settings->n_times_to_eat = ft_atoi(argv[5]);
	else
		settings->n_times_to_eat = INT_MAX;
	return (settings);
}

int	ft_parse_and_init(t_table *table, int argc, char **argv)
{
	t_settings		*settings;
	pthread_mutex_t	*forks;
	t_phil			*phils;

	settings = ft_parse(table->settings, argc, argv);
	forks = ft_init_forks(settings->num_of_phil);
	phils = ft_init_phils(settings->num_of_phil, forks);
	if (!settings || !forks || !phils)
		return (ft_panic("Memory allocation error", &table));
	if (settings->num_of_phil < 1 || settings->time_to_die < 1 \
		|| settings->time_to_eat < 1 || settings->time_to_sleep < 1)
		return (ft_panic("Incorrect argument", &table));
	if (settings->n_times_to_eat < 1)
		return (ft_panic("Incorrect optional arguments", &table));
	if (ft_horde_is_coming(table, phils, forks, settings) == 0)
	{
		ft_free_run (&table, &settings, &forks, &phils);
		return (0);
	}
	else
		return (ft_panic("Thread creation error", &table));
}
