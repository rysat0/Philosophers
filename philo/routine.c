/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rysato <rysato@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:41:49 by rysato            #+#    #+#             */
/*   Updated: 2025/11/25 16:14:45 by rysato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_safe(t_philo *ph, const char *str)
{
	t_obs *obs;
	long long now;

	obs = ph->obs;
	pthread_mutex_lock(&obs->print_mx);
	if(!(obs->stop))
	{
		now = elapsed_ms(obs->start_ms);
		printf("%lld %d %s\n", now, (ph->id) + 1, str);
	}
	pthread_mutex_unlock(&obs->print_mx);
	return ;
}

void safe_usleep(int ms, t_obs *obs)
{
	long long start;
	long long elapsed;

	start = timestamp_ms();
	while(!obs->stop)
	{
		elapsed = timestamp_ms() - start;
		if(elapsed >= ms)
			break;
		usleep(10);
	}
	return ;
}

static void routine_one(t_philo *ph)
{
	pthread_mutex_lock(ph->lfork);
	print_safe(ph, "has taken a fork");
	safe_usleep(ph->obs->conf.t_die, ph->obs);
	pthread_mutex_unlock(ph->lfork);
	return ;
}

static void take_forks(t_philo *ph)
{
	if((ph->id % 2) == 0)
	{
		pthread_mutex_lock(ph->lfork);
		print_safe(ph, "has taken a fork");
		pthread_mutex_lock(ph->rfork);
		print_safe(ph, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(ph->rfork);
		print_safe(ph, "has taken a fork");
		pthread_mutex_lock(ph->lfork);
		print_safe(ph, "has taken a fork");
	}
	return ;
}

void *routine(void *arg)
{
	t_philo *ph;

	ph = (t_philo *)arg;
	if(ph->obs->conf.nop == 1)
		return(routine_one(ph), NULL);
	while(!(ph->obs->stop))
	{
		take_forks(ph);
		pthread_mutex_lock(ph->meal_mx);
		print_safe(ph, "is eating");
		ph->lastmeal_ms = timestamp_ms();
		safe_usleep(ph->obs->conf.t_eat, ph->obs);
		(ph->meals)++;
		pthread_mutex_unlock(ph->meal_mx);
		pthread_mutex_unlock(ph->lfork);
		pthread_mutex_unlock(ph->rfork);
		print_safe(ph, "is sleeping");
		safe_usleep(ph->obs->conf.t_sleep, ph->obs);
		print_safe(ph, "is thinking");
	}
	return NULL;
}
