/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilcent <tmilcent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 00:25:36 by tmilcent          #+#    #+#             */
/*   Updated: 2023/09/18 00:30:41 by tmilcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

int	get_lf_lock(t_philo *philo)
{
	int	is_lf_locked;

	pthread_mutex_lock(&philo->lf_lock);
	is_lf_locked = philo->is_lf_locked;
	pthread_mutex_unlock(&philo->lf_lock);
	return (is_lf_locked);
}

int	get_rf_lock(t_philo *philo)
{
	int	is_rf_locked;

	pthread_mutex_lock(&philo->rf_lock);
	is_rf_locked = philo->is_rf_locked;
	pthread_mutex_unlock(&philo->rf_lock);
	return (is_rf_locked);
}

void	set_lf_lock(t_philo *philo, int value)
{
	pthread_mutex_lock(&philo->lf_lock);
	philo->is_lf_locked = value;
	pthread_mutex_unlock(&philo->lf_lock);
}

void	set_rf_lock(t_philo *philo, int value)
{
	pthread_mutex_lock(&philo->rf_lock);
	philo->is_rf_locked = value;
	pthread_mutex_unlock(&philo->rf_lock);
}
