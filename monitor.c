/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:42:30 by ybahri            #+#    #+#             */
/*   Updated: 2025/06/25 12:43:56 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool philo_died(t_philo *philo)
{
	long	time_since_last_meal;
	long	current_time;
	long	last_meal;

	if(philo->full)
		return false;
	current_time = get_time(MICROSECOND);
	last_meal = get_long(philo->philo_mutex, &philo->last_meal_time);
	time_since_last_meal = current_time - last_meal;
	return (time_since_last_meal >= philo->table->time_to_die);
}

void	*monitor_dinner(void *data)
{
	int i;
	t_table	*table;
	bool	simulation_ended;

	table = (t_table *)data;
	simulation_ended = false;
	while(!all_threads_running(&table->table_mutex,
			&table->threads_running_nbr, table->philo_nbr));
	while(!simulation_ended)
	{
		i = -1;
		while(++i < table->philo_nbr)
		{
			if(philo_died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->simulation_end, true);
				write_status(DIED, table->philos + i);
				simulation_ended = true;
				return NULL;
			}
		}
		if(!simulation_ended)
			precise_usleep(50, table);
	}
	return NULL;
}
