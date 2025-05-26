/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:35:38 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/26 21:27:16 by gzovkic          ###   ########.fr       */
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

void	pthread_creation(t_philo_list *philo_list)
{
	int				count;
	t_philo_node	*philo_node;
	int				num_philos;

	if (!philo_list || !philo_list->head || !philo_list->head->dinner)
		return ;
	count = 0;
	philo_node = philo_list->head;
	num_philos = philo_node->dinner->number_of_philos;
	while (count < num_philos && philo_node)
	{
		if (pthread_create(&philo_node->thread, NULL, &routine,
				philo_node) != 0)
		{
			ft_putstr_fd("Error creating thread\n", 2);
			return ;
		}
		// usleep(5);
		philo_node = philo_node->next;
		count++;
	}
}

void	pthread_wait(t_philo_list *philo_list)
{
	int				count;
	t_philo_node	*philo_node;
	int				num_philos;

	if (!philo_list || !philo_list->head || !philo_list->head->dinner)
		return ;
	count = 0;
	philo_node = philo_list->head;
	num_philos = philo_node->dinner->number_of_philos;
	while (count < num_philos && philo_node)
	{
		if (pthread_join(philo_node->thread, NULL) != 0)
		{
			ft_putstr_fd("Error joining thread\n", 2);
			return ;
		}
		philo_node = philo_node->next;
		count++;
	}
}
