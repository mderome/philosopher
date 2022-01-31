/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:50:44 by mderome           #+#    #+#             */
/*   Updated: 2022/01/31 14:10:42 by mderome          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_fork(t_philo *philo)
{
	if (philo->id_p % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print(philo, L_FORK);
		pthread_mutex_lock(philo->right_fork);
		ft_print(philo, R_FORK);
		return (2);
	}
	pthread_mutex_lock(philo->right_fork);
	ft_print(philo, R_FORK);
	pthread_mutex_lock(philo->left_fork);
	ft_print(philo, L_FORK);
	return (2);
}

long int	get_time(void)
{
	t_timeval	time;

	gettimeofday(&time, NULL);
	return ((1000 * time.tv_sec) + (time.tv_usec / 1000));
}

long int	get_time_now(t_info *info)
{
	return ((get_time() - info->t_start));
}
