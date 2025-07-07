/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:17:37 by ybahri            #+#    #+#             */
/*   Updated: 2025/07/07 20:40:34 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_digit(char c)
{
	return(c >= '0' && c <= '9');
}

static bool	is_space(char c)
{
	return((c >= 9 && c <= 13) || c == 32);
}

static const char	*valid_input(const char *str)
{
	int	len;
	const char *number;

	len = 0;
	while(is_space(*str))
		str++;
	if(*str == '+')
		str++;
	else if(*str == '-')
		error_exit("Only positive values.");
	if(!is_digit(*str))
		error_exit("The input is not a digit.");
	number = str;
	while(is_digit(*str++))
		len++;
	if(len > 10)
		error_exit("The value is too big, INT_MAX is the limit.");
	return(number);
}

static long	ft_atol(const char *str)
{
	long	num;
	num = 0;

	str = valid_input(str);
	while(is_digit(*str))
		num = (num * 10) + (*str++ - '0');
	if(num > INT_MAX)
		error_exit("The value is too big, INT_MAX is the limit.");
	return(num);
}

void	parse_input(t_table *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1000;
	table->time_to_eat = ft_atol(av[3]) * 1000;
	table->time_to_sleep = ft_atol(av[4]) * 1000;
	if(table->time_to_die < 60000
		|| table->time_to_eat < 60000
		|| table->time_to_sleep < 60000)
		error_exit("Use timestamps major than 60ms");
	if(av[5])
		table->meal_limit = atol(av[5]);
	else
		table->meal_limit = -1;
}
