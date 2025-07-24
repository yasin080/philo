/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:17:27 by ybahri            #+#    #+#             */
/*   Updated: 2025/07/24 20:25:53 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_mtx *mtx, bool *dest, bool value)
{
	safe_mutex_handle(mtx, LOCK);
	*dest = value;
	safe_mutex_handle(mtx, UNLOCK);
}

bool	get_bool(t_mtx *mtx, bool *value)
{
	bool	ret;

	safe_mutex_handle(mtx, LOCK);
	ret = *value;
	safe_mutex_handle(mtx, UNLOCK);
	return(ret);
}

long	get_long(t_mtx *mtx, long *value)
{
	long	ret;

	safe_mutex_handle(mtx, LOCK);
	ret = *value;
	safe_mutex_handle(mtx, UNLOCK);
	return(ret);
}

void	set_long(t_mtx *mtx, long *dest, long value)
{
	safe_mutex_handle(mtx, LOCK);
	*dest = value;
	safe_mutex_handle(mtx, UNLOCK);
} 

bool	simulation_end(t_table *table)
{
	return(get_bool(&table->table_mutex, &table->simulation_end));
}
