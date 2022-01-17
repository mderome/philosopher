/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 10:58:31 by mderome           #+#    #+#             */
/*   Updated: 2022/01/17 15:40:07 by mderome          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <pthread.h>

int	test = 0;

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
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != '\0')
		return (1);
	return (0);
}

void	init_philo(t_philo *info)
{
	pthread_mutex_init(&info->fork, NULL);
	pthread_mutex_init(&info->death, NULL);
	pthread_mutex_init(&info->write, NULL);
	info->p = malloc(sizeof(t_philo) * info->n_p);
}

int	init_arg(t_philo *info, int ac, char **av)
{
	int i;

	i = 1;
	while (i < ac - 1)
	{
		if (str_is_num(av[i]) != 0)
			return (-1);
		i++;
	}
	info->n_p = ft_atoi_f(av[1]);
	info->t_die = ft_atoi_f(av[2]);
	info->t_eat = ft_atoi_f(av[3]);
	info->t_sleep = ft_atoi_f(av[4]);
	if (ac == 6)
		info->nb_eat = ft_atoi_f(av[5]);
	init_philo(info);
	return (0);
}

void	*routine(void *arg_v)
{
	t_philo		*arg;
	int			i;

	arg = (t_philo *)arg_v;
	i = 0;
	printf("entree thread\n");
	pthread_mutex_lock(&arg->write);
	while (i++ < 10)
	{
		test++;
		pthread_mutex_unlock(&arg->write);
	}
	printf("philo number %d\n", arg->p_n);
	printf("t_eat = %d\n", arg->t_eat);
	printf("t_die = %d\n", arg->t_eat);
	printf("t_sleep = %d\n", arg->t_sleep);
	printf("sortie thread\n");
}

int	start_thread(t_philo *arg)
{
	int			i;
	t_timeval	time;

	i = 0;
	if (gettimeofday(&time, NULL) == 0)
		arg->t_start = time.tv_usec;
	printf("time_s = %ld\n", time.tv_usec);
	while (i < arg->n_p)
	{
		arg->p_n = i + 1;
		if (pthread_create(&arg->p[i], NULL, &routine, (void*)arg) != 0)
			return (-1);
		printf("philo [%d] started.\n", i);
		i++;
	}
	usleep(1000);
	pthread_mutex_lock(&arg->fork);
	i = 0;
	while (i < arg->n_p)
	{
		if (pthread_join(arg->p[i], NULL) != 0)
			return (-1);
		printf("philo [%d] finished.\n", i);
		i++;
	}
	pthread_mutex_unlock(&arg->fork);
	printf("test = %d\n", test);
	if (gettimeofday(&time, NULL) == 0)
		printf("time= %ld\n", time.tv_usec - arg->t_start);
	printf("time_s = %ld\n", time.tv_usec);
	pthread_mutex_destroy(&arg->fork);
	pthread_mutex_destroy(&arg->write);
	pthread_mutex_destroy(&arg->death);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	arg;

	if (ac < 5 || ac > 6)
	{
		write(2, "Incorrect number of arguments.", 31);
		return (-1);
	}
	if (init_arg(&arg, ac, av) != 0)
	{
		write(2, "Bad arguments\n", 14);
		return (-2);
	}
	if (start_thread(&arg) != 0)
		return (-1);
	return (0);
}