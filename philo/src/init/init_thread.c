/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilcent <tmilcent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:17:39 by tmilcent          #+#    #+#             */
/*   Updated: 2023/09/18 02:48:38 by tmilcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

static void	*end_check(void *arg)
{
	t_philo		*philo;
	long long	curr_time;
	int			i;

	philo = (t_philo *)arg;
	while (!get_stop_lock(philo->settings))
	{
		i = -1;
		while (++i < philo->settings->nb_philo)
		{
			curr_time = get_time();
			if (curr_time - get_last_eat_lock(&philo[i]) \
				> philo->settings->time_to_die)
				return (log_death(curr_time, &philo[i]));
			if (philo->settings->nb_eat != -1 && philo[i].full == 0
				&& get_eat_count_lock(&philo[i]) \
				>= philo->settings->nb_eat)
				philo->settings->nb_full += ++philo[i].full;
		}
		if (philo->settings->nb_full == philo->settings->nb_philo)
			set_stop_lock(philo->settings, 1);
	}
	return (NULL);
}

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(20);
	while (get_stop_lock(philo->settings) == 0)
	{
		take_forks(philo);
		if (get_stop_lock(philo->settings) == 1)
			break ;
		eat(philo);
		if (get_stop_lock(philo->settings) == 1)
			break ;
		drop_forks(philo);
		if (get_stop_lock(philo->settings) == 1)
			break ;
		sleeping(philo);
		if (get_stop_lock(philo->settings) == 1)
			break ;
		thinking(philo);
	}
	drop_forks(philo);
	return (NULL);
}

int	init_thread(t_settings *settings)
{
	int			i;
	pthread_t	thread;

	settings->start_time = get_time();
	i = -1;
	while (++i < settings->nb_philo)
	{
		settings->philo[i].last_eat = settings->start_time;
		if (pthread_create(&settings->tid[i], NULL,
				&philo_routine, &settings->philo[i]))
			return (1);
	}
	if (pthread_create(&thread, NULL, &end_check, settings->philo))
		return (1);
	i = -1;
	while (++i < settings->nb_philo)
		if (pthread_join(settings->tid[i], NULL))
			return (1);
	if (pthread_join(thread, NULL))
		return (1);
	return (0);
}
