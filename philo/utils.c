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

#include <limits.h>
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

static int	skip_space_and_sign(const char *str, int *sign)
{
	int	i;

	i = 0;
	*sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	int			i;
	long long	result;
	int			sign;
	long long	limit;

	result = 0;
	i = skip_space_and_sign(str, &sign);
	if (sign == -1)
		limit = (long long)INT_MAX + 1;
	else
		limit = INT_MAX;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > (limit - (str[i] - '0')) / 10)
		{
			if (sign == -1)
				return (INT_MIN);
			return (INT_MAX);
		}
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return ((int)(result * sign));
}
