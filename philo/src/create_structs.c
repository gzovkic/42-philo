/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_structs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:34:41 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/15 13:30:00 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_dinner(t_dinner *dinner, char *argv[])
{
	dinner->number_of_philos = ft_atoi(argv[2]);
	dinner->time_to_die = ft_atoi(argv[3]);
	dinner->time_to_eat = ft_atoi(argv[4]);
	dinner->time_to_sleep = ft_atoi(argv[5]);
	dinner->times_must_eat = TIME_MUST_EAT_NOT_SET;
	if (argv[6] != NULL)
		dinner->times_must_eat = ft_atoi(argv[6]);
	dinner->start_timer_of_sim = curr_time();
	dinner->sim_status = SIM_ACTIV;
}

void	create_mutexes(t_dinner *dinner)
{
	int	count;

	dinner->forks = ft_calloc(dinner->number_of_philos,
			sizeof(pthread_mutex_t));
	if (!dinner->forks)
		ft_putstr_fd("Memory alloction failed\n", 2);
	count = 0;
	while (count < dinner->number_of_philos)
	{
		pthread_mutex_init(&dinner->forks[count], NULL);
		count++;
	}
}

t_philo	*init_philo_struct(t_dinner *dinner)
{
	t_philo	*philos;
	int		id;

	philos = ft_calloc(sizeof(t_philo), dinner->number_of_philos);
	if (!philos)
	{
		ft_putstr_fd("Memory alloction failed for philos\n", 2);
		return (NULL);
	}
	id = 0;
	while (id < dinner->number_of_philos)
	{
		philos[id].philo_id = id + 1;
		philos->dinner = dinner;
		philos->time_since_last_meal = dinner->start_timer_of_sim;
		philos->meals_eaten = 0;
		philos->thread = id++;
	}
	return (philos);
}
