/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rysato <rysato@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:39:19 by rysato            #+#    #+#             */
/*   Updated: 2025/10/02 20:34:35 by rysato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int validate_input(int argc, char **argv)
{
	if(!(argc == 5 || argc == 6))
	{
		write(2, "Argument Invalid\n", 18);
		write(2, "[./philo] [number_of_philos] [time_to_die] ", 44);
		write(2, "[time_to_eat] [time_to_sleep] ", 31);
		write(2, "[number_of_times_each_philo_must_eat]\n", 39);
		return(-1);
	}
	if(ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0)
	{
		write(2, "Number Invalid\n", 16);
		return(-1);
	}
	if(argc == 6)
	{
		if(ft_atoi(argv[5]) < 0)
		{
			write(2, "Number Invalid\n", 16);
			return(-1);
		}
	}
	return(1);
}

static void initialize_conf(int argc, char **argv, t_obs *obs)
{
	obs->conf.nop = ft_atoi(argv[1]);
	obs->conf.t_die = ft_atoi(argv[2]);
	obs->conf.t_eat = ft_atoi(argv[3]);
	obs->conf.t_sleep = ft_atoi(argv[4]);
	obs->conf.must_eat = -1;
	if(argc == 6)
		obs->conf.must_eat = ft_atoi(argv[5]);
	return ;
}

static int alloc_array(t_obs *obs)
{
	obs->forks = malloc(sizeof(pthread_mutex_t) * obs->conf.nop);
	if(obs->forks == NULL)
		return(-1);
	obs->meal_mx = malloc(sizeof(pthread_mutex_t) * obs->conf.nop);
	if(obs->meal_mx == NULL)
		return(free(obs->forks), -1);
}

int init_philos(int argc, char **argv, t_obs *obs)
{
	if(validate_input(argc, argv) == -1)
		return(-1);
	initialize_conf(argc, argv, obs);


}
