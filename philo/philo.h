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

typedef struct s_philo t_philo;

typedef struct s_conf//設定構造体
{
	int	nop;//num of philo
	int	t_die;//time to die
	int	t_eat;//time to eat
	int	t_sleep;//time to sleep
	int	must_eat;//必須食事回数
}		t_conf;

typedef struct s_obs//観測者の構造体
{
	t_conf			conf;//設定読み込み
	long long		start_ms;//開始時刻
	volatile int	stop;//終了フラグ
	pthread_mutex_t	*forks;//フォーク
	pthread_mutex_t	*meal_mx;//食事情報のミューテックス
	pthread_mutex_t	print_mx;//ログ出力用
	pthread_mutex_t	state_mx;//状態共有用
	t_philo			*ph;//philoたちの管理
	pthread_t		monitor_th;//監視スレッド
}					t_obs;

typedef struct s_philo//philoそれぞれの構造体
{
	int				id;//自分のforkid
	int				leftid;//左のforkid
	int				rightid;//右
	long long		lastmeal_ms;//最後に食べた時刻
	int				meals;//食べた回数
	pthread_t		th;//スレッド
	t_obs			*obs;//管理構造体
	pthread_mutex_t	*lfork;//左フォークへのmutexポインタ
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*meal_mx;//食事データmutex
}					t_philo;


int init(int argc, char **argv, t_obs *obs);
int	ft_atoi(const char *str);
long long elapsed_ms(long long start_ms);
long long timestamp_ms(void);
void set_start_time(t_obs *obs);
void wait_and_destroy(t_obs *obs);
int start_philo(t_obs *obs);
void print_safe(t_philo *ph, const char *str);
void *routine(void *arg);
void safe_usleep(int ms, t_obs *obs);
void *monitor(void *arg);
int is_stop(t_obs *obs);
void make_lock(t_obs *obs);

#endif
