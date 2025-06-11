/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:17:22 by ybahri            #+#    #+#             */
/*   Updated: 2025/06/03 15:17:23 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//todo
void	thinking(t_philo *philo, bool pre_simulation)
{
	long	t_eat = philo->table->time_to_eat;
	long	t_sleep = philo->table->time_to_sleep;
	long	t_think = t_eat * 2 - t_sleep;

	if(!pre_simulation)
		write_status(THINKING, philo);
	//if is even dont care
	if(philo->table->philo_nbr % 2 == 0)
		return ;
	//odd not always fair
	if(t_think < 0)
		t_think = 0;
	//at least think half time
	precise_usleep(t_think * 0.42, philo-> table);
}

void	*unique_philo(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	//spinlock
	wait_all_threads(philo->table);
	//set last meal time
	set_long(philo->philo_mutex, &philo->last_meal_time,
		get_time(MICROSECOND));
	//syncro with monitor
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	write_status(TAKE_FIRST_FORK, philo);
	while(!simulation_end(philo->table))
		usleep(200);
	return(NULL);
}

static void	eat(t_philo *philo)
{
	//take first fork
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo);
	//take second fork
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo);
	//set last meal time
	set_long(philo->philo_mutex, &philo->last_meal_time,
		get_time(MICROSECOND));
	philo->meals_counter++;
	write_status(EATING, philo);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if(philo->table->meal_limit > 0
		&& philo->meals_counter == philo->table->meal_limit)
		set_bool(philo->philo_mutex, &philo->full, true);
	//release forks
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

void	*dinner_simulation(void *data)
{
	t_philo *philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(philo->philo_mutex, &philo->last_meal_time,
		get_time(MICROSECOND));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	de_synchro_philos(philo);

	while(!simulation_end(philo->table))
	{
		if(philo->full)
			break;
		eat(philo);
		write_status(SLEEPING, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, false);
	}
	return(NULL);
}

void	dinner_start(t_table *table)
{
	int i = -1;

	if(0 == table->meal_limit)
		return ;
	else if(1 == table->philo_nbr)
		safe_thread_handle(&table->philos[0].thread_id,
			unique_philo, &table->philos[0], CREATE);
	else
	{
		while(++i < table->philo_nbr)
			safe_thread_handle(&table->philos[i].thread_id,
				dinner_simulation, &table->philos[i], CREATE);
	}
	safe_thread_handle(&table->monitor, monitor_dinner, table, CREATE);
	table->start_simulation = get_time(MILLISECOND);
	set_bool(&table->table_mutex, &table->all_threads_created, true);

	i = -1;
	while(++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->simulation_end, true);
	safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}
