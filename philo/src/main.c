/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:50:04 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/18 15:01:14 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	main(int argc, char **argv)
{
	t_philo_list *philo_list;
	t_dinner	*dinner;
	
	dinner = ft_calloc(sizeof(t_dinner), 1);
	if (check_arguments(argc, argv))
	return (1);
	create_dinner(dinner, argv);
	philo_list = init_philo_list();
	fill_philo_list(philo_list, dinner);
	// print_philo_list(philo_list);
	pthread_creation(philo_list);
	pthread_wait(philo_list);
	return (0);
}

void	*routine(void *arg)
{
	t_philo_node	*philo_node;
	t_dinner		*dinner;
	
	philo_node = (t_philo_node *)arg;
	dinner = philo_node->dinner;
	while (is_sim_active(dinner))
	{
		routine_loop(philo_node);
		if(dinner->times_must_eat != TIME_MUST_EAT_NOT_SET && philo_node->meals_eaten >= dinner->times_must_eat)
		break;
	}
	return (NULL);
}

void	routine_loop(t_philo_node *philo_node)
{
	philo_node->meals_eaten++;
	usleep(100);
}
