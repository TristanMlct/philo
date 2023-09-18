/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilcent <tmilcent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 22:44:45 by tmilcent          #+#    #+#             */
/*   Updated: 2023/09/17 17:05:17 by tmilcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

int	ft_atoi(const char *str)
{
	int			i;
	long long	res;
	int			neg;

	i = -1;
	res = 0;
	neg = 1;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			neg = -1;
		i++;
	}
	while (str[++i])
	{
		res = res * 10 + (str[i] - '0');
		if (i == 1 && neg == -1)
			res *= -1;
	}
	return ((int)res);
}

int	free_plus_plus(t_settings *settings)
{
	if (settings->tid)
		free(settings->tid);
	settings->tid = NULL;
	if (settings->philo)
		free(settings->philo);
	settings->philo = NULL;
	if (settings->forks)
		free(settings->forks);
	settings->forks = NULL;
	return (1);
}

long long	get_time(void)
{
	long long		ms;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}

void	ft_usleep(long long time)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(1000);
}
