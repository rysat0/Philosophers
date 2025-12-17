/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rysato <rysato@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:09:12 by rysato            #+#    #+#             */
/*   Updated: 2025/12/17 21:16:18 by rysato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_num(const char *arg, int *value)
{
	long long	sum;
	int			i;

	sum = 0;
	i = 0;
	if (arg == NULL || arg[0] == '\0')
		return (0);
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (0);
		sum = (sum * 10) + (arg[i] - '0');
		if (sum > INT_MAX)
			return (0);
		i++;
	}
	*value = (int)sum;
	return (1);
}

static int	print_error(int is_argument_error)
{
	if (is_argument_error)
	{
		write(2, "Argument Invalid\n", 18);
		write(2, "[./philo] [number_of_philos] [time_to_die] ", 44);
		write(2, "[time_to_eat] [time_to_sleep] ", 31);
		write(2, "[number_of_times_each_philo_must_eat]\n", 39);
	}
	else
		write(2, "Number Invalid\n", 16);
	return (-1);
}

int	validate_input(int argc, char **argv)
{
	int	parsed_value;
	int	i;

	if (argc != 5 && argc != 6)
		return (print_error(1));
	i = 1;
	while (i <= 4)
	{
		if (!parse_num(argv[i], &parsed_value)
			|| parsed_value <= 0)
			return (print_error(0));
		i++;
	}
	if (argc == 6)
	{
		if (!parse_num(argv[5], &parsed_value) || parsed_value <= 0)
			return (print_error(0));
	}
	return (1);
}

void	initialize_conf(int argc, char **argv, t_obs *obs)
{
	parse_num(argv[1], &obs->conf.nop);
	parse_num(argv[2], &obs->conf.t_die);
	parse_num(argv[3], &obs->conf.t_eat);
	parse_num(argv[4], &obs->conf.t_sleep);
	obs->conf.must_eat = -1;
	if (argc == 6)
		parse_num(argv[5], &obs->conf.must_eat);
	return ;
}
