/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilcent <tmilcent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:59:05 by tmilcent          #+#    #+#             */
/*   Updated: 2023/09/18 02:11:52 by tmilcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	take_forks(t_philo *philo)
{
	set_lf_lock(philo, 1);
	pthread_mutex_lock(philo->left_fork);
	log_take_fork(philo);
	set_rf_lock(philo, 1);
	pthread_mutex_lock(philo->right_fork);
	log_take_fork(philo);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_eat_lock);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->last_eat_lock);
	log_eat(philo);
	ft_usleep(philo->settings->time_to_eat);
	pthread_mutex_lock(&philo->eat_count_lock);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_count_lock);
}

void	drop_forks(t_philo *philo)
{
	if (get_lf_lock(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		set_lf_lock(philo, 0);
	}
	if (get_rf_lock(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		set_rf_lock(philo, 0);
	}
}

void	sleeping(t_philo *philo)
{
	log_sleep(philo);
	ft_usleep(philo->settings->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	log_think(philo);
}
