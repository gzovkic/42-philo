/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:50:22 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/12 16:28:02 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
# include <limits.h>
#include <stdbool.h>

// src/error_checking.c
bool	check_arguments(int argc, char *arvg[]);
bool	check_nbr_numeric(char *argv[]);
bool	check_nbr_arg(int argc);
bool	check_minus(char *argv[]);
bool	check_max_int(char *argv[]);
bool	check_arguments(int argc, char *argv[]);

// src/fake_libft.c
size_t	ft_strlen(const char *str);
long	ft_atol(char *str);
