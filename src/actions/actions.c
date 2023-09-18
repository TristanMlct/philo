/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilcent <tmilcent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:59:05 by tmilcent          #+#    #+#             */
/*   Updated: 2023/09/17 17:32:51 by tmilcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	take_forks(t_philo *philo)
{
	philo->is_lf_locked = 1;
	pthread_mutex_lock(philo->left_fork);
	log_take_fork(philo);
	philo->is_rf_locked = 1;
	pthread_mutex_lock(philo->right_fork);
	log_take_fork(philo);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	philo->last_eat = get_time();
	philo->eat_count++;
	log_eat(philo);
	pthread_mutex_unlock(&philo->lock);
	ft_usleep(philo->settings->time_to_eat);
}

void	drop_forks(t_philo *philo)
{
	if (philo->is_lf_locked)
	{
		pthread_mutex_unlock(philo->left_fork);
		philo->is_lf_locked = 0;
	}
	if (philo->is_rf_locked)
	{
		pthread_mutex_unlock(philo->right_fork);
		philo->is_rf_locked = 0;
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
