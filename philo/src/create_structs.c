/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_structs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:34:41 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/26 20:07:04 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_dinner(t_dinner *dinner, char *argv[])
{
	dinner->number_of_philos = ft_atoi(argv[1]);
	dinner->time_to_die = ft_atoi(argv[2]);
	dinner->time_to_eat = ft_atoi(argv[3]);
	dinner->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		dinner->times_must_eat = ft_atoi(argv[5]);
	else
		dinner->times_must_eat = TIME_MUST_EAT_NOT_SET;
	dinner->start_timer_of_sim = curr_time();
	if (pthread_mutex_init(&dinner->print_action_mutex, NULL) != 0)
	{
		free(dinner);
		ft_putstr_fd("Error: mutex initialization failed\n", 2);
		return ;
	}
}

void	add_to_list(t_philo_list *philo_list, t_philo_node *new_node)
{
	if (!philo_list->head)
		philo_list->head = new_node;
	else
	{
		new_node->next = philo_list->head;
		philo_list->tail->next = new_node;
	}
	philo_list->tail = new_node;
	philo_list->size++;
}

void	add_philo_node(t_philo_list *philo_list, t_dinner *dinner, int count)
{
	t_philo_node	*new_node;

	new_node = ft_calloc(sizeof(t_philo_node), 1);
	if (!new_node)
		return ;
	new_node->time_since_last_meal = dinner->start_timer_of_sim;
	new_node->meals_eaten = 0;
	new_node->philo_id = count;
	new_node->dinner = dinner;
	new_node->times_must_eat = dinner->times_must_eat;
	if (pthread_mutex_init(&new_node->fork, NULL) != 0)
	{
		free(new_node);
		ft_putstr_fd("Error: fork mutex initialization failed\n", 2);
		return ;
	}
	if (pthread_mutex_init(&new_node->sim_status_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&new_node->fork);
		free(new_node);
		ft_putstr_fd("Error: status mutex initialization failed\n", 2);
		return ;
	}
	add_to_list(philo_list, new_node);
}

void	fill_philo_list(t_philo_list *philo_list, t_dinner *dinner)
{
	int	count;

	count = 0;
	if (!philo_list || !dinner)
		return ;
	while (count < dinner->number_of_philos)
	{
		add_philo_node(philo_list, dinner, count + 1);
		count++;
	}
}

t_philo_list	*init_philo_list(void)
{
	t_philo_list	*new_list;

	new_list = ft_calloc(sizeof(t_philo_list), 1);
	if (!new_list)
		return (NULL);
	new_list->head = NULL;
	new_list->tail = NULL;
	new_list->size = 0;
	return (new_list);
}
