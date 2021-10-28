/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utl2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brattles <brattles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 01:01:22 by brattles          #+#    #+#             */
/*   Updated: 2021/10/27 22:30:37 by brattles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_death_record(t_table *table, int i)
{
	t_phil	*diogenes;

	diogenes = table->phil;
	printf("%s%s%s%10lu   %5d   died%s\n", BEEP, FBLACK, BRED, \
		ft_chronometer() - table->settings->start_time, \
		diogenes[i].phil_id, NONE);
	ft_party_is_over(table->phil, table->settings->num_of_phil, table->forks);
}

int	check_if_dead(t_phil *diogenes)
{
	if (ft_chronometer() - diogenes->eat_last_time > \
		(uint64_t)diogenes->settings->time_to_die)
		return (1);
	return (0);
}

static bool	ft_kostili(t_table *table, t_phil *diogenes)
{
	int	i;

	i = -1;
	while (++i < table->settings->num_of_phil)
	{
		if (check_if_dead(&diogenes[i]))
		{
			ft_death_record(table, i);
			return (true);
		}
		if (diogenes[i].well_fed == true)
		{
			diogenes[i].well_fed = false;
			++table->finished;
			if (table->finished >= table->settings->num_of_phil)
			{
				ft_party_is_over(table->phil, \
					table->settings->num_of_phil, table->forks);
				return (true);
			}
		}
	}
	return (false);
}

void	ft_heartbeat_monitor(t_table *table)
{
	t_phil	*diogenes;
	bool	status;

	diogenes = table->phil;
	while (true)
	{
		status = ft_kostili(table, diogenes);
		if (status)
			return ;
	}
	usleep(50);
}
