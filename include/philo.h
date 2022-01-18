/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 10:58:17 by mderome           #+#    #+#             */
/*   Updated: 2022/01/18 12:20:27 by mderome          ###   ########.fr       */
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

typedef struct s_info
{
	int				t_eat;
	int				t_die;
	int				t_sleep;
	int				nb_eat;
	long int		t_start;
	int				n_p;
	pthread_mutex_t	write;
	pthread_mutex_t	fork;
}				t_info;

typedef struct s_philo
{
	pthread_t		p;
	t_info			*info;
	int				p_n;
	int				t_eat;
	int				t_die;
	int				t_sleep;
	int				t_lasteat;
	long int		now;
	pthread_mutex_t	death;
}				t_philo;

int	ft_atoi_f(char *str);
int	start_thread(t_philo *arg, t_info *info);
int	init_arg(t_philo *arg, t_info *info, int ac, char **av);

#endif