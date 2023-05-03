/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:37:46 by fassier-          #+#    #+#             */
/*   Updated: 2022/03/03 17:21:10 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	clean_all(t_game *game)
{
	int		i;

	i = 0;
	if (game)
	{
		if (game->fork)
		{
			while (i < game->nb_philo)
				pthread_mutex_destroy(&game->fork[i++]);
			free(game->fork);
		}
		pthread_mutex_destroy(&game->text);
		if (game->philos)
		{
			i = 0;
			while (i < game->nb_philo)
				pthread_mutex_destroy(&game->philos[i++].is_eating);
			free(game->philos);
			game->philos = NULL;
		}
	}
	return (1);
}

int	exit_error(t_game *game, int i)
{
	if (i == 2)
	{
		write(2, "Error : Malloc went wrong\n", 26);
		clean_all(game);
	}
	else if (i == 3)
	{
		write(2, "Error : Mutex went wrong\n", 26);
		clean_all(game);
	}
	return (i);
}
