/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 10:58:17 by mderome           #+#    #+#             */
/*   Updated: 2022/01/17 15:38:25 by mderome          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct timeval	t_timeval;

typedef struct s_philo
{
	pthread_t	*p;
	int			n_p;
	int			p_n;
	int			t_eat;
	int			t_die;
	int			t_sleep;
	int			nb_eat;
	int			t_lasteat;
	long int	now;
	long int	t_start;
	pthread_mutex_t	write;
	pthread_mutex_t	fork;
	pthread_mutex_t	death;
}				t_philo;

int	ft_atoi_f(char *str);

#endif