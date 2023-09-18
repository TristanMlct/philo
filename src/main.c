/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilcent <tmilcent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:28:09 by tmilcent          #+#    #+#             */
/*   Updated: 2023/09/17 16:27:19 by tmilcent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_settings	settings;

	if (check_input(ac, av))
		return (1);
	if (init_data(&settings, ac, av))
		return (1);
	if (init_thread(&settings))
		return (1);
	free_plus_plus(&settings);
	return (0);
}
