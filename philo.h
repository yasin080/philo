/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:17:42 by ybahri            #+#    #+#             */
/*   Updated: 2025/07/24 20:39:49 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <errno.h>

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}			t_philo_status;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}			t_opcode;

typedef enum e_time_code
{
	MILLISECOND,
	MICROSECOND,
}			t_time_code;

typedef	pthread_mutex_t	t_mtx;
typedef struct s_table t_table;

typedef struct	s_fork
{
	t_mtx	fork;
	int		fork_id;
}				t_fork;

typedef struct	s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_mtx		*philo_mutex;
	t_table		*table;
}				t_philo;


typedef struct s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		meal_limit;
	long		start_simulation;
	bool		simulation_end;
	bool		all_threads_created;
	long		threads_running_nbr;
	pthread_t	monitor;
	t_mtx		table_mutex;
	t_mtx		write_mutex;
	t_fork		*forks;
	t_philo		*philos;

}				t_table;


//utils
void	error_exit(const char *error);
long	get_time(t_time_code time_code);
void	precise_usleep(long	usec, t_table *table);
void	clean(t_table *table);

//parsing
void	parse_input(t_table *table, char **av);

//security
void	*safe_malloc(size_t bytes);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
			void *data, t_opcode opcode);

//init
void	data_init(t_table *table);

//getters_setters
void	set_bool(t_mtx *mtx, bool *dest, bool value);
void	set_long(t_mtx *mtx, long *dest, long value);
bool	get_bool(t_mtx *mtx, bool *value);
long	get_long(t_mtx *mtx, long *value);
bool	simulation_end(t_table *table);

//sync_utils
void	wait_all_threads(t_table *table);
bool	all_threads_running(t_mtx *mtx, long *threads,
		long philo_nbr);
void	increase_long(t_mtx *mtx, long *value);
void	de_synchro_philos(t_philo *philo);

//write_status
void	write_status(t_philo_status status, t_philo *philo);

//dinner
void	*dinner_simulation(void *data);
void	dinner_start(t_table *table);
void	thinking(t_philo *philo, bool pre_simulation);

//monitor
void	*monitor_dinner(void *data);
