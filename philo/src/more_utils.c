/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:56:22 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/26 22:17:33 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_full_philos(t_philo_list *philo_list, t_philo_node *philo_node)
{
	if (philo_node->times_must_eat != TIME_MUST_EAT_NOT_SET
		&& philo_node->meals_eaten >= philo_node->times_must_eat
		&& check_philo_status(philo_list))
	{
		tell_philos(philo_list);
		pthread_mutex_unlock(&philo_node->dinner->print_action_mutex);
		return (true);
	}
	return (false);
}

bool	check_philo_status(t_philo_list *philo_list)
{
	int				full_philos;
	t_philo_node	*philo_node;

	full_philos = 0;
	philo_node = philo_list->head;
	while (philo_node)
	{
		if (philo_node->meals_eaten >= philo_node->times_must_eat)
			full_philos++;
		if (philo_node == philo_list->tail)
			break ;
		philo_node = philo_node->next;
	}
	if (full_philos == philo_node->dinner->number_of_philos)
		return (true);
	return (false);
}

bool	pick_odd(t_philo_node *philo_node)
{
	t_dinner	*dinner;

	dinner = philo_node->dinner;
	pthread_mutex_lock(&philo_node->fork);
	if (!is_sim_active_node(philo_node))
	{
		pthread_mutex_unlock(&philo_node->fork);
		return (false);
	}
	if (!is_sim_active_node(philo_node))
		return (false);
	print_action(dinner, philo_node->philo_id, "has taken a fork");
	pthread_mutex_lock(&philo_node->next->fork);
	if (!is_sim_active_node(philo_node))
	{
		pthread_mutex_unlock(&philo_node->fork);
		pthread_mutex_unlock(&philo_node->next->fork);
		return (false);
	}
	if (!is_sim_active_node(philo_node))
		return (false);
	print_action(dinner, philo_node->philo_id, "has taken a fork");
	return (true);
}

bool	pick_even(t_philo_node *philo_node)
{
	t_dinner	*dinner;

	dinner = philo_node->dinner;
	pthread_mutex_lock(&philo_node->next->fork);
	if (!is_sim_active_node(philo_node))
	{
		pthread_mutex_unlock(&philo_node->next->fork);
		return (false);
	}
	print_action(dinner, philo_node->philo_id, "has taken a fork");
	pthread_mutex_lock(&philo_node->fork);
	if (!is_sim_active_node(philo_node))
	{
		pthread_mutex_unlock(&philo_node->fork);
		pthread_mutex_unlock(&philo_node->next->fork);
		return (false);
	}
	print_action(dinner, philo_node->philo_id, "has taken a fork");
	return (true);
}
