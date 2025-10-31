/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:58:33 by frocha-b          #+#    #+#             */
/*   Updated: 2025/10/31 11:39:50 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/******************************************************************************/
/*                             Libraries                                      */
/******************************************************************************/
# include "pthread.h"
# include "stdio.h"
# include "unistd.h"
# include "stdlib.h"
# include "limits.h"

/******************************************************************************/
/*                               STRUCTS                                      */
/******************************************************************************/
typedef	struct s_philo
{
	int	id;
}				t_philo;

typedef struct s_data
{
	int		number_of_philos;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int		number_of_meals;	
}				t_data;

/******************************************************************************/
/*                               UTILS                                        */
/******************************************************************************/
long	ft_atol(char *n);
void	ft_exit_error(char *message);
void	ft_putstr_fd(char *s, int fd);

/******************************************************************************/
/*                               PARSER                                       */
/******************************************************************************/
void	validate_args(int argc, char **argv);
void	init_args(t_data *data, int argc, char **argv);
#endif