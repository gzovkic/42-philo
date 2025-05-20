/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:50:04 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/20 12:27:48 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	main(int argc, char **argv)
{
	pthread_t		monitor_thread;
	t_philo_list	*philo_list;
	t_dinner		*dinner;

	dinner = ft_calloc(sizeof(t_dinner), 1);
	if (check_arguments(argc, argv))
		return (1);
	create_dinner(dinner, argv);
	philo_list = init_philo_list();
	fill_philo_list(philo_list, dinner);
	pthread_creation(philo_list);
	pthread_create(&monitor_thread, NULL, monitor, philo_list);
	pthread_wait(philo_list);
	pthread_join(monitor_thread, NULL);
	return (0);
}

bool	check_full_philos(t_philo_list *philo_list, t_dinner *dinner)
{
	int				count;
	int				full_philos;
	t_philo_node	*current;

	count = 0;
	full_philos = 0;
	current = philo_list->head;
	while (count < dinner->number_of_philos)
	{
		if (dinner->times_must_eat != TIME_MUST_EAT_NOT_SET
			&& current->meals_eaten >= dinner->times_must_eat)
			full_philos++;
		count++;
		current = current->next;
	}
	if (dinner->times_must_eat != TIME_MUST_EAT_NOT_SET
		&& full_philos == dinner->number_of_philos)
	{
		dinner->sim_status = SIM_INACTIV;
		return (false);
	}
	return (true);
}

void	*monitor(void *arg)
{
	t_philo_list	*philo_list;
	t_dinner		*dinner;

	philo_list = (t_philo_list *)arg;
	dinner = philo_list->head->dinner;
	while (is_sim_active(dinner))
	{
		if (!check_full_philos(philo_list, dinner))
		{
			dinner->sim_status = SIM_INACTIV;
			return (NULL);
		}
		if (!monitor_loop(philo_list, dinner))
			return (NULL);
		usleep(10);
	}
	return (NULL);
}

bool	monitor_loop(t_philo_list *philo_list, t_dinner *dinner)
{
	int				count;
	t_philo_node	*current;
	long			current_time;

	count = 0;
	current = philo_list->head;
	while (count < dinner->number_of_philos)
	{
		current_time = curr_time();
		if (current_time - current->time_since_last_meal > dinner->time_to_die)
		{
			pthread_mutex_lock(&dinner->print_action_mutex);
			(void)printf("%ld %d died\n", current_time
				- dinner->start_timer_of_sim, current->philo_id);
			pthread_mutex_unlock(&dinner->print_action_mutex);
			dinner->sim_status = SIM_INACTIV;
			return (false);
		}
		current = current->next;
		count++;
	}
	return (true);
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

void	routine_loop(t_philo_node *philo_node)
{
	if (!is_sim_active(philo_node->dinner))
		return ;
	philo_think(philo_node);
	if (philo_node->philo_id % 2 == 1)
		usleep(1000);
	pick_forks(philo_node);
	philo_eat(philo_node);
	pthread_mutex_unlock(&philo_node->fork);
	pthread_mutex_unlock(&philo_node->next->fork);
	if (!is_sim_active(philo_node->dinner))
		return ;
	philo_sleep(philo_node);
}
