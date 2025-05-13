/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:50:22 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/13 09:42:11 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_dinner
{
	t_philo			*philos;
	int				number_of_philos;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				times_must_eat;
	int				start_timer_of_sim;
	int				sim_status;
}	t_dinner;

typedef struct s_philo
{
	t_dinner		*dinner;
	int				philo_id;
	int				time_since_last_meal;
	int				meals_eaten;
}	t_philo;

typedef enum PHILO
{
	TIME_MUST_EAT_NOT_SET = -1,
	SIM_ACTIV = 0,
	SIM_INACTIV
}	t_PHILO;

// src/error_checking.c
bool	check_nbr_numeric(char *argv[]);
bool	check_nbr_arg(int argc);
bool	check_minus(char *argv[]);
bool	check_max_int(char *argv[]);

// stc/error_checking_utils.c
bool	check_arguments(int argc, char *arvg[]);
bool	check_statments(char *argv[], int index, int count);

// src/fake_libft.c
size_t	ft_strlen(const char *str);
long	ft_atol(const char *str);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);