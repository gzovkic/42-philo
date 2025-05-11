/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:01:06 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/11 12:08:48 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_nbr_arg(int argc)
{
	if(argc < 5 || argc > 6)
		(void)printf("Wrong number of arguments");
}

void	check_arguments(int argc, char *argv[])
{
	(void)argv;
	check_nbr_arg(argc);
}