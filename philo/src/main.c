/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:50:04 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/18 16:00:05 by gzovkic          ###   ########.fr       */
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
		if (dinner->times_must_eat != TIME_MUST_EAT_NOT_SET
			&& philo_node->meals_eaten >= dinner->times_must_eat)
			break ;
	}
	return (NULL);
}

void	pick_forks(t_philo_node *philo_node)
{
	t_dinner	*dinner;

	dinner = philo_node->dinner;
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
	print_action(dinner, philo_node->philo_id, "is eating");
	philo_node->meals_eaten++;
	philo_node->time_since_last_meal = curr_time();
	usleep(dinner->time_to_eat * 1000);
}

void	philo_sleep(t_philo_node *philo_node)
{
	t_dinner	*dinner;

	dinner = philo_node->dinner;
	print_action(dinner, philo_node->philo_id, "is sleeping");
	usleep(dinner->time_to_sleep * 1000);
}

void	philo_think(t_philo_node *philo_node)
{
	t_dinner	*dinner;

	dinner = philo_node->dinner;
	print_action(dinner, philo_node->philo_id, "is thinking");
	usleep(100);
}

void	print_action(t_dinner *dinner, int philo_id, char *str)
{
	long	timestamp;

	timestamp = curr_time() - dinner->start_timer_of_sim;
	pthread_mutex_lock(&dinner->print_action_mutex);
	printf("%ld %d %s\n", timestamp, philo_id, str);
	pthread_mutex_unlock(&dinner->print_action_mutex);
}

void	routine_loop(t_philo_node *philo_node)
{
	philo_think(philo_node);
	pick_forks(philo_node);
	philo_eat(philo_node);
	pthread_mutex_unlock(&philo_node->fork);
	pthread_mutex_unlock(&philo_node->next->fork);
	philo_sleep(philo_node);
}
