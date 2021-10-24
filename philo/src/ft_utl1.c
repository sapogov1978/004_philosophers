/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utl1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brattles <brattles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 01:01:22 by brattles          #+#    #+#             */
/*   Updated: 2021/10/24 17:53:22 by brattles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (c);
	return (0);
}

static int	ft_isspace(const char c)
{
	if (c == '\t' || c == ' ' || c == '\n' || c == '\v' || c == '\f' || \
		c == '\r')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	long	int_value;
	int		isnegative;

	int_value = 0;
	isnegative = 1;
	while (ft_isspace(*nptr) != 0 || *nptr == '0' || *nptr == '+' || *nptr == '-')
	{
		if ((*nptr == '+' || *nptr == '-') && ft_isdigit(*(nptr + 1)) == 0)
			return (0);
		if (*nptr == '-')
			isnegative = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr) != 0)
	{
		int_value = ((int_value * 10) + (*nptr - '0'));
		nptr++;
	}
	if (isnegative == -1)
		int_value = int_value * -1;
	if (int_value > INT_MAX || int_value < INT_MIN)
		return (0);
	return ((int)int_value);
}

long	ft_chronometer(void)
{
	struct timeval	tv;
	long 			starttime;

	gettimeofday(&tv, NULL);
	starttime = (tv.tv_sec * 1000) + tv.tv_usec / 1000;
	return (starttime);
}

static void	ft_death_record(t_table *table, int i)
{
	t_phil	*diogenes;

	diogenes = table->phil;
	printf("%s%s%s%ld %d died%s\n", BEEP, FBLACK, BRED, ft_chronometer() - table->settings->start_time, diogenes[i].phil_id, NONE);
	ft_party_is_over(table->phil, table->settings->num_of_phil, table->forks);
}

void	ft_heartbeat_monitor(t_table *table)
{
	t_phil			*diogenes;
	unsigned int	i;

	diogenes = table->phil;
	while (1)
	{
		i = -1;
		while (++i < table->settings->num_of_phil)
		{
			if (diogenes[i].dead_or_alive)
//			if (ft_chronometer() - diogenes[i].eat_last_time > table->settings->time_to_die)
			{
				ft_death_record(table, i);
				return ;
			}
			if (diogenes[i].well_fed == true)
			{
				//diogenes[i].well_fed = false;
				//++table->phil->eat_complete_counter;
				//if (table->phil->eat_complete_counter >= table->settings->num_of_phil)
					ft_party_is_over(table->phil, (int)table->settings->num_of_phil, table->forks);
					return ;
			}
		}
		usleep(1);
	}
}
