/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:17:48 by ybahri            #+#    #+#             */
/*   Updated: 2025/06/21 00:44:14 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_table *table)
{
	while(!get_bool(&table->table_mutex, &table->all_threads_created))
		;
}

//Monitor waits until all threads are running
bool	all_threads_running(t_mtx *mtx, long *threads,
		long philo_nbr)
{
	bool	ret = false;
	safe_mutex_handle(mtx, LOCK);
	if(*threads == philo_nbr)
		ret = true;
	safe_mutex_handle(mtx, UNLOCK);
	return(ret);
}

//increase threads running to sync with the monitor
void	increase_long(t_mtx *mtx, long *value)
{
	safe_mutex_handle(mtx, LOCK);
	(*value)++;
	safe_mutex_handle(mtx, UNLOCK);
}

void	de_synchro_philos(t_philo *philo)
{
	if(philo->table->philo_nbr % 2 == 0)
	{
		if(philo->id % 2 == 0)
			precise_usleep(3e4, philo->table);
	}
	else
	{
		if(philo->id % 2)
			thinking(philo, true);
	}
}
