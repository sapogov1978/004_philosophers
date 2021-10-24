/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brattles <brattles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 00:35:28 by brattles          #+#    #+#             */
/*   Updated: 2021/10/23 01:07:27 by brattles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

# define	BRED	"41m"
# define	FBLACK	"\033[30;"
# define	NONE	"\033[0m"
# define	BEEP	"\a"

typedef struct	s_table		t_table;
typedef struct	s_settings	t_settings;
typedef struct	s_phil		t_phil;

struct s_table {
	struct s_settings	*settings;
	struct s_phil		*phil;
	pthread_mutex_t		*forks;
};

struct s_settings	{
	unsigned int	num_of_phil;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	n_times_to_eat;
	long			start_time;
};

struct	s_phil {
	pthread_t			*phil;
	unsigned int		phil_id;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	long unsigned int	eat_last_time;
	unsigned int		eat_complete_counter;
	bool				dead_or_alive;
	bool				well_fed;
	t_settings			*settings;
};

int		main(int argc, char **argv);
int 	ft_parse_and_init(t_table *table, int argc, char **argv);
int		ft_panic(char *msg, t_table **table);
long	ft_chronometer(void);
void	*lifecycle(void *phil);
void	ft_heartbeat_monitor(t_table *table);
int		ft_party_is_over(t_phil *phil, int num, pthread_mutex_t *forks);
int		ft_atoi(const char *nptr);

#endif