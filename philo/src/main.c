/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:50:04 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/13 09:10:02 by gzovkic          ###   ########.fr       */
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
	dinner->philos = ft_calloc(dinner->number_of_philos, sizeof(t_philo));
	if (!dinner->philos)
	{
		(void)printf("Memory allocation failed\n");
		return ;
	}
}

int	main(int argc, char **argv)
{
	t_dinner	*dinner;

	if (check_arguments(argc, argv))
		return (1);
	create_dinner(dinner, argv);
	return (0);
}
