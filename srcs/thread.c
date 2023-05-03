/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:39:30 by fassier-          #+#    #+#             */
/*   Updated: 2022/03/03 17:01:59 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	get_time(void)
{
	struct timeval	tv;
	int				i;

	gettimeofday(&tv, NULL);
	i = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (i);
}

int	check_philo(void *args)
{
	t_philo			*philo;

	philo = args;
	if (philo->eat_count >= philo->game->eat_goal)
		philo->game->philo_repu++;
	if (philo->game->philo_repu == philo->game->nb_philo)
	{
		affichage(philo, 6);
		return (1);
	}
	return (0);
}

void	*is_he_dead(void *args)
{
	t_philo			*philo;

	philo = args;
	while (!philo->game->finish)
	{
		pthread_mutex_lock(&philo->is_eating);
		if (!philo->game->finish && \
			get_time() - philo->last_eat > philo->game->time_to_die)
		{
			affichage(philo, 5);
			pthread_mutex_unlock(&philo->is_eating);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->is_eating);
		usleep(100);
	}
	return (NULL);
}

void	*routine(void *args)
{
	t_philo			*philo;

	philo = args;
	philo->last_eat = get_time();
	while (!philo->game->finish)
	{
		take_forks(philo);
		if (philo->game->finish)
			break ;
		eat(philo);
		if (philo->game->finish)
			break ;
		drop_forks(philo);
		if (philo->game->eat_goal > 0 && check_philo(philo))
			break ;
		if (philo->game->finish)
			break ;
		sleeping(philo);
		affichage(philo, 4);
	}
	pthread_mutex_unlock(&philo->game->fork[philo->fork_l]);
	pthread_mutex_unlock(&philo->game->fork[philo->fork_r]);
	pthread_mutex_unlock(&philo->game->text);
	return (NULL);
}

int	init_thread(t_game *game)
{
	int				i;
	pthread_t		thread;

	i = 0;
	while (i < game->nb_philo)
	{
		if (pthread_create(&thread, NULL, routine, (void *)&game->philos[i]))
			return (1);
		pthread_detach(thread);
		if (pthread_create(&game->philos[i].thread, NULL, \
					&is_he_dead, (void *)&game->philos[i]))
			return (1);
		usleep(1000);
		i++;
	}
	i = 0;
	while (i < game->nb_philo)
		pthread_join(game->philos[i++].thread, NULL);
	return (0);
}
