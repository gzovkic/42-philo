/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:50:22 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/13 08:37:48 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

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
long	ft_atol(char *str);
