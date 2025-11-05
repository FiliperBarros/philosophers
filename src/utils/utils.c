/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha-b <frocha-b@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:47:41 by frocha-b          #+#    #+#             */
/*   Updated: 2025/11/05 11:29:56 by frocha-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

long	ft_atol(char *n)
{
	int		i;
	int		signal;
	long 	res;

	i = 0;
	signal = 1;
	res = 0;
	while (n[i] == ' ' || (n[i] >= 9 && n[i] <= 13))
		i++;
	if (n[i] == '+' || n[i] == '-')
	{
		if (n[i] == '-')
			signal *= -1;
		i++;
	}
	while (n[i] >= '0' && n[i] <= '9')
	{
		res = res * 10 + (n[i] - '0');
		i++;
	}
	return (res * signal);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
}


void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = c;
		i++;
	}
	return (s);
}

long	get_time_in_ms()
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + current_time.tv_usec / 1000);
}

