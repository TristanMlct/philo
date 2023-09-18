/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilcent <tmilcent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:17:39 by tmilcent          #+#    #+#             */
/*   Updated: 2023/09/17 17:26:03 by tmilcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

static void	*end_check(void *arg)
{
	t_philo		*philo;
	long long	curr_time;
	int			i;

	philo = (t_philo *)arg;
	while (!philo->settings->stop)
	{
		i = -1;
		while (++i < philo->settings->nb_philo)
		{
			curr_time = get_time();
			if (curr_time - philo[i].last_eat > philo->settings->time_to_die)
			{
				log_death(curr_time, &philo[i]);
				return (NULL);
			}
			if (philo->settings->nb_eat != -1 && philo[i].full == 0
				&& philo[i].eat_count >= philo->settings->nb_eat)
			{
				philo->settings->nb_full++;
				philo[i].full = 1;
			}
		}
		if (philo->settings->nb_full == philo->settings->nb_philo)
			philo->settings->stop = 1;
	}
	return (NULL);
}

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->settings->stop == 0)
	{
		take_forks(philo);
		if (philo->settings->stop == 1)
			break ;
		eat(philo);
		if (philo->settings->stop == 1)
			break ;
		drop_forks(philo);
		if (philo->settings->stop == 1)
			break ;
		sleeping(philo);
		if (philo->settings->stop == 1)
			break ;
		thinking(philo);
	}
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
		i++;
	}
	ft_usleep(100);
	i = 0;
	while (++i < settings->nb_philo)
	{
		settings->philo[i].last_eat = settings->start_time;
		if (pthread_create(&settings->tid[i], NULL,
				&philo_routine, &settings->philo[i]))
			return (1);
		i++;
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
