/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:35:38 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/18 16:47:47 by gzovkic          ###   ########.fr       */
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
	return (dinner->sim_status == SIM_ACTIV);
}

void	pthread_creation(t_philo_list *philo_list)
{
	int count;
	t_philo_node *current_node;
	
	count = 0;
	current_node = philo_list->head;
	while (count < current_node->dinner->number_of_philos && current_node)
	{
		pthread_create(&current_node->thread, NULL, &routine,	current_node);
		current_node = current_node->next;
		count++;
		if(current_node == philo_list->head)
		break;
	}
}

void	pthread_wait(t_philo_list *philo_list)
{
	int count;
	t_philo_node *current_node;
	
	count = 0;
	current_node = philo_list->head;
	while (count < current_node->dinner->number_of_philos && current_node)
	{
		pthread_join(current_node->thread, NULL);
		current_node = current_node->next;
		count++;
	}
}
