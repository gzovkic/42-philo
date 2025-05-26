/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checking_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 08:35:14 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/26 19:45:16 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_meal_must_eat(char *argv[])
{
	if (!argv[5])
		return (false);
	if (ft_atoi(argv[5]) <= 0)
	{
		(void)printf("INVALID: meal must eat must be bigger than 0\n");
		return (true);
	}
	return (false);
}

bool	check_arguments(int argc, char *argv[])
{
	if (check_nbr_arg(argc))
		return (true);
	if (check_nbr_numeric(argv))
		return (true);
	if (check_max_int(argv))
		return (true);
	if (check_minus(argv))
		return (true);
	if (check_meal_must_eat(argv))
		return (true);
	return (false);
}

bool	check_statments(char *argv[], int index, int count)
{
	if (argv[index][count] == '+' || argv[index][count] == '-')
		count++;
	if (argv[index][count] == '\0')
	{
		(void)printf("INVALID: Non numeric argument\n");
		return (true);
	}
	if (argv[index][count] < '0' || argv[index][count] > '9')
	{
		(void)printf("INVALID: Non numeric argument\n");
		return (true);
	}
	return (false);
}
