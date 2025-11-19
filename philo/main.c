/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rysato <rysato@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:22:41 by rysato            #+#    #+#             */
/*   Updated: 2025/09/27 16:23:04 by rysato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_obs	*obs;

	obs = malloc(sizeof(t_obs));
	if (obs == NULL)
		return (EXIT_FAILURE);
	if (init(argc, argv, obs) == -1)
		return (free(obs), EXIT_FAILURE);
	//監視スレッド開始
/*スレッド生成ロジックを設計する：t_philo それぞれに pthread_create して routine 関数を走らせ、合わせて monitor_th も立ち上げる流れを main や別関数にまとめる。
哲学者ループの実装：think → forks lock → eat → unlock → sleep というループ関数を作り、偶数/奇数でロック順序を変えるなどデッドロック対策を組み込む。
モニタ実装：全哲学者の lastmeal_ms と meals を監視して、time_to_die 超過や must_eat 達成を検知したら stop フラグを立てるスレッドを作る。
時間管理／出力：gettimeofday を使った timestamp_ms() ヘルパー、print_status のような関数で print_mx を使ってログを整形する。
クリーンアップ：stop フラグ後に全スレッドを join、各ミューテックスを destroy、確保した配列を free する cleanup_obs を用意する。*/
	return (EXIT_SUCCESS);
}
