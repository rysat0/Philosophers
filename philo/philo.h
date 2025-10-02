/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rysato <rysato@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:29:01 by rysato            #+#    #+#             */
/*   Updated: 2025/10/02 18:29:01 by rysato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_conf
{
	int	nop;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	must_eat;
}		t_conf;

typedef struct s_philo
{
	int				id;
	int				leftid;
	int				rightid;
	int				lastmeal_ms;
	int				meals;
	pthread_t		th;
	t_obs			*obs;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*meal_mx;
}					t_philo;

typedef struct s_obs
{
	t_conf			conf;
	long			start_ms;
	volatile int	stop;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*meal_mx;
	pthread_mutex_t	*print_mx;;
	pthread_mutex_t	*state_mx;
	t_philo			*ph;
	pthread_t		monitor_th;
}					t_obs;

#endif
