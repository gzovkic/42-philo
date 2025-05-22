/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:01:28 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/22 16:33:05 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo_node	*philo_node;
	// t_dinner		*dinner;

	philo_node = (t_philo_node *)arg;
	// dinner = philo_node->dinner;
	if (philo_node->dinner->number_of_philos == 1)
	{
		one_philo_case(philo_node);
		return(NULL);
	}
	while (is_sim_active_node(philo_node))
	{
		routine_loop(philo_node);
		if(philo_node->meals_eaten >= philo_node->times_must_eat)
			break;
	}
	return (NULL);
}

void	routine_loop(t_philo_node *philo_node)
{
	if(philo_node->philo_id % 2 == 1)
		philo_think(philo_node);
	if (pick_forks(philo_node))
	{
		philo_eat(philo_node);
		pthread_mutex_unlock(&philo_node->fork);
		pthread_mutex_unlock(&philo_node->next->fork);
		philo_sleep(philo_node);
	}
	if(philo_node->philo_id % 2 == 0)
		philo_think(philo_node);
	if(philo_node->meals_eaten >= philo_node->times_must_eat)
		return ;
}

void one_philo_case(t_philo_node *philo_node)
{
	long	start_time;
	t_dinner	*dinner;
	
	dinner = philo_node->dinner;
	start_time = curr_time();
	philo_think(philo_node);
	pthread_mutex_lock(&philo_node->fork);
	print_action(dinner, philo_node->philo_id, "has taken a fork");
	philo_node->time_since_last_meal = start_time;
	// while (is_sim_active_node(philo_node))
	// 	ft_usleep(100);
	pthread_mutex_unlock(&philo_node->fork);
}
