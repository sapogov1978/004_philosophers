/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utl2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brattles <brattles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 01:01:22 by brattles          #+#    #+#             */
/*   Updated: 2021/11/07 13:47:15 by brattles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_death_record(t_table *table, int i)
{
	t_phil	*diogenes;

	diogenes = table->phil;
	printf("%s%s%s%lu %d died%s\n", BEEP, FBLACK, BRED, \
		ft_chronometer() - table->settings->start_time, \
		diogenes[i].phil_numb, NONE);
	ft_party_is_over(table->phil, table->settings->num_of_phil, table->forks);
}

int	check_if_dead(t_phil *ph)
{
	if (ft_chronometer() - ph->eat_last_time > \
		(uint64_t)ph->settings->time_to_die && ph->need_check)
		return (1);
	return (0);
}

static bool	ft_norm_is_a_pain(t_table *table, t_phil *diogenes)
{
	diogenes->well_fed = false;
	++table->finished;
	if (table->finished >= table->settings->num_of_phil)
	{
		ft_party_is_over(table->phil, \
			table->settings->num_of_phil, table->forks);
		return (true);
	}
	return (false);
}

void	ft_heartbeat_monitor(t_table *table)
{
	t_phil			*diogenes;
	int				i;

	diogenes = table->phil;
	while (1)
	{
		i = -1;
		while (++i < table->settings->num_of_phil)
		{
			if (diogenes[i].well_fed == true)
			{
				if (ft_norm_is_a_pain(table, &diogenes[i]))
					return ;
			}
			if (check_if_dead(&diogenes[i]))
			{
				ft_death_record(table, i);
				return ;
			}
		}
		usleep(50);
	}
}
