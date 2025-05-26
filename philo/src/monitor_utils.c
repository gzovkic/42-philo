/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:53:09 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/26 19:13:11 by gzovkic          ###   ########.fr       */
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
void	ft_usleep(long ms, t_philo_node *philo_node)
{
	long	start;
	long	elapsed;

	start = curr_time();
	while (1)
	{
		if (!is_sim_active_node(philo_node))
			return ;
		elapsed = curr_time() - start;
		if (elapsed >= ms / 1000)
			break ;
		usleep(100);
	}
}
void	cleanup(t_philo_list *philo_list)
{
	t_philo_node *current;
	t_philo_node *next;
	
	if (!philo_list || !philo_list->head || !philo_list->head->dinner)
		return ;
	if (philo_list->head->dinner)
	{
		pthread_mutex_destroy(&philo_list->head->dinner->print_action_mutex);
		free(philo_list->head->dinner);
	}
	if (philo_list)
	{
		current = philo_list->head;
		while (current && philo_list->size > 0)
		{
			next = current->next;
			pthread_mutex_destroy(&current->fork);
			pthread_mutex_destroy(&current->sim_status_mutex);
			free(current);
			current = next;
			philo_list->size--;
		}
		free(philo_list);
	}
}
