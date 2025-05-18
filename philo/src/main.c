/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:50:04 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/18 12:27:58 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

// bool	is_sim_active(t_dinner *dinner)
// {
//     return (dinner->sim_status == SIM_ACTIV);
// }

// void	print_action(t_dinner *dinner, int philo_id, char *str)
// {
// 	long time_stamp;

// 	time_stamp = curr_time() - dinner->start_timer_of_sim;
//     pthread_mutex_lock(dinner->print_action_mutex);
//     printf("%ld %d %s\n", time_stamp, philo_id, str);
//     pthread_mutex_unlock(&dinner->print_action_mutex);
// }

// bool	thinking(t_dinner *dinner, t_philo *philo)
// {
// 	long time_stamp;

// 	time_stamp = curr_time() - dinner->start_timer_of_sim;
// 	printf("%ld Philo %d is thinking\n", time_stamp, philo->philo_id);
// 	usleep(100);
// 	return(false);
// }

// bool	sleeping(t_dinner *dinner, t_philo *philo)
// {
// 	long time_stamp;

// 	time_stamp = curr_time() - dinner->start_timer_of_sim;
// 	printf("%ld Philo %d is sleeping\n",time_stamp, philo->philo_id);
// 	usleep(100);
// 	return(false);
// }

// bool	eating(t_dinner *dinner, t_philo *philo)
// {
// 	long time_stamp;

// 	time_stamp = curr_time() - dinner->start_timer_of_sim;
// 	printf("%ld Philo %d is eating\n",time_stamp, philo->philo_id);
// 	usleep(100);
// 	philo->meals_eaten++;
// 	return(false);
// }

// void	start_of_routine(t_philo_list *philo_list)
// {
	// int			left_fork;
	// int			right_fork;
	// t_dinner	*dinner;

	// dinner = philo->dinner;
	// left_fork = philo->philo_id - 1;
	// right_fork = philo->philo_id % dinner->number_of_philos;
	// while (is_sim_active(philo->dinner) && philo->meals_eaten != dinner->times_must_eat)
	// {
	// 	if (philo->philo_id % 2 == 1)
	// 	{
	// 		pthread_mutex_lock(&dinner->forks[left_fork]);
	// 		pthread_mutex_lock(&dinner->forks[right_fork]);
	// 	}
	// 	else
	// 	{
	// 		pthread_mutex_lock(&dinner->forks[right_fork]);
	// 		pthread_mutex_lock(&dinner->forks[left_fork]);
	// 	}
	// 	pthread_mutex_unlock(&dinner->forks[left_fork]);
	// 	pthread_mutex_unlock(&dinner->forks[right_fork]);
	// 	eating(dinner, philo);
	// 	pthread_mutex_unlock(&dinner->forks[left_fork]);
	// 	pthread_mutex_unlock(&dinner->forks[right_fork]);
	// 	sleeping(dinner, philo);
	// 	thinking(dinner, philo);
	// }
// }

t_philo_list *init_philo_list(void)
{
	t_philo_list *new_list;

	new_list = ft_calloc(sizeof(t_philo_list), 1);
	if(!new_list)
		return(NULL);
	new_list->head = NULL;
	new_list->tail = NULL;
	new_list->size = 0;
	return(new_list);
}

void	*routine(void *arg)
{
	t_philo_list	*philo_list;

	philo_list = (t_philo_list *)arg;
	// start_of_routine(philo_list);
	(void)philo_list;
	return (NULL);
}

void	add_philo_node(t_philo_list *philo_list, int count)
{
	t_philo_node	*new_node;

	new_node = ft_calloc(sizeof(t_philo_node), 1);
	if (!new_node)
		return ;
	new_node->time_since_last_meal = philo_list->dinner->start_timer_of_sim;
	new_node->meals_eaten = 0;
	new_node->philo_id = count;
	pthread_mutex_init(&new_node->fork, NULL);
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

void	fill_philo_list(t_philo_list *philo_list)
{
	int count;

	count = 0;
	while(count < philo_list->dinner->number_of_philos)
	{
		add_philo_node(philo_list, count + 1);
		count++;
	}
}

void	print_philo_list(t_philo_list *philo_list)
{
    t_philo_node *current = philo_list->head;
    int i = 1;

    printf("Philo list (size: %zd):\n", philo_list->size);
    while (current)
    {
        printf("Philo #%d:\n", i);
        printf("  philo_id: %d\n", current->philo_id);
        printf("  meals_eaten: %d\n", current->meals_eaten);
        printf("  time_since_last_meal: %d\n", current->time_since_last_meal);
        printf("  Dinner struct:\n");
        printf("    number_of_philos: %d\n", philo_list->dinner->number_of_philos);
        printf("    time_to_die: %ld\n", philo_list->dinner->time_to_die);
        printf("    time_to_eat: %ld\n", philo_list->dinner->time_to_eat);
        printf("    time_to_sleep: %ld\n", philo_list->dinner->time_to_sleep);
        printf("    times_must_eat: %ld\n", philo_list->dinner->times_must_eat);
        printf("    start_timer_of_sim: %d\n", philo_list->dinner->start_timer_of_sim);
        printf("    sim_status: %d\n", philo_list->dinner->sim_status);
        current = current->next;
        i++;
        if (current == philo_list->head)
            break;
    }
}

int	main(int argc, char **argv)
{
	t_philo_list *philo_list;
	t_dinner	*dinner;

	dinner = ft_calloc(sizeof(t_dinner), 1);
	if (check_arguments(argc, argv))
		return (1);
	create_dinner(dinner, argv);
	philo_list = init_philo_list();
	philo_list->dinner = dinner;
	fill_philo_list(philo_list);
	print_philo_list(philo_list);
	// while (id < dinner->number_of_philos)
	// {
	// 	pthread_create(&dinner->philos[id].thread, NULL, &routine, &dinner->philos[id]);
	// 	id++;
	// }
	// id = 0;
	// while (id < dinner->number_of_philos)
	// {
	// 	pthread_join(dinner->philos[id].thread, NULL);
	// 	id++;
	// }
	return (0);
}
