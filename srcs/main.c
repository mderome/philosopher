/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 10:58:31 by mderome           #+#    #+#             */
/*   Updated: 2022/01/31 13:03:30 by mderome          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	free_all(t_info *info)
{
	if (info->fork)
		free(info->fork);
	info->fork = NULL;
	if (info->philo)
		free(info->philo);
	info->philo = NULL;
}

void	end_thread(t_info *info)
{
	int		i;
	t_philo	*ph;

	i = 0;
	while (i < info->n_p)
	{
		ph = info->philo + i;
		if (pthread_join(ph->thread, NULL) != 0)
		{
			write(2, "failed to join thread\n", 23);
			return ;
		}
		i++;
	}
	pthread_mutex_destroy(&info->write);
	pthread_mutex_destroy(&info->death);
	pthread_mutex_destroy(&info->lock);
	i = 0;
	while (i < info->n_p)
	{
		pthread_mutex_destroy(info->fork + i);
		i++;
	}
	free_all(info);
}

int	create_thread(t_info *info)
{
	int	i;

	i = 0;
	info->philo = malloc(sizeof(t_philo) * info->n_p + 1);
	if (!info->philo)
		return (write(2, "failed to malloc philo\n", 24));
	while (i < info->n_p)
	{
		init_philo(info, i);
		i++;
	}
	return (0);
}

void	start_thread(t_info *info)
{
	if (start_mutex(info) != 0)
	{
		free_all(info);
		return ;
	}
	info->t_start = get_time();
	if (create_thread(info) != 0)
	{
		free_all(info);
		return ;
	}
	end_thread(info);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (ac < 5 || ac > 6)
	{
		write(2, "Incorrect number of arguments.", 31);
		return (-1);
	}
	if (init_arg(&info, ac, av) != 0)
	{
		write(2, "Bad arguments\n", 14);
		return (-2);
	}
	start_thread(&info);
	return (0);
}
