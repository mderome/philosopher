/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:23:11 by mderome           #+#    #+#             */
/*   Updated: 2022/01/31 13:01:12 by mderome          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	ft_len(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	str_is_num(char *str)
{
	int	i ;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] == '0' && str[i + 1] != 0)
		i++;
	if (ft_len(str + i) > 12)
		return (1);
	if (ft_atoi_f(str + i) < 0 || ft_atoi_f(str + i) > INT_MAX)
		return (1);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != '\0')
		return (1);
	return (0);
}

int	philo_is_dead(t_info *info)
{
	pthread_mutex_lock(&info->death);
	if (info->dead)
	{
		pthread_mutex_unlock(&info->death);
		return (1);
	}
	pthread_mutex_unlock(&info->death);
	return (0);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->death);
	if (philo->t_lasteat + philo->info->t_die < get_time_now(philo->info))
	{
		philo->dead = 1;
		pthread_mutex_unlock(&philo->info->death);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->death);
	return (0);
}

int	check_nb_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->lock);
	if (philo->meals == philo->info->nb_eat && philo->info->nb_eat != 0)
	{
		pthread_mutex_unlock(&philo->info->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->lock);
	return (0);
}