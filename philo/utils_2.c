/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rysato <rysato@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:12:30 by rysato            #+#    #+#             */
/*   Updated: 2025/11/26 00:13:22 by rysato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_stop(t_obs *obs)
{
	pthread_mutex_lock(&obs->state_mx);
	if (obs->stop == 1)
		return (pthread_mutex_unlock(&obs->state_mx), 1);
	return (pthread_mutex_unlock(&obs->state_mx), 0);
}

void	make_lock(t_obs *obs)
{
	pthread_mutex_lock(&obs->state_mx);
	obs->stop = 1;
	pthread_mutex_unlock(&obs->state_mx);
	return ;
}
