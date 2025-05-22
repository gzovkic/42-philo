/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:53:09 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/22 16:24:23 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_sim_active_node(t_philo_node *philo_node)
{
	bool	status;

	pthread_mutex_lock(&philo_node->sim_status_mutex);
	status = (philo_node->sim_status == SIM_ACTIV);
	pthread_mutex_unlock(&philo_node->sim_status_mutex);
	return (status);
}

bool	is_sim_active_list(t_philo_list *philo_list)
{
	int				count;
	t_philo_node	*philo_node;

	count = 0;
	philo_node = philo_list->head;
	while (philo_node && count < philo_list->size)
	{
		pthread_mutex_lock(&philo_node->sim_status_mutex);
		if (philo_node->sim_status == SIM_INACTIV)
		{
			tell_philos(philo_list);
			return (true);
		}
		pthread_mutex_unlock(&philo_node->sim_status_mutex);
		count++;
	}
	return (false);
}

void	tell_philos(t_philo_list *philo_list)
{
	int				count;
	t_philo_node	*philo_node;

	count = 0;
	philo_node = philo_list->head;
	while (philo_node && count < philo_list->size)
	{
		pthread_mutex_lock(&philo_node->sim_status_mutex);
		philo_node->sim_status = SIM_INACTIV;
		pthread_mutex_unlock(&philo_node->sim_status_mutex);
		philo_node = philo_node->next;
		count++;
	}
}
void	ft_usleep(long ms)
{
	long	start;
	long	elapsed;

	start = curr_time();
	while (1)
	{
		elapsed = curr_time() - start;
		if (elapsed >= ms / 1000)
			break ;
		usleep(100);
	}
}
