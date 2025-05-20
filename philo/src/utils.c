/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:35:38 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/20 17:33:29 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	curr_time(void)
{
	int				time;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		ft_putstr_fd("gettimeofday() failed\n", 2);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

bool	is_sim_active(t_dinner *dinner)
{
	bool	status;

	pthread_mutex_lock(&dinner->print_action_mutex);
	status = (dinner->sim_status == SIM_ACTIV);
	pthread_mutex_unlock(&dinner->print_action_mutex);
	return (status);
}

void	pthread_creation(t_philo_list *philo_list)
{
	int				count;
	t_philo_node	*current_node;
	int				num_philos;

	if (!philo_list || !philo_list->head || !philo_list->head->dinner)
		return ;
	count = 0;
	current_node = philo_list->head;
	num_philos = current_node->dinner->number_of_philos;
	while (count < num_philos && current_node)
	{
		if (pthread_create(&current_node->thread, NULL, &routine,
				current_node) != 0)
		{
			ft_putstr_fd("Error creating thread\n", 2);
			return ;
		}
		current_node = current_node->next;
		count++;
	}
}

void	pthread_wait(t_philo_list *philo_list)
{
	int				count;
	t_philo_node	*current_node;
	int				num_philos;

	if (!philo_list || !philo_list->head || !philo_list->head->dinner)
		return ;
	count = 0;
	current_node = philo_list->head;
	num_philos = current_node->dinner->number_of_philos;
	while (count < num_philos && current_node)
	{
		if (pthread_join(current_node->thread, NULL) != 0)
		{
			ft_putstr_fd("Error joining thread\n", 2);
			return ;
		}
		current_node = current_node->next;
		count++;
	}
}
