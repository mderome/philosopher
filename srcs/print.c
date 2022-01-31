/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:12:23 by mderome           #+#    #+#             */
/*   Updated: 2022/01/31 12:55:51 by mderome          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print3(t_philo *ph, int status)
{
	if (status == THINK && ph->info->dead == 0)
	{
		printf("%ld : philo[%d] think.\n", get_time_now(ph->info), ph->id_p);
		pthread_mutex_unlock(&ph->info->death);
		pthread_mutex_unlock(&ph->info->write);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&ph->info->death);
		pthread_mutex_unlock(&ph->info->write);
		return (0);
	}
}

int	ft_print2(t_philo *ph, int status)
{
	if (status == L_FORK && ph->info->dead == 0)
	{
		printf("%ld : philo[%d] take left fork.\n", get_time_now(ph->info),
			ph->id_p);
		pthread_mutex_unlock(&ph->info->death);
		pthread_mutex_unlock(&ph->info->write);
		return (0);
	}
	else if (status == R_FORK && ph->info->dead == 0)
	{
		printf("%ld : philo[%d] take right fork.\n", get_time_now(ph->info),
			ph->id_p);
		pthread_mutex_unlock(&ph->info->death);
		pthread_mutex_unlock(&ph->info->write);
		return (0);
	}
	else if (status == EAT && ph->info->dead == 0)
	{
		printf("%ld : philo[%d] eat.\n", get_time_now(ph->info), ph->id_p);
		pthread_mutex_unlock(&ph->info->death);
		pthread_mutex_unlock(&ph->info->write);
		return (0);
	}
	return (ft_print3(ph, status));
}

int	ft_print(t_philo *ph, int status)
{
	pthread_mutex_lock(&ph->info->death);
	pthread_mutex_lock(&ph->info->write);
	if (status == DEATH && ph->info->dead == 0)
	{
		printf("%ld : philo[%d] is dead.\n", get_time_now(ph->info), ph->id_p);
		ph->info->dead = 1;
		pthread_mutex_unlock(&ph->info->death);
		pthread_mutex_unlock(&ph->info->write);
		return (0);
	}
	else if (status == SLEEP && ph->info->dead == 0)
	{
		printf("%ld : philo[%d] sleep.\n", get_time_now(ph->info), ph->id_p);
		pthread_mutex_unlock(&ph->info->death);
		pthread_mutex_unlock(&ph->info->write);
		return (0);
	}
	else
		return (ft_print2(ph, status));
}
