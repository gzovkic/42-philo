/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:50:04 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/15 13:29:24 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	(void)philo;
	return (NULL);
}

int	main(int argc, char **argv)
{
	int			id;
	t_dinner	*dinner;

	id = 0;
	dinner = ft_calloc(sizeof(t_dinner), 1);
	if (check_arguments(argc, argv))
		return (1);
	create_dinner(dinner, argv);
	dinner->philos = init_philo_struct(dinner);
	create_mutexes(dinner);
	if (pthread_create(&dinner->philos[id].thread, NULL, &routine,
			&dinner->philos[id]) != 0)
	{
		ft_putstr_fd("Thread creation failed", 2);
		return (1);
	}
	id = 0;
	while (id < dinner->number_of_philos)
	{
		pthread_join(dinner->philos[id].thread, NULL);
		id++;
	}
	return (0);
}
