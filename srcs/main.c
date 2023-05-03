/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:38:10 by fassier-          #+#    #+#             */
/*   Updated: 2022/03/07 12:31:01 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_philo(t_game *game)
{
	int		i;

	i = -1;
	game->philos = malloc(sizeof(t_game) * game->nb_philo);
	game->fork = malloc(sizeof(pthread_mutex_t) * game->nb_philo);
	if (!game->philos || !game->fork)
		return (2);
	while (++i < game->nb_philo)
	{
		game->philos[i].position = i;
		game->philos[i].eat_count = 0;
		game->philos[i].fork_l = i;
		game->philos[i].fork_r = (i + 1) % game->nb_philo;
		if (pthread_mutex_init(&game->philos[i].is_eating, NULL))
			return (3);
		game->philos[i].game = game;
		if (pthread_mutex_init(&game->fork[i], NULL))
			return (3);
	}
	if (pthread_mutex_init(&game->text, NULL))
		return (3);
	return (0);
}

void	check_error(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("erreur : veuillez indiquez un nombre valide\n");
				exit (1);
			}
			j++;
		}
		i++;
	}
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200 || ft_atoi(argv[2]) < 60
		|| ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
	{
		printf("erreur : vos parametres ne sont pas adaptes\n");
		exit (1);
	}
}

void	init_param(t_game *game, int argc, char **argv)
{
	game->nb_philo = ft_atoi(argv[1]);
	game->time_to_die = ft_atoi(argv[2]);
	game->time_to_eat = ft_atoi(argv[3]);
	game->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		game->eat_goal = ft_atoi(argv[5]);
	else
		game->eat_goal = 0;
}

int	main(int argc, char **argv)
{
	t_game		game;
	int			i;

	memset(&game, 0, sizeof(t_game));
	if (argc < 5 || argc > 6)
	{
		printf("erreur : mauvais nombre d'arguments\n");
		return (0);
	}
	check_error(argc, argv);
	init_param(&game, argc, argv);
	i = init_philo(&game);
	if (i != 0)
		return (exit_error(&game, i));
	i = init_thread(&game);
	if (i != 0)
		return (exit_error(&game, 3));
	clean_all(&game);
	return (0);
}
