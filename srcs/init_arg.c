/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:13:23 by mderome           #+#    #+#             */
/*   Updated: 2022/01/31 13:02:29 by mderome          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_mutex(t_info *info)
{
	int	i;

	i = 0;
	info->fork = malloc(sizeof(pthread_mutex_t) * info->n_p);
	if (!info->fork)
		return (write(2, "failed malloc fork\n", 20));
	while (i < info->n_p)
	{
		if (pthread_mutex_init(info->fork + i, NULL) != 0)
			return (write(2, "failed create mutex fork\n", 26));
		i++;
	}
	if (pthread_mutex_init(&info->lock, NULL) != 0)
		return (write(2, "failed create mutex fork\n", 26));
	if (pthread_mutex_init(&info->write, NULL) != 0)
		return (write(2, "failed create mutex fork\n", 26));
	if (pthread_mutex_init(&info->death, NULL) != 0)
		return (write(2, "failed create mutex fork\n", 26));
	return (0);
}

void	init_philo(t_info *info, int i)
{
	t_philo	*philo;

	philo = info->philo + i;
	philo->info = info;
	philo->meals = 0;
	philo->id_p = i + 1;
	philo ->t_lasteat = 0;
	philo->left_fork = info->fork + i;
	philo->dead = 0;
	if (i == info->n_p - 1)
		philo->right_fork = info->fork;
	else
		philo->right_fork = info->fork + i + 1;
	if (pthread_create(&philo->thread, NULL, &routine, philo) != 0)
		write(2, "failed to start thread\n", 24);
}

int	init_arg(t_info *info, int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac - 1)
	{
		if (str_is_num(av[i]) != 0)
			return (-1);
		i++;
	}
	info->dead = 0;
	info->n_p = ft_atoi_f(av[1]);
	if (info->n_p == 0)
		return (-1);
	info->t_die = ft_atoi_f(av[2]);
	info->t_eat = ft_atoi_f(av[3]);
	info->t_sleep = ft_atoi_f(av[4]);
	info->t_start = 0;
	info->finish_eat = false;
	if (ac == 6)
		info->nb_eat = ft_atoi_f(av[5]);
	else
		info->nb_eat = 0;
	return (0);
}
