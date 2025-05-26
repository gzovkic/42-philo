/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:50:04 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/26 19:17:48 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	main(int argc, char **argv)
{
	t_philo_list	*philo_list;
	t_dinner		*dinner;

	dinner = ft_calloc(sizeof(t_dinner), 1);
	if(!dinner)
	{
		(void)printf("Memory allocation failed");
		return(1);
	}	
	if (check_arguments(argc, argv))
	{
		free(dinner);
		return (1);
	}
	create_dinner(dinner, argv);
	philo_list = init_philo_list();
	fill_philo_list(philo_list, dinner);
	pthread_creation(philo_list);
	ft_monitor(philo_list);
	pthread_wait(philo_list);
	cleanup(philo_list);
	return (0);
}
