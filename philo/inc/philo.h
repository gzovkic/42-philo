/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:50:22 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/26 20:07:36 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

struct	s_philo_node;

typedef struct s_dinner
{
	pthread_mutex_t		print_action_mutex;
	int					number_of_philos;
	time_t				time_to_die;
	time_t				time_to_sleep;
	time_t				time_to_eat;
	int					times_must_eat;
	time_t				start_timer_of_sim;
}						t_dinner;
typedef struct s_philo_node
{
	t_dinner			*dinner;
	int					philo_id;
	int					time_since_last_meal;
	int					times_must_eat;
	int					meals_eaten;
	int					sim_status;
	pthread_t			thread;
	pthread_mutex_t		fork;
	pthread_mutex_t		sim_status_mutex;
	struct s_philo_node	*next;
}						t_philo_node;
typedef struct s_philo_list
{
	t_philo_node		*head;
	t_philo_node		*tail;
	ssize_t				size;
}						t_philo_list;

typedef enum PHILO_ENUMS
{
	TIME_MUST_EAT_NOT_SET = -1,
	SIM_ACTIV,
	SIM_INACTIV
}						t_PHILO;

// src/error_checking.c
bool					check_nbr_numeric(char *argv[]);
bool					check_nbr_arg(int argc);
bool					check_minus(char *argv[]);
bool					check_max_int(char *argv[]);

// stc/error_checking_utils.c
bool					check_meal_must_eat(char *argv[]);
bool					check_arguments(int argc, char *arvg[]);
bool					check_statments(char *argv[], int index, int count);

// src/fake_libft.c
size_t					ft_strlen(const char *str);
long					ft_atol(const char *str);
int						ft_atoi(const char *str);
void					ft_putstr_fd(char *s, int fd);
void					*ft_calloc(size_t count, size_t size);

// src/create_structs.c
void					create_dinner(t_dinner *dinner, char *argv[]);
void					add_philo_node(t_philo_list *philo_list,
							t_dinner *dinner, int count);
void					fill_philo_list(t_philo_list *philo_list,
							t_dinner *dinner);
t_philo_list			*init_philo_list(void);
void					add_to_list(t_philo_list *philo_list,
							t_philo_node *new_node);

// src/utils.c
long					curr_time(void);
void					pthread_creation(t_philo_list *philo_list);
void					pthread_wait(t_philo_list *philo_list);

// src/philo_action.c
bool					pick_forks(t_philo_node *philo_node);
void					philo_eat(t_philo_node *philo_node);
void					philo_sleep(t_philo_node *philo_node);
void					philo_think(t_philo_node *philo_node);
void					print_action(t_dinner *dinner, int philo_id, char *str);

// src/monitor_utils.c
bool					is_sim_active_node(t_philo_node *philo_node);
bool					is_sim_active_list(t_philo_list *philo_list);
void					tell_philos(t_philo_list *philo_list);
void					ft_usleep(long ms, t_philo_node *philo_node);
void					cleanup(t_philo_list *philo_list);

// src/routines.c
void					ft_monitor(t_philo_list *philo_list);
bool					monitor_loop(t_philo_list *philo_list);
void					*routine(void *arg);
void					routine_loop(t_philo_node *philo_node);
void					one_philo_case(t_philo_node *philo_node);

// src/more_utils.c
bool					check_full_philos(t_philo_list *philo_list,
							t_philo_node *philo_node);
bool					check_philo_status(t_philo_list *philo_list);
bool					pick_odd(t_philo_node *philo_node);
bool					pick_even(t_philo_node *philo_node);