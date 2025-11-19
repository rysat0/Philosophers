/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rysato <rysato@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:39:19 by rysato            #+#    #+#             */
/*   Updated: 2025/11/19 21:27:43 by rysato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	validate_input(int argc, char **argv)
{
	if (!(argc == 5 || argc == 6))
	{
		write(2, "Argument Invalid\n", 18);
		write(2, "[./philo] [number_of_philos] [time_to_die] ", 44);
		write(2, "[time_to_eat] [time_to_sleep] ", 31);
		write(2, "[number_of_times_each_philo_must_eat]\n", 39);
		return (-1);
	}
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0
		|| ft_atoi(argv[4]) < 0)
	{
		write(2, "Number Invalid\n", 16);
		return (-1);
	}
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) < 0)
		{
			write(2, "Number Invalid\n", 16);
			return (-1);
		}
	}
	return (1);
}

static void	initialize_conf(int argc, char **argv, t_obs *obs)
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

static void	destroy_mtx(t_obs *obs, pthread_mutex_t *mxs, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&mxs[j]);
		j++;
	}
}

static int	init_mtx(t_obs *obs)
{
	int	i;

	i = 0;
	while (i < obs->conf.nop)
	{
		if (pthread_mutex_init(&obs->forks[i], NULL) != 0)
			return (destroy_mtx(obs, obs->forks, i), free(obs->forks),
				free(obs->meal_mx), -1);
		i++;
	}
	i = 0;
	while (i < obs->conf.nop)
	{
		if (pthread_mutex_init(&obs->meal_mx[i], NULL) != 0)
			return (destroy_mtx(obs, obs->forks, obs->conf.nop),
				destroy_mtx(obs, obs->meal_mx, i), free(obs->forks),
				free(obs->meal_mx), -1);
		i++;
	}
	return (0);
}

static int	init_philo(t_obs *obs)
{
	int		i;
	t_philo	*ph;

	i = 0;
	if (init_mtx(obs) == -1)
		return (-1);
	while (i < obs->conf.nop)
	{
		ph = &obs->ph[i];
		ph->id = i;
		ph->leftid = i;
		ph->rightid = ((i + 1) % obs->conf.nop);
		ph->lastmeal_ms = 0;
		ph->lfork = &obs->forks[i];
		ph->rfork = &obs->forks[ph->rightid];
		ph->meal_mx = &obs->meal_mx[i];
		ph->meals = 0;
		ph->obs = obs;
		ph->th = 0;
		i++;
	}
	return (0);
}

static int	init_obs(t_obs *obs)
{
	obs->forks = malloc(sizeof(pthread_mutex_t) * obs->conf.nop);
	if (obs->forks == NULL)
		return (-1);
	obs->meal_mx = malloc(sizeof(pthread_mutex_t) * obs->conf.nop);
	if (obs->meal_mx == NULL)
		return (free(obs->forks), -1);
	if (pthread_mutex_init(&obs->print_mx, NULL) != 0)
		return (free(obs->forks), free(obs->meal_mx), -1);
	if (pthread_mutex_init(&obs->state_mx, NULL) != 0)
		return (free(obs->forks), free(obs->meal_mx),
			pthread_mutex_destroy(&obs->print_mx), -1);
	obs->ph = malloc(sizeof(t_philo) * obs->conf.nop);
	if (obs->ph == NULL)
		return (free(obs->forks), free(obs->meal_mx),
			pthread_mutex_destroy(&obs->state_mx),
			pthread_mutex_destroy(&obs->print_mx), -1);
	if (init_philo(obs) == -1)
		return (pthread_mutex_destroy(&obs->state_mx),
			pthread_mutex_destroy(&obs->print_mx), free(obs->ph), -1);
	obs->start_ms = 0;
	obs->stop = 0;
	obs->monitor_th = 0;
	return (0);
}

int	init(int argc, char **argv, t_obs *obs)
{
	if (validate_input(argc, argv) == -1)
		return (-1);
	initialize_conf(argc, argv, obs);
	if (init_obs(obs) == -1)
		return (write(2, "Failure Initialization\n", 24), -1);
	return(0);
}
