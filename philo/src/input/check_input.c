/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilcent <tmilcent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:51:33 by tmilcent          #+#    #+#             */
/*   Updated: 2023/09/16 17:21:28 by tmilcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

static int	is_int(char *str)
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
		if (str[i] < '0' || str[i] > '9')
			return (1);
		res = res * 10 + (str[i] - '0');
		if (res > INT_MAX || res < INT_MIN)
			return (1);
		if (i == 1 && neg == -1)
			res *= -1;
	}
	return (0);
}

int	check_input(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (1);
	i = 0;
	while (++i < ac)
		if (is_int(av[i]))
			return (1);
	return (0);
}
