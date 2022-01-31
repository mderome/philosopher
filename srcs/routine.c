/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:30:58 by mderome           #+#    #+#             */
/*   Updated: 2022/01/31 14:13:16 by mderome          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(int action, t_philo *philo)
{
	int			start;
	int			now;

	start = get_time_now(philo->info);
	now = start;
	while (action > now - start)
	{
		if (check_death(philo) || check_nb_eat(philo))
		{
			ft_print(philo, DEATH);
			return ;
		}
		usleep(100);
		now = get_time_now(philo->info);
	}
}

void	eating(t_philo *philo)
{
	if (philo->info->n_p == 1)
	{
		ft_print(philo, L_FORK);
		ft_sleep(philo->info->t_die, philo);
		ft_print(philo, DEATH);
		return ;
	}
	mutex_fork(philo);
	philo->t_lasteat = get_time_now(philo->info);
	ft_print(philo, EAT);
	ft_sleep(philo->info->t_sleep, philo);
	pthread_mutex_unlock(philo->right_fork);
	if (philo->info->n_p != 1)
		pthread_mutex_unlock(philo->left_fork);
}

void	sleeping(t_philo *philo)
{
	ft_print(philo, SLEEP);
	ft_sleep(philo->info->t_sleep, philo);
	ft_print(philo, THINK);
}

void	who_is_dead(t_philo *philo)
{
	if (philo->dead == 1)
		ft_print(philo, SLEEP);
}

void	*routine(void *arg_v)
{
	t_philo		*philo;

	philo = (t_philo *)arg_v;
	if (philo->info->n_p % 2 == 0)
		usleep(1000);
	while (philo_is_dead(philo->info) == 0 && check_nb_eat(philo) == 0)
	{
		eating(philo);
		if (philo_is_dead(philo->info) == 1 || check_nb_eat(philo) == 1)
		{
			if (philo_is_dead(philo->info) == 1 && philo->info->dead == 0)
				who_is_dead(philo);
			break ;
		}
		sleeping(philo);
	}
	return (NULL);
}
