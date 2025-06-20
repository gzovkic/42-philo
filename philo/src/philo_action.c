/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:02:04 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/27 01:05:15 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	pick_forks(t_philo_node *philo_node)
{
	if (!is_sim_active_node(philo_node))
		return (false);
	if (philo_node->philo_id % 2 == 1)
	{
		if (!pick_odd(philo_node))
			return (false);
	}
	else
	{
		if (!pick_even(philo_node))
			return (false);
	}
	return (true);
}

void	philo_eat(t_philo_node *philo_node)
{
	t_dinner	*dinner;
	long		current;

	if (!is_sim_active_node(philo_node))
		return ;
	dinner = philo_node->dinner;
	pthread_mutex_lock(&dinner->print_action_mutex);
	current = curr_time();
	printf("%ld %d %s\n", current - dinner->start_timer_of_sim,
		philo_node->philo_id, "is eating");
	philo_node->time_since_last_meal = current;
	philo_node->meals_eaten++;
	pthread_mutex_unlock(&dinner->print_action_mutex);
	ft_usleep(dinner->time_to_eat * 1000, philo_node);
}

void	philo_sleep(t_philo_node *philo_node)
{
	t_dinner	*dinner;

	if (!is_sim_active_node(philo_node))
		return ;
	dinner = philo_node->dinner;
	print_action(dinner, philo_node->philo_id, "is sleeping");
	ft_usleep(dinner->time_to_sleep * 1000, philo_node);
}

void	philo_think(t_philo_node *philo_node)
{
	t_dinner	*dinner;
	long		think_time;

	if (!is_sim_active_node(philo_node))
		return ;
	dinner = philo_node->dinner;
	print_action(dinner, philo_node->philo_id, "is thinking");
	think_time = (dinner->time_to_die - (dinner->time_to_eat
				+ dinner->time_to_sleep)) / 4;
	if (think_time > 100)
		think_time = 100;
	else if (think_time < 0)
		think_time = 0;
	if (think_time > 0)
		ft_usleep(think_time * 1000, philo_node);
}

void	print_action(t_dinner *dinner, int philo_id, char *str)
{
	long	timestamp;

	pthread_mutex_lock(&dinner->print_action_mutex);
	timestamp = curr_time() - dinner->start_timer_of_sim;
	printf("%ld %d %s\n", timestamp, philo_id, str);
	pthread_mutex_unlock(&dinner->print_action_mutex);
}
