/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 10:58:31 by mderome           #+#    #+#             */
/*   Updated: 2022/01/18 14:52:26 by mderome          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	free_all(void *philo, t_info *info)
{
	free(info->fork);
	free(philo);
}

int	end_thread(t_philo *arg, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_p)
	{
		if (pthread_join(arg[i].p, NULL) != 0)
			return (-1);
		i++;
	}
	pthread_mutex_destroy(&arg->info->write);
	pthread_mutex_destroy(&arg->death);
	free_all((void *)arg, info);
	return (0);
}

int	start_thread(t_philo *arg, t_info *info)
{
	int			i;
	t_timeval	time;

	i = 0;
	if (gettimeofday(&time, NULL) == 0)
		info->t_start = 1000 * time.tv_sec + time.tv_usec / 1000;
	while (i < info->n_p)
	{
		arg[i].p_n = i + 1;
		if (pthread_create(&arg[i].p, NULL, &routine, (void *)&arg[i]) != 0)
		{
			free_all((void *) arg, info);
			return (-1);
		}
		i++;
	}
	end_thread(arg, info);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	*arg;
	t_info	info;

	arg = NULL;
	if (ac < 5 || ac > 6)
	{
		write(2, "Incorrect number of arguments.", 31);
		return (-1);
	}
	if (init_arg(arg, &info, ac, av) != 0)
	{
		write(2, "Bad arguments\n", 14);
		return (-2);
	}
	return (0);
}
