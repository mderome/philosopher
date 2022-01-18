/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:30:58 by mderome           #+#    #+#             */
/*   Updated: 2022/01/18 17:00:36 by mderome          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(int time, int action, t_philo *arg)
{
	int			tmp;
	int			tmp2;

	tmp2 = time;
	while (1)
	{
		usleep(100);
		tmp = get_time();
		if (arg->t_lasteat + (tmp - tmp2) >= arg->info->t_die)
		{
			arg->info->dead = 1;
			printf("%ld : philo[%d] dead\n", (get_time() - arg->info->t_start)
			, arg->p_n);
			exit(0);
		}
		if (tmp - tmp2 >= action)
			return ;
	}
}

void	thinking(t_philo *arg)
{
	t_timeval	time;

	pthread_mutex_lock(&arg->info->death);
	if (arg->info->dead == 1)
		return ;
	pthread_mutex_unlock(&arg->info->death);
	if (gettimeofday(&time, NULL) == 0)
		arg->info->now = get_time();
	pthread_mutex_lock(&arg->info->write);
	printf("%ld : philo[%d] think\n", (arg->info->now - arg->info->t_start)
		, arg->p_n);
	pthread_mutex_unlock(&arg->info->write);
	ft_sleep(arg->info->now, arg->info->t_die - (arg->info->t_sleep + arg->info->nb_eat), arg);
	eating(arg);
	if (arg->info->t_die < arg->now + 10)
	{
		printf("philo is dead\n");
		return ;
	}
	return ;
}

void	sleeping(t_philo *arg)
{
	t_timeval	time;

	pthread_mutex_lock(&arg->info->death);
	if (arg->info->dead == 1)
		return ;
	pthread_mutex_unlock(&arg->info->death);
	if (gettimeofday(&time, NULL) == 0)
		arg->info->now = 1000 * time.tv_sec + time.tv_usec / 1000;
	pthread_mutex_lock(&arg->info->write);
	printf("%ld : philo[%d] sleeping\n", (arg->info->now - arg->info->t_start)
		, arg->p_n);
	pthread_mutex_unlock(&arg->info->write);
	ft_sleep(arg->info->now, arg->info->t_sleep, arg);
	thinking(arg);
	if (arg->info->t_die < arg->now + 10)
	{
		printf("philo is dead\n");
		return ;
	}
	return ;
}

void	eating(t_philo *arg)
{
	t_timeval	time;
	int			tmp;

	pthread_mutex_lock(&arg->info->death);
	if (arg->info->dead == 1)
		return ;
	pthread_mutex_unlock(&arg->info->death);
	if (gettimeofday(&time, NULL) == 0)
		arg->info->now = 1000 * time.tv_sec + time.tv_usec / 1000;
	if (arg->p_n == arg->info->n_p)
		tmp = 0;
	else
		tmp = arg->p_n;
	pthread_mutex_lock(&arg->info->fork[tmp]);
	pthread_mutex_lock(&arg->info->fork[arg->p_n - 1]);
	pthread_mutex_lock(&arg->info->write);
	printf("%ld : philo[%d] take right fork\n", (arg->info->now - arg->info->t_start)
		, arg->p_n);
	printf("%ld : philo[%d] take left fork\n", (arg->info->now - arg->info->t_start)
		, arg->p_n);
	printf("%ld : philo[%d] eating\n", (arg->info->now - arg->info->t_start)
		, arg->p_n);
	pthread_mutex_unlock(&arg->info->write);
	ft_sleep(arg->info->now, arg->info->t_sleep, arg);
	arg->t_lasteat = arg->info->now;
	pthread_mutex_unlock(&arg->info->fork[arg->p_n - 1]);
	pthread_mutex_unlock(&arg->info->fork[tmp]);
	if (arg->info->t_die < arg->now + 10)
	{
		printf("philo is dead\n");
		return ;
	}
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
