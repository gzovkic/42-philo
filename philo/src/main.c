/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:50:04 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/14 13:41:43 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_dinner	*dinner;
	pthread_t	*philos;

	philos = NULL;
	dinner = NULL;
	if (check_arguments(argc, argv))
		return (1);
	create_dinner(dinner, argv);
	create_mutexes(dinner);
	create_threads(dinner, philos);
	return (0);
}
