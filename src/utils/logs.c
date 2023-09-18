/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilcent <tmilcent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 12:39:21 by tmilcent          #+#    #+#             */
/*   Updated: 2023/09/17 17:10:00 by tmilcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	log_death(long long curr_time, t_philo *philo)
{
	pthread_mutex_lock(&philo->settings->log_lock);
	if (philo->settings->stop == 1)
	{
		pthread_mutex_unlock(&philo->settings->log_lock);
		return ;
	}
	printf("%lld %d died\n", curr_time - philo->settings->start_time,
		philo->id);
	philo->settings->stop = 1;
	pthread_mutex_unlock(&philo->settings->log_lock);
	drop_forks(philo);
}

void	log_take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->settings->log_lock);
	if (philo->settings->stop == 1)
	{
		pthread_mutex_unlock(&philo->settings->log_lock);
		return ;
	}
	printf("%lld %d has taken a fork\n",
		get_time() - philo->settings->start_time, philo->id);
	pthread_mutex_unlock(&philo->settings->log_lock);
}

void	log_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->settings->log_lock);
	if (philo->settings->stop == 1)
	{
		pthread_mutex_unlock(&philo->settings->log_lock);
		return ;
	}
	printf("%lld %d is eating\n",
		get_time() - philo->settings->start_time, philo->id);
	pthread_mutex_unlock(&philo->settings->log_lock);
}

void	log_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->settings->log_lock);
	if (philo->settings->stop == 1)
	{
		pthread_mutex_unlock(&philo->settings->log_lock);
		return ;
	}
	printf("%lld %d is sleeping\n",
		get_time() - philo->settings->start_time, philo->id);
	pthread_mutex_unlock(&philo->settings->log_lock);
}

void	log_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->settings->log_lock);
	if (philo->settings->stop == 1)
	{
		pthread_mutex_unlock(&philo->settings->log_lock);
		return ;
	}
	printf("%lld %d is thinking\n",
		get_time() - philo->settings->start_time, philo->id);
	pthread_mutex_unlock(&philo->settings->log_lock);
}
