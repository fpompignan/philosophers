/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:37:05 by fassier-          #+#    #+#             */
/*   Updated: 2022/03/03 16:40:02 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

char	*text(int i)
{
	if (i == 1)
		return (" has taken a fork\n");
	else if (i == 2)
		return (" is eating\n");
	else if (i == 3)
		return (" is sleeping\n");
	else if (i == 4)
		return (" is thinking\n");
	else if (i == 5)
		return (" died\n");
	return (NULL);
}

void	affichage(t_philo *philo, int i)
{
	char			*tmp;

	pthread_mutex_lock(&philo->game->text);
	if (!philo->game->finish)
	{
		if (i != 6)
		{
			tmp = text(i);
			ft_putnbr(get_time());
			write(1, " ", 1);
			ft_putnbr(philo->position + 1);
			write(1, tmp, ft_strlen(tmp));
			tmp = NULL;
		}
		if (i == 5 || i == 6)
		{
			philo->game->finish = 1;
			return ;
		}
	}
	pthread_mutex_unlock(&philo->game->text);
}
