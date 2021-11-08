/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brattles <brattles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 00:35:28 by brattles          #+#    #+#             */
/*   Updated: 2021/11/07 13:48:18 by brattles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <stdbool.h>
# include <string.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

# define NONE	"\033[0m"
# define BEEP	"\a"

//Foreground Colors
# define FBLACK		"\033[30;"
# define FRED		"\033[31;"
# define FGREEN		"\033[32;"
# define FYELLOW	"\033[33;"
# define FBLUE		"\033[34;"
# define FMAGENTA	"\033[35;"
# define FCYAN		"\033[36;"
# define FWHITE		"\033[37;"

//Background Colors
# define BBLACK		"40m"
# define BRED		"41m"
# define BGREEN		"42m"
# define BYELLOW	"43m"
# define BBLUE		"44m"
# define BMAGENTA	"45m"
# define BCYAN		"46m"
# define BWHITE		"47m"

typedef struct s_table		t_table;
typedef struct s_settings	t_settings;
typedef struct s_phil		t_phil;

struct s_table {
	pthread_mutex_t		*forks;
	struct s_settings	*settings;
	struct s_phil		*phil;
	int					finished;
};

struct s_settings	{
	uint64_t	start_time;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			n_times_to_eat;
	int			num_of_phil;
};

struct	s_phil {
	t_settings			*settings;
	pthread_t			*phil;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	uint64_t			eat_last_time;
	int					phil_numb;
	int					eat_complete_counter;
	bool				need_check;
	bool				well_fed;
};

int		main(int argc, char **argv);
int		ft_parse_and_init(t_table *table, int argc, char **argv);
int		ft_panic(char *msg, t_table **table);
long	ft_chronometer(void);
void	lifecycle(void *phil);
void	ft_heartbeat_monitor(t_table *table);
int		ft_party_is_over(t_phil *phil, int num, pthread_mutex_t *forks);
void	ft_free_run(t_table **table, t_settings **settings, \
			pthread_mutex_t **forks, t_phil **phils);
int		ft_atoi(const char *nptr);

#endif
