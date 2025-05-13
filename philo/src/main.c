/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:50:04 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/13 09:00:30 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_dinner(t_dinner *dinner, char *argv[])
{
	dinner->time_to_die = ft_atoi(argv[3]);
	dinner->time_to_eat = ft_atoi(argv[4]);
	dinner->time_to_sleep = ft_atoi(argv[5]);
	if (argv[6] != NULL)
		dinner->times_must_eat = ft_atoi(argv[6]);
}

int	main(int argc, char **argv)
{
	t_dinner	*dinner;

	if (check_arguments(argc, argv))
		return (1);
	create_dinner(dinner, argv);
	return (0);
}
