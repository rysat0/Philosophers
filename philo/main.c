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

int main(int argc, char **argv)
{
	t_obs *obs;

	obs = malloc(sizeof(t_obs));
	if(obs == NULL)
		return(EXIT_FAILURE);
	if(init_philos(argc, argv, obs) == -1)
		return(free(obs), EXIT_FAILURE);//ここinit側でphilosをmallocしたらfree

	return(EXIT_SUCCESS);
}
