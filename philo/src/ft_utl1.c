/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utl1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brattles <brattles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 01:01:22 by brattles          #+#    #+#             */
/*   Updated: 2021/10/27 01:32:24 by brattles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (c);
	return (0);
}

static int	ft_isspc(const char c)
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
	while (ft_isspc(*nptr) != 0 || *nptr == '0' || *nptr == '+' || *nptr == '-')
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
	long			starttime;

	gettimeofday(&tv, NULL);
	starttime = (tv.tv_sec * 1000) + tv.tv_usec / 1000;
	return (starttime);
}
