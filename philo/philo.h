/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rysato <rysato@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:29:01 by rysato            #+#    #+#             */
/*   Updated: 2025/11/26 00:15:30 by rysato           ###   ########.fr       */
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

typedef struct s_philo	t_philo;

typedef struct s_conf
{
	int					nop;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					must_eat;
}						t_conf;

typedef struct s_obs
{
	t_conf				conf;
	long long			start_ms;
	volatile int		stop;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*meal_mx;
	pthread_mutex_t		print_mx;
	pthread_mutex_t		state_mx;
	t_philo				*ph;
	pthread_t			monitor_th;
}						t_obs;

typedef struct s_philo
{
	int					id;
	int					leftid;
	int					rightid;
	long long			lastmeal_ms;
	int					meals;
	pthread_t			th;
	t_obs				*obs;
	pthread_mutex_t		*lfork;
	pthread_mutex_t		*rfork;
	pthread_mutex_t		*meal_mx;
}						t_philo;

int						init(int argc, char **argv, t_obs *obs);
int						ft_atoi(const char *str);
long long				elapsed_ms(long long start_ms);
long long				timestamp_ms(void);
void					set_start_time(t_obs *obs);
void					wait_and_destroy(t_obs *obs);
int						start_philo(t_obs *obs);
void					print_safe(t_philo *ph, const char *str);
void					*routine(void *arg);
void					safe_usleep(int ms, t_obs *obs);
void					*monitor(void *arg);
int						is_stop(t_obs *obs);
void					make_lock(t_obs *obs);
int						validate_input(int argc, char **argv);
void					initialize_conf(int argc, char **argv, t_obs *obs);

#endif
