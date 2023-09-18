/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilcent <tmilcent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:48:07 by tmilcent          #+#    #+#             */
/*   Updated: 2023/09/18 02:49:11 by tmilcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define INT_MAX 2147483647
# define INT_MIN -2147483648

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_settings	t_settings;

typedef struct s_philo
{
	t_settings		*settings;

	int				id;
	int				eat_count;
	pthread_mutex_t	eat_count_lock;
	int				full;
	long long		last_eat;
	pthread_mutex_t	last_eat_lock;

	pthread_mutex_t	*left_fork;
	int				is_lf_locked;
	pthread_mutex_t	lf_lock;
	pthread_mutex_t	*right_fork;
	int				is_rf_locked;
	pthread_mutex_t	rf_lock;
}					t_philo;

typedef struct s_settings
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;

	t_philo			*philo;
	pthread_mutex_t	*forks;

	long long		start_time;
	int				stop;
	pthread_mutex_t	stop_lock;
	int				nb_full;

	pthread_t		*tid;

	pthread_mutex_t	log_lock;
}					t_settings;

// utils/utils.c
int			ft_atoi(const char *str);
int			free_plus_plus(t_settings *settings);
long long	get_time(void);
void		ft_usleep(long long time);

// utils/logs.c
void		*log_death(long long curr_time, t_philo *philo);
void		log_take_fork(t_philo *philo);
void		log_eat(t_philo *philo);
void		log_sleep(t_philo *philo);
void		log_think(t_philo *philo);

// utils/mutex.c
int			get_stop_lock(t_settings *settings);
void		set_stop_lock(t_settings *settings, int stop);
int			get_eat_count_lock(t_philo *philo);
long long	get_last_eat_lock(t_philo *philo);
void		destroy_mutex(t_settings *settings);

// utils/mutex2.c
int			get_lf_lock(t_philo *philo);
int			get_rf_lock(t_philo *philo);
void		set_lf_lock(t_philo *philo, int value);
void		set_rf_lock(t_philo *philo, int value);

// init/init_structs.c
int			init_data(t_settings *settings, int ac, char **av);

// init/init_thread.c
int			init_thread(t_settings *settings);

// input/check_input.c
int			check_input(int ac, char **av);

// actions/actions.c
void		take_forks(t_philo *philo);
void		drop_forks(t_philo *philo);
void		eat(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);

#endif