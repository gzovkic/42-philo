/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_structs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:34:41 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/14 13:41:03 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_dinner(t_dinner *dinner, char *argv[])
{
	int	count;

	count = 0;
	dinner->number_of_philos = ft_atoi(argv[2]);
	dinner->time_to_die = ft_atoi(argv[3]);
	dinner->time_to_eat = ft_atoi(argv[4]);
	dinner->time_to_sleep = ft_atoi(argv[5]);
	dinner->times_must_eat = TIME_MUST_EAT_NOT_SET;
	if (argv[6] != NULL)
		dinner->times_must_eat = ft_atoi(argv[6]);
	dinner->philos = ft_calloc(dinner->number_of_philos, sizeof(t_philo));
	if (!dinner->philos)
	{
		(void)printf("Memory allocation failed\n");
		return ;
	}
	dinner->start_timer_of_sim = curr_time();
	dinner->sim_status = SIM_ACTIV;
	while (count < dinner->number_of_philos)
	{
		dinner->philos[count].meals_eaten = 0;
		dinner->philos[count].time_since_last_meal = dinner->start_timer_of_sim;
		count++;
	}
}

void	create_mutexes(t_dinner *dinner)
{
	int	count;

	dinner->forks = ft_calloc(dinner->number_of_philos,
			sizeof(pthread_mutex_init));
	if (!dinner->forks)
		ft_putstr_fd("Memory alloction failed\n", 2);
	count = 0;
	while (count < dinner->number_of_philos)
	{
		pthread_mutex_init(&dinner->forks[count], NULL);
		count++;
	}
}

void	create_threads(t_dinner *dinner, pthread_t *philos)
{
	int	id;

	philos = ft_calloc(sizeof(pthread_t), dinner->number_of_philos);
	if (!philos)
	{
		ft_putstr_fd("Memory alloction failed for philos\n", 2);
		return ;
	}
	id = 0;
	while (id < dinner->number_of_philos)
	{
		dinner->philos[id].philo_id = id + 1;
		dinner->philos->dinner = dinner;
		dinner->philos->time_since_last_meal = dinner->start_timer_of_sim;
		if (pthread_create(&philos[id], NULL, routine,
				&dinner->philos[id]) != 0)
		{
			ft_putstr_fd("Thread creation failed", 2);
			return ;
		}
		id++;
	}
}
