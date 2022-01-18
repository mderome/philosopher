/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:30:58 by mderome           #+#    #+#             */
/*   Updated: 2022/01/18 15:38:43 by mderome          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(int time, int action, t_philo *arg)
{
	int			i;
	t_timeval	time2;
	int			tmp;

	i = 0;
	while (i < action)
	{
		usleep(10);
		if (gettimeofday(&time2, NULL) == 0)
			tmp = 1000 * time2.tv_sec + time2.tv_usec / 1000;
		if ((tmp - arg->info->t_start) >= time)
			return ;
	}
}

void	sleeping(t_philo *arg)
{
	t_timeval	time;

	if (gettimeofday(&time, NULL) == 0)
		arg->info->now = 1000 * time.tv_sec + time.tv_usec / 1000;
	printf("%ld : philo[%d] sleeping\n", (arg->info->now - arg->info->t_start)
		, arg->p_n);
	ft_sleep(arg->info->now, arg->info->t_sleep, arg);
	routine((void *)arg);
	return ;
}

void	eating(t_philo *arg)
{
	t_timeval	time;
	int			tmp;

	if (gettimeofday(&time, NULL) == 0)
		arg->info->now = 1000 * time.tv_sec + time.tv_usec / 1000;
	printf("time is [%ld]\n", arg->info->now - arg->info->t_start);
	if (arg->p_n == arg->info->n_p)
		tmp = 0;
	else
		tmp = arg->p_n;
	pthread_mutex_lock(&arg->info->fork[tmp]);
	pthread_mutex_lock(&arg->info->fork[arg->p_n - 1]);
	printf("%ld : philo[%d] take right fork\n", (arg->info->now - arg->info->t_start)
		, arg->p_n);
	printf("%ld : philo[%d] take left fork\n", (arg->info->now - arg->info->t_start)
		, arg->p_n);
	printf("%ld : philo[%d] eating\n", (arg->info->now - arg->info->t_start)
		, arg->p_n);
	ft_sleep(arg->info->now, arg->info->t_sleep, arg);
	pthread_mutex_unlock(&arg->info->fork[arg->p_n - 1]);
	pthread_mutex_unlock(&arg->info->fork[tmp]);
	if (arg->info->t_die < arg->now + 10)
		return ;
	sleeping(arg);
	return ;
}

void	*routine(void *arg_v)
{
	t_philo		*arg;

	arg = (t_philo *)arg_v;
	eating(arg);
	return (NULL);
}
