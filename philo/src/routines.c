/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:01:28 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/26 23:04:38 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	monitor_loop(t_philo_list *philo_list)
{
	t_philo_node	*philo_node;
	long			curr_t;
	long			calc_t;

	philo_node = philo_list->head;
	while (philo_node)
	{
		curr_t = curr_time();
		pthread_mutex_lock(&philo_node->dinner->print_action_mutex);
		calc_t = curr_t - philo_node->time_since_last_meal;
		if (calc_t > philo_node->dinner->time_to_die)
		{
			printf("%ld %d died\n", curr_t
				- philo_node->dinner->start_timer_of_sim, philo_node->philo_id);
			tell_philos(philo_list);
			pthread_mutex_unlock(&philo_node->dinner->print_action_mutex);
			return (true);
		}
		if (check_full_philos(philo_list, philo_node))
			return (true);
		pthread_mutex_unlock(&philo_node->dinner->print_action_mutex);
		philo_node = philo_node->next;
	}
	return (false);
}

void	ft_monitor(t_philo_list *philo_list)
{
	if (!philo_list)
		return ;
	while (1)
	{
		if (monitor_loop(philo_list))
			return ;
		ft_usleep(100, philo_list->head);
	}
}

void	*routine(void *arg)
{
	t_philo_node	*philo_node;

	philo_node = (t_philo_node *)arg;
	if (philo_node->dinner->number_of_philos == 1)
	{
		one_philo_case(philo_node);
		return (NULL);
	}
	while (is_sim_active_node(philo_node))
	{
		routine_loop(philo_node);
		if (philo_node->times_must_eat != TIME_MUST_EAT_NOT_SET
			&& philo_node->meals_eaten >= philo_node->times_must_eat)
			break ;
	}
	return (NULL);
}

void	routine_loop(t_philo_node *philo_node)
{
	if (!is_sim_active_node(philo_node))
		return ;
	if (philo_node->philo_id % 2 == 1)
		philo_think(philo_node);
	if (pick_forks(philo_node))
	{
		if (!is_sim_active_node(philo_node))
		{
			pthread_mutex_unlock(&philo_node->fork);
			pthread_mutex_unlock(&philo_node->next->fork);
			return ;
		}
		philo_eat(philo_node);
		pthread_mutex_unlock(&philo_node->fork);
		pthread_mutex_unlock(&philo_node->next->fork);
		if (!is_sim_active_node(philo_node))
			return ;
		philo_sleep(philo_node);
	}
	if (philo_node->philo_id % 2 == 0)
		philo_think(philo_node);
}

void	one_philo_case(t_philo_node *philo_node)
{
	long		start_time;
	t_dinner	*dinner;

	dinner = philo_node->dinner;
	philo_think(philo_node);
	print_action(dinner, philo_node->philo_id, "has taken a fork");
	start_time = dinner->start_timer_of_sim;
	pthread_mutex_lock(&dinner->print_action_mutex);
	philo_node->time_since_last_meal = start_time;
	pthread_mutex_unlock(&dinner->print_action_mutex);
	ft_usleep(dinner->time_to_die, philo_node);
}
