/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rysato <rysato@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 21:36:08 by rysato            #+#    #+#             */
/*   Updated: 2025/11/25 18:05:24 by rysato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void join_created(t_obs *obs, int count)
{
	int i;
	i = 0;
	while(i < count)
	{
		pthread_join(obs->ph[i].th, NULL);
		i++;
	}
	return ;
}

void wait_and_destroy(t_obs *obs)
{
	int i;

	i = 0;
	while(i < obs->conf.nop)
	{
		pthread_mutex_destroy(&obs->forks[i]);
		pthread_mutex_destroy(&obs->meal_mx[i]);
		i++;
	}
	pthread_mutex_destroy(&obs->state_mx);
	pthread_mutex_destroy(&obs->print_mx);
	free(obs->meal_mx);
	free(obs->forks);
	free(obs->ph);
	free(obs);
}

int start_philo(t_obs *obs)
{
	int i;

	i = 0;
	while(i < obs->conf.nop)
	{
		if(pthread_create(&obs->ph[i].th, NULL, routine, &obs->ph[i]) != 0)
			return(make_lock(obs), join_created(obs, i), -1);
		i++;
	}
	if(pthread_create(&obs->monitor_th, NULL, monitor, obs) != 0)
		return(make_lock(obs), join_created(obs, obs->conf.nop), -1);
	pthread_join(obs->monitor_th, NULL);
	join_created(obs, obs->conf.nop);
	return(0);
}
