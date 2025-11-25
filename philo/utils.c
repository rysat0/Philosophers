/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rysato <rysato@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:02:12 by rysato            #+#    #+#             */
/*   Updated: 2025/11/26 00:13:19 by rysato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_start_time(t_obs *obs)
{
	int	i;

	i = 0;
	obs->start_ms = timestamp_ms();
	while (i < obs->conf.nop)
	{
		obs->ph[i].lastmeal_ms = obs->start_ms;
		i++;
	}
	return ;
}

long long	timestamp_ms(void)
{
	long long		time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL);
	return (time);
}

long long	elapsed_ms(long long start_ms)
{
	return (timestamp_ms() - start_ms);
}

static int	minus_judge_space_cut(const char *str, int *judge)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*judge = 1;
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	num;
	int	judge;

	num = 0;
	i = 0;
	judge = 0;
	i = minus_judge_space_cut(str, &judge);
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	if (judge == 1)
		return (-num);
	return (num);
}
