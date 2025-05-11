/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:01:06 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/11 12:34:34 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_nbr_numeric(char *argv[])
{
	int	index;
	int count;

	index = 1;
	while(argv[index] != NULL)
	{
		count = 0;
		while(argv[index][count] != '\0')
		{
			if(argv[index][count] < '0' || argv[index][count] > '9')
			{
				(void)printf("Non numeric argument\n");
				return ;
			}
			count++;
		}
		index++;
	}
}

void	check_nbr_arg(int argc)
{
	if(argc < 5 || argc > 6)
		(void)printf("Wrong number of arguments\n");
}

void	check_arguments(int argc, char *argv[])
{
	(void)argv;
	check_nbr_arg(argc);
	check_nbr_numeric(argv);
}
