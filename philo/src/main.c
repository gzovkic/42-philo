/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:50:04 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/22 16:32:38 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	main(int argc, char **argv)
{
	t_philo_list	*philo_list;
	t_dinner		*dinner;

	dinner = ft_calloc(sizeof(t_dinner), 1);
	if (check_arguments(argc, argv))
		return (1);
	create_dinner(dinner, argv);
	philo_list = init_philo_list();
	fill_philo_list(philo_list, dinner);
	pthread_creation(philo_list);
	ft_monitor()
	pthread_wait(philo_list);
	return (0);
}

