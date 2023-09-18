/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilcent <tmilcent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 22:41:34 by tmilcent          #+#    #+#             */
/*   Updated: 2023/09/18 00:40:21 by tmilcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

int	get_stop_lock(t_settings *settings)
{
	int	stop;

	pthread_mutex_lock(&settings->stop_lock);
	stop = settings->stop;
	pthread_mutex_unlock(&settings->stop_lock);
	return (stop);
}

void	set_stop_lock(t_settings *settings, int stop)
{
	pthread_mutex_lock(&settings->stop_lock);
	settings->stop = stop;
	pthread_mutex_unlock(&settings->stop_lock);
}

int	get_eat_count_lock(t_philo *philo)
{
	int	eat_count;

	pthread_mutex_lock(&philo->eat_count_lock);
	eat_count = philo->eat_count;
	pthread_mutex_unlock(&philo->eat_count_lock);
	return (eat_count);
}

long long	get_last_eat_lock(t_philo *philo)
{
	long long	last_eat;

	pthread_mutex_lock(&philo->last_eat_lock);
	last_eat = philo->last_eat;
	pthread_mutex_unlock(&philo->last_eat_lock);
	return (last_eat);
}

void	destroy_mutex(t_settings *settings)
{
	int	i;

	pthread_mutex_destroy(&settings->stop_lock);
	pthread_mutex_destroy(&settings->log_lock);
	i = -1;
	while (++i < settings->nb_philo)
	{
		pthread_mutex_destroy(&settings->forks[i]);
		pthread_mutex_destroy(&settings->philo[i].eat_count_lock);
		pthread_mutex_destroy(&settings->philo[i].last_eat_lock);
		pthread_mutex_destroy(&settings->philo[i].lf_lock);
		pthread_mutex_destroy(&settings->philo[i].rf_lock);
	}
}
