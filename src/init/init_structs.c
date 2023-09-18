/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilcent <tmilcent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 22:39:11 by tmilcent          #+#    #+#             */
/*   Updated: 2023/09/18 02:06:21 by tmilcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

static int	init_settings(t_settings *settings, int ac, char **av)
{
	settings->nb_philo = ft_atoi(av[1]);
	settings->time_to_die = ft_atoi(av[2]);
	settings->time_to_eat = ft_atoi(av[3]);
	settings->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		settings->nb_eat = ft_atoi(av[5]);
	else
		settings->nb_eat = -1;
	if (settings->nb_philo < 1 || settings->time_to_die < 0
		|| settings->time_to_eat < 0 || settings->time_to_sleep < 0
		|| settings->nb_eat < -1)
		return (1);
	settings->stop = 0;
	settings->nb_full = 0;
	settings->start_time = 0;
	settings->tid = NULL;
	settings->philo = NULL;
	settings->forks = NULL;
	pthread_mutex_init(&settings->log_lock, NULL);
	pthread_mutex_init(&settings->stop_lock, NULL);
	return (0);
}

static void	init_forks(t_settings *settings)
{
	int	i;

	i = -1;
	while (++i < settings->nb_philo)
		pthread_mutex_init(&settings->forks[i], NULL);
	i = -1;
	while (++i < settings->nb_philo)
	{
		settings->philo[i].left_fork = &settings->forks[i];
		settings->philo[i].right_fork = &settings->forks[(i + 1) \
										% settings->nb_philo];
		i++;
	}
	i = 0;
	while (++i < settings->nb_philo)
	{
		settings->philo[i].right_fork = &settings->forks[i];
		settings->philo[i].left_fork = &settings->forks[(i + 1) \
										% settings->nb_philo];
		i++;
	}
}

static void	init_philo(t_settings *settings)
{
	int	i;

	i = -1;
	while (++i < settings->nb_philo)
	{
		settings->philo[i].settings = settings;
		settings->philo[i].id = i + 1;
		settings->philo[i].eat_count = 0;
		settings->philo[i].last_eat = 0;
		settings->philo[i].full = 0;
		settings->philo[i].is_lf_locked = 0;
		settings->philo[i].is_rf_locked = 0;
		pthread_mutex_init(&settings->philo[i].eat_count_lock, NULL);
		pthread_mutex_init(&settings->philo[i].last_eat_lock, NULL);
		pthread_mutex_init(&settings->philo[i].lf_lock, NULL);
		pthread_mutex_init(&settings->philo[i].rf_lock, NULL);
	}
}

int	init_data(t_settings *settings, int ac, char **av)
{
	if (init_settings(settings, ac, av))
		return (1);
	settings->tid = malloc(sizeof(pthread_t) * settings->nb_philo);
	if (!settings->tid)
		return (free_plus_plus(settings));
	settings->philo = malloc(sizeof(t_philo) * settings->nb_philo);
	if (!settings->philo)
		return (free_plus_plus(settings));
	settings->forks = malloc(sizeof(pthread_mutex_t) * settings->nb_philo);
	if (!settings->forks)
		return (free_plus_plus(settings));
	init_forks(settings);
	init_philo(settings);
	return (0);
}
