/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:02:04 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/20 11:45:38 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_forks(t_philo_node *philo_node)
{
	t_dinner	*dinner;

	dinner = philo_node->dinner;
	if (!is_sim_active(dinner))
		return ;
	if (philo_node->philo_id % 2 == 1)
	{
		pthread_mutex_lock(&philo_node->fork);
		print_action(dinner, philo_node->philo_id, "has taken a fork");
		pthread_mutex_lock(&philo_node->next->fork);
		print_action(dinner, philo_node->philo_id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo_node->next->fork);
		print_action(dinner, philo_node->philo_id, "has taken a fork");
		pthread_mutex_lock(&philo_node->fork);
		print_action(dinner, philo_node->philo_id, "has taken a fork");
	}
}

void	philo_eat(t_philo_node *philo_node)
{
	t_dinner	*dinner;

	dinner = philo_node->dinner;
	if (!is_sim_active(dinner))
		return ;
	print_action(dinner, philo_node->philo_id, "is eating");
	philo_node->meals_eaten++;
	philo_node->time_since_last_meal = curr_time();
	usleep(dinner->time_to_eat * 1000);
}

void	philo_sleep(t_philo_node *philo_node)
{
	t_dinner	*dinner;

	dinner = philo_node->dinner;
	if (!is_sim_active(dinner))
		return ;
	print_action(dinner, philo_node->philo_id, "is sleeping");
	usleep(dinner->time_to_sleep * 1000);
}

void	philo_think(t_philo_node *philo_node)
{
	t_dinner	*dinner;

	dinner = philo_node->dinner;
	if (!is_sim_active(dinner))
		return ;
	print_action(dinner, philo_node->philo_id, "is thinking");
	usleep(200 * 1000);
}

void	print_action(t_dinner *dinner, int philo_id, char *str)
{
	long	timestamp;

	if (!is_sim_active(dinner))
		return ;
	timestamp = curr_time() - dinner->start_timer_of_sim;
	pthread_mutex_lock(&dinner->print_action_mutex);
	printf("%ld %d %s\n", timestamp, philo_id, str);
	pthread_mutex_unlock(&dinner->print_action_mutex);
}
