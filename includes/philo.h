/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:35:57 by fassier-          #+#    #+#             */
/*   Updated: 2022/03/03 17:24:00 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct s_philo
{
	int				position;
	int				eat_count;
	int				last_eat;
	int				fork_l;
	int				fork_r;
	pthread_t		thread;
	pthread_mutex_t	is_eating;
	struct s_game	*game;
}					t_philo;

typedef struct s_game
{
	int				nb_philo;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				eat_goal;
	int				philo_repu;
	int				finish;
	t_philo			*philos;
	pthread_mutex_t	*fork;
	pthread_mutex_t	text;
}					t_game;

/*
** --MAIN--
*/

int					main(int argc, char **argv);

/*
** --TREAD--
*/

int					init_thread(t_game *game);
void				*routine(void *args);
void				*is_he_dead(void *args);
int					check_philo(void *args);
int					get_time(void);

/*
** --ROUTINE--
*/

void				take_forks(t_philo *philo);
void				drop_forks(t_philo *philo);
void				eat(t_philo *philo);
void				sleeping(t_philo *philo);

/*
** --AFFICHAGE--
*/

void				affichage(t_philo *philo, int i);
char				*text(int i);

/*
** --UTILS--
*/

int					ft_atoi(const char *str);
void				ft_putnbr(int n);
int					ft_strlen(const char *s);
int					ft_isdigit(int c);
void				ft_putchar_fd(char c, int fd);

/*
** --EXIT--
*/

int					clean_all(t_game *game);
int					exit_error(t_game *game, int i);

#endif
