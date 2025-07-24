/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:17:50 by ybahri            #+#    #+#             */
/*   Updated: 2025/07/24 11:51:19 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(t_time_code time_code)
{
	struct timeval tv;

	if(gettimeofday(&tv, NULL))
		error_exit("Gettimeofday failed");
	if(SECOND == time_code)
		return(tv.tv_sec + (tv.tv_usec / 1e6));
	else if(MILLISECOND == time_code)
		return(tv.tv_sec * 1000 + tv.tv_usec / 1000);
	else if(MICROSECOND == time_code)
		return((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_exit("Wrong input to gettime!");
	return(42);
}

void	error_exit(const char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}
//spinlock 55
void	precise_usleep(long	usec, t_table *table)
{
	long	start = get_time(MICROSECOND);
	long	elapsed;
	long	remaining;

	while(get_time(MICROSECOND) - start < usec)
	{
		if(simulation_end(table))
			break;
		elapsed = get_time(MICROSECOND) - start;
		remaining = usec - elapsed;

		if(remaining > 1e3)
			usleep(remaining/2);
		else
		{
			while(get_time(MICROSECOND) - start < usec)
				;
		}
	}
}

void	clean(t_table *table)
{
	t_philo	*philo;
	int	i = -1;
	while(++i < table->philo_nbr)
	{
		philo = &table->philos[i];
		safe_mutex_handle(philo->philo_mutex, DESTROY);
	}
	safe_mutex_handle(&table->table_mutex, DESTROY);
	safe_mutex_handle(&table->write_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}
