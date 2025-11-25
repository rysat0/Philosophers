/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rysato <rysato@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:41:54 by rysato            #+#    #+#             */
/*   Updated: 2025/11/25 20:11:51 by rysato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	load_meal_conf(t_obs *obs, long long *last_meal_ms, int *meal_times,
		int i)
{
	pthread_mutex_lock(&obs->meal_mx[i]);
	*last_meal_ms = obs->ph[i].lastmeal_ms;
	*meal_times = obs->ph[i].meals;
	pthread_mutex_unlock(&obs->meal_mx[i]);
	return ;
}

static int	is_philo_die(t_obs *obs, long long last_meal_ms, int i)
{
	if ((timestamp_ms() - last_meal_ms) >= obs->conf.t_die)
	{
		pthread_mutex_lock(&obs->state_mx);
		if (!(obs->stop))
		{
			obs->stop = 1;
			pthread_mutex_lock(&obs->print_mx);
			printf("%lld %d died\n", elapsed_ms(obs->start_ms), obs->ph[i].id
				+ 1);
			pthread_mutex_unlock(&obs->print_mx);
		}
		pthread_mutex_unlock(&obs->state_mx);
		return (1);
	}
	return (0);
}

static int	count_meals(t_obs *obs, int meal_times, int philo_full_count)
{
	if ((obs->conf.must_eat > 0) && (meal_times >= obs->conf.must_eat))
		return (philo_full_count + 1);
	return (philo_full_count);
}

static int	is_all_full(t_obs *obs, int philo_full_count)
{
	if ((obs->conf.must_eat > 0) && (philo_full_count == obs->conf.nop))
	{
		pthread_mutex_lock(&obs->state_mx);
		obs->stop = 1;
		pthread_mutex_unlock(&obs->state_mx);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_obs		*obs;
	int			philo_full_count;
	long long	last_meal_ms;
	int			meal_times;
	int			i;

	obs = (t_obs *)arg;
	philo_full_count = 0;
	i = 0;
	last_meal_ms = 0;
	meal_times = 0;
	while (is_stop(obs) == 0)
	{
		if (i == 0)
			philo_full_count = 0;
		load_meal_conf(obs, &last_meal_ms, &meal_times, i);
		if (is_philo_die(obs, last_meal_ms, i) == 1)
			return (NULL);
		philo_full_count = count_meals(obs, meal_times, philo_full_count);
		if (is_all_full(obs, philo_full_count) == 1)
			return (NULL);
		i = (i + 1) % obs->conf.nop;
		usleep(10);
	}
	return (NULL);
}
