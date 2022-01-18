/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:13:23 by mderome           #+#    #+#             */
/*   Updated: 2022/01/18 16:58:09 by mderome          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != '\0')
		return (1);
	return (0);
}

t_philo	*init_philo(t_philo *philo, t_info *info)
{
	int			i;
	t_timeval	time;

	i = 0;
	if (gettimeofday(&time, NULL) == 0)
		info->t_start = 1000 * time.tv_sec + time.tv_usec / 1000;
	info->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info->n_p);
	pthread_mutex_init(&info->write, NULL);
	philo = malloc(sizeof(t_philo) * info->n_p);
	while (i < info->n_p)
	{
		philo[i].info = info;
		philo[i].p_n = i + 1;
		pthread_mutex_init(&philo[i].info->death, NULL);
		pthread_mutex_init(&philo[i].info->fork[i], NULL);
		i++;
	}
	return (philo);
}

int	init_arg(t_philo *arg, t_info *info, int ac, char **av)
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
	info->t_die = ft_atoi_f(av[2]);
	info->t_eat = ft_atoi_f(av[3]);
	info->t_sleep = ft_atoi_f(av[4]);
	if (ac == 6)
		info->nb_eat = ft_atoi_f(av[5]);
	arg = init_philo(arg, info);
	if (start_thread(arg, info) != 0)
		return (-1);
	return (0);
}
