/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:54:23 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/13 14:42:31 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	validate_arg_count(int argc)
{
	if (argc != 5 && argc != 6)
		ft_exit_error("Invalid number of arguments (expected 4 or 5).");
}

static void	validate_positive_nbr(long value)
{
	if (value <= 0)
		ft_exit_error("Only positive numeric arguments are allowed.");
}

static void	validate_digit_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_is_digit(argv[i][j]))
				ft_exit_error("Only numeric arguments are allowed.");
			j++;
		}
		i++;
	}
}

void	check_args(int argc, char **argv)
{
	long	nbr_of_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_of_meals;

	validate_arg_count(argc);
	validate_digit_args(argc, argv);
	nbr_of_philos = ft_atol(argv[1]);
	time_to_die = ft_atol(argv[2]);
	time_to_eat = ft_atol(argv[3]);
	time_to_sleep = ft_atol(argv[4]);
	validate_positive_nbr(nbr_of_philos);
	validate_positive_nbr(time_to_die);
	validate_positive_nbr(time_to_eat);
	validate_positive_nbr(time_to_sleep);
	if (argc == 6)
	{
		nbr_of_meals = ft_atol(argv[5]);
		validate_positive_nbr(nbr_of_meals);
	}
}
