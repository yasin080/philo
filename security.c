/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   security.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:17:46 by ybahri            #+#    #+#             */
/*   Updated: 2025/06/03 15:17:47 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;//porque el malloc es un return de un puntero generico?

	ret = malloc(bytes);
	if(NULL == ret)
		error_exit("Error with malloc");
	return(ret);
}

static	void handle_mutex_error(int status, t_opcode opcode)
{
	if(status == 0)
		return;
	if(EINVAL == status && (LOCK == opcode || UNLOCK == opcode))
		error_exit("The value specified by mutex is invalid.");
	else if(EINVAL == status && INIT == opcode)
		error_exit("The value specified by attr is invalid.");
	else if(EBUSY == status)
		error_exit("Mutex is locked.");
	else if(EDEADLK == status)
		error_exit("A deadlock would occur if the thread blocked waiting for mutex.");
	else if(EPERM == status)
		error_exit("The current threads does not hold a lock on mutex");
	else if(ENOMEM == status)
		error_exit("The process cannot allocate enough memory to create another mutex.");
	else if(EINVAL == status && DESTROY == opcode)
		error_exit("The value specified by mutex is invalid or mutex is locked by another thread.");
}

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if(LOCK == opcode)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if(UNLOCK == opcode)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if(INIT == opcode)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if(DESTROY == opcode)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Wrong opcode for mutex handle");
}

//***Threads***

static void	handle_thread_error(int status, t_opcode opcode)
{
	if(0 == status)
		return;
	if(EAGAIN == status)
		error_exit("No resources to create another thread.");
	else if(EPERM == status)
		error_exit("The caller does not have appropiate permission.");
	else if(EINVAL == status && CREATE == opcode)
		error_exit("The value specified by attr is invalid.");
	else if(EINVAL == status && (JOIN == opcode || DETACH == opcode))
		error_exit("The value specified by thread is not joinable.");
	else if(ESRCH == status)
		error_exit("No thread could be found corresponding to that "
			"specified by the given thread ID, thread.");
	else if(EDEADLK == status)
		error_exit("A deadlock was detected or the value of "
			"thread specifies the calling threads.");
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
		void *data, t_opcode opcode)
{
	if(CREATE == opcode)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if(JOIN == opcode)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if(DETACH == opcode)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("Wrong opcode for thread_handle: "
			  "use <CREATE> <JOIN> <DETACH>");
}
