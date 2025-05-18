/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:57:47 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/18 14:58:06 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo_list(t_philo_list *philo_list)
{
	t_philo_node	*current;
	int				i;

	current = philo_list->head;
	i = 1;
	printf("Philo list (size: %zd):\n", philo_list->size);
	if (!current)
	{
		printf("  (empty)\n");
		return ;
	}
	do
	{
		printf("Philo #%d:\n", i);
		printf("  philo_id: %d\n", current->philo_id);
		printf("  meals_eaten: %d\n", current->meals_eaten);
		printf("  time_since_last_meal: %d\n", current->time_since_last_meal);
		printf("  thread: %p\n", (void *)current->thread);
		printf("  fork (mutex address): %p\n", (void *)&current->fork);
		printf("  next: %p\n", (void *)current->next);
		printf("  Dinner struct:\n");
		printf("    number_of_philos: %d\n", current->dinner->number_of_philos);
		printf("    time_to_die: %ld\n", current->dinner->time_to_die);
		printf("    time_to_eat: %ld\n", current->dinner->time_to_eat);
		printf("    time_to_sleep: %ld\n", current->dinner->time_to_sleep);
		printf("    times_must_eat: %ld\n", current->dinner->times_must_eat);
		printf("    start_timer_of_sim: %d\n",
			current->dinner->start_timer_of_sim);
		printf("    sim_status: %d\n", current->dinner->sim_status);
		i++;
		current = current->next;
	} while (current && current != philo_list->head);
}
