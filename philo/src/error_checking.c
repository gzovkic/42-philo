/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:01:06 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/13 08:37:41 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_nbr_numeric(char *argv[])
{
	int	index;
	int	count;

	index = 1;
	while (argv[index] != NULL)
	{
		count = 0;
		while (argv[index][count] != '\0')
		{
			if (check_statments(argv, index, count))
				return (true);
			count++;
		}
		index++;
	}
	return (false);
}

bool	check_nbr_arg(int argc)
{
	if (argc < 5 || argc > 6)
	{
		(void)printf("Wrong number of arguments\n");
		return (true);
	}
	return (false);
}

bool	check_minus(char *argv[])
{
	int	index;

	index = 1;
	while (argv[index] != NULL)
	{
		if (ft_atol(argv[index]) < 0)
		{
			(void)printf("Only positive numbers\n");
			return (true);
		}
		index++;
	}
	return (false);
}

bool	check_max_int(char *argv[])
{
	int	index;

	index = 1;
	while (argv[index] != NULL)
	{
		if (ft_strlen(argv[index]) > 11)
		{
			(void)printf("Number is over max int range\n");
			return (true);
		}
		index++;
	}
	index = 1;
	while (argv[index] != NULL)
	{
		if (ft_atol(argv[index]) > INT_MAX)
		{
			(void)printf("Number is over max int range\n");
			return (true);
		}
		index++;
	}
	return (false);
}
