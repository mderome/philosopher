/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 10:58:17 by mderome           #+#    #+#             */
/*   Updated: 2022/01/31 14:10:59 by mderome          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>

# define EAT 0
# define SLEEP 1
# define THINK 2
# define R_FORK 3
# define L_FORK 4
# define DEATH 5

typedef struct timeval	t_timeval;
typedef struct s_philo	t_philo;

typedef struct s_info
{
	int				t_eat;
	int				t_die;
	int				t_sleep;
	int				nb_eat;
	int				n_p;
	int				dead;
	bool			finish_eat;
	long int		t_start;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	death;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}				t_info;

typedef struct s_philo
{
	t_info			*info;
	int				meals;
	int				id_p;
	int				dead;
	long int		t_lasteat;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}				t_philo;

int			ft_atoi_f(char *str);
void		start_thread(t_info *info);
int			init_arg(t_info *info, int ac, char **av);
void		init_philo(t_info *info, int i);
void		*routine(void *arg_v);
void		eating(t_philo *arg);
int			start_mutex(t_info *info);
int			str_is_num(char *str);
int			philo_is_dead(t_info *info);
int			check_death(t_philo *philo);
int			ft_len(char *str);
int			check_nb_eat(t_philo *philo);
long int	get_time(void);
long int	get_time_now(t_info *info);
int			ft_print(t_philo *ph, int status);
int			mutex_fork(t_philo *philo);

#endif