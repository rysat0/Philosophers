/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rysato <rysato@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:09:12 by rysato            #+#    #+#             */
/*   Updated: 2025/11/26 00:09:39 by rysato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_input(int argc, char **argv)
{
	if (!(argc == 5 || argc == 6))
	{
		write(2, "Argument Invalid\n", 18);
		write(2, "[./philo] [number_of_philos] [time_to_die] ", 44);
		write(2, "[time_to_eat] [time_to_sleep] ", 31);
		write(2, "[number_of_times_each_philo_must_eat]\n", 39);
		return (-1);
	}
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0
		|| ft_atoi(argv[4]) <= 0)
	{
		write(2, "Number Invalid\n", 16);
		return (-1);
	}
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) <= 0)
		{
			write(2, "Number Invalid\n", 16);
			return (-1);
		}
	}
	return (1);
}

void	initialize_conf(int argc, char **argv, t_obs *obs)
{
	obs->conf.nop = ft_atoi(argv[1]);
	obs->conf.t_die = ft_atoi(argv[2]);
	obs->conf.t_eat = ft_atoi(argv[3]);
	obs->conf.t_sleep = ft_atoi(argv[4]);
	obs->conf.must_eat = -1;
	if (argc == 6)
		obs->conf.must_eat = ft_atoi(argv[5]);
	return ;
}
