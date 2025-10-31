/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:54:23 by frocha-b          #+#    #+#             */
/*   Updated: 2025/10/14 18:13:28 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	validate_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		exit_error("Please insert 4 or 5 arguments.");
	if (ft_atol(argv[1]) <= 0 || ft_atol(argv[1] > INT_MAX))
		exit_error("Please, insert an positive integer number of philos.");
	if (ft_atol(argv[2]) < 60 || ft_atol(argv[3]) < 60 || ft_atol(argv[4]) < 60)
		exit_error("Please, insert only valid times.");
	if (argc == 6)
	{
		if (ft_atol(argv[5]) <= 0)
			exit_error("Please, insert valid times to eat.");
	}
}
