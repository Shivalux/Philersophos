/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:38:25 by sharnvon          #+#    #+#             */
/*   Updated: 2022/07/09 20:29:15 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				life;
	int				status;
	int				fork;
	int				meal;
	pthread_mutex_t mutex;
}	t_philo;

typedef struct s_table
{
	t_philo			*philo;
	int				amount;
	int				count;
//	int				max_meal;
}	t_table;

void	*ft_calloc(int count, int size);
int		ft_atoi(char *str);
#endif
