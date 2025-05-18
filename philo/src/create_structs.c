/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_structs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:34:41 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/18 12:46:33 by gzovkic          ###   ########.fr       */
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
	dinner->sim_status = SIM_ACTIV;
}

// void	create_mutexes(t_dinner *dinner)
// {
// 	int	count;

// 	dinner->forks = ft_calloc(dinner->number_of_philos,
// 			sizeof(pthread_mutex_t));
// 	if (!dinner->forks)
// 		ft_putstr_fd("Memory alloction failed\n", 2);
// 	count = 0;
// 	while (count < dinner->number_of_philos)
// 	{
// 		if(pthread_mutex_init(&dinner->forks[count], NULL) == -1)
// 		{
// 			ft_putstr_fd("Mutex creation failed for forks\n", 2);
// 			return ;
// 		}
// 		count++;
// 	}
// }