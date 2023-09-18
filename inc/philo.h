/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilcent <tmilcent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:48:07 by tmilcent          #+#    #+#             */
/*   Updated: 2023/09/17 17:30:12 by tmilcent         ###   ########.fr       */
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
	int				full;
	long long		last_eat;

	pthread_mutex_t	*left_fork;
	int				is_lf_locked;
	pthread_mutex_t	*right_fork;
	int				is_rf_locked;

	pthread_mutex_t	lock;
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
void		log_death(long long curr_time, t_philo *philo);
void		log_take_fork(t_philo *philo);
void		log_eat(t_philo *philo);
void		log_sleep(t_philo *philo);
void		log_think(t_philo *philo);

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