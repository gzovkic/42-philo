/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzovkic <gzovkic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:57:53 by gzovkic           #+#    #+#             */
/*   Updated: 2025/05/13 13:10:04 by gzovkic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (str == NULL)
		return ((size_t) NULL);
	while (str[len] != '\0')
		len++;
	return (len);
}

long	ft_atol(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (result > (LONG_MAX - (*str - '0')) / 10)
		{
			if (sign == 1)
				return (LONG_MAX);
			else
				return (LONG_MIN);
		}
		result = result * 10 + *str++ - '0';
	}
	return (sign * result);
}

int	ft_atoi(const char *str)
{
	int	min_count;
	int	i;
	int	nb;

	i = 0;
	min_count = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			min_count++;
		i++;
	}
	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (min_count % 2 != 0)
		nb = -nb;
	return (nb);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL || fd <= 0)
		return ;
	while (s[i] != '\0')
	{
		write (fd, &s[i], 1);
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*arr;
	size_t			store;
	size_t			i;

	store = count * size;
	arr = malloc(store);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < store)
	{
		((unsigned char *)arr)[i] = 0;
		i++;
	}
	return (arr);
}
