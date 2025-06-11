/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:17:53 by ybahri            #+#    #+#             */
/*   Updated: 2025/06/03 15:17:54 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_philo_status status, t_philo *philo)
{
	long	elapsed = get_time(MILLISECOND) - philo->table->start_simulation;

	if(philo->full)
		return;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& !simulation_end(philo->table))
		printf("%6ld %d has taken a fork\n", elapsed, philo->id);
	else if(EATING == status && !simulation_end(philo->table))
		printf("%6ld %d is eating\n", elapsed, philo->id);
	else if(SLEEPING == status && !simulation_end(philo->table))
		printf("%6ld %d is sleeping\n", elapsed, philo->id);
	else if(THINKING == status && !simulation_end(philo->table))
		printf("%6ld %d is thinking\n", elapsed, philo->id);
	else if(DIED == status)
		printf("%6ld %d died\n", elapsed, philo->id);
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}


