/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderome <mderome@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:50:44 by mderome           #+#    #+#             */
/*   Updated: 2022/01/18 16:53:13 by mderome          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(void)
{
	t_timeval	time;

	gettimeofday(&time, NULL);
	return (1000 * time.tv_sec + time.tv_usec / 1000);
}