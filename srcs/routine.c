/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:39:08 by fassier-          #+#    #+#             */
/*   Updated: 2022/03/07 12:31:27 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->fork[philo->fork_l]);
	affichage(philo, 1);
	pthread_mutex_lock(&philo->game->fork[philo->fork_r]);
	affichage(philo, 1);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->game->fork[philo->fork_l]);
	pthread_mutex_unlock(&philo->game->fork[philo->fork_r]);
}

void	eat(t_philo *philo)
{
	affichage(philo, 2);
	philo->last_eat = get_time();
	pthread_mutex_lock(&philo->is_eating);
	usleep(philo->game->time_to_eat * 1000);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->is_eating);
}

void	sleeping(t_philo *philo)
{
	affichage(philo, 3);
	usleep(philo->game->time_to_sleep * 1000);
}
