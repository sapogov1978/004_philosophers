/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brattles <brattles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 00:34:11 by brattles          #+#    #+#             */
/*   Updated: 2021/11/07 12:20:26 by brattles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (ft_panic("Memory allocation error", &table));
	memset(table, 0, sizeof(t_table));
	if (argc < 5 || argc > 6)
		return (ft_panic("Incorrect number of parameters", &table));
	if (ft_parse_and_init(table, argc, argv) == 0)
	{
		table = NULL;
		return (EXIT_SUCCESS);
	}
	free (table);
	table = NULL;
	return (EXIT_FAILURE);
}
