/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:38:25 by sharnvon          #+#    #+#             */
/*   Updated: 2022/08/31 01:38:10 by sharnvon         ###   ########.fr       */
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

 /* mode in ft_timestamp_cal */
# define TIME_REGIS 1
# define TIME_CAL 2

# define ALIVE 1;
# define DEAD 0;
typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t mutex;
	int				index;
	int				life;	// lifepoint => (2)argument, if == 0 philo is dead;
	int				fork;	// status of fork;
	unsigned long	used_time;
//	int				meal;	// number of time to eat => (optional)(5)argurment; 
//	int				eat;	// status of philo => (3)argument 
//	int				think;	// status of philo
//	int				sleep;	// status of philo => (4)argument

}	t_philo;

typedef struct s_table
{
	t_philo				*philo;
	int					amount; // (1st) argument number of philosophers
	unsigned long int	sec;	// timestamp
	unsigned long int	micro;	// timestamp
	int					count;
	int					eat;	// (3st) argurment: eating time of philosophers
	int					sleep;	// (4th) argurment: sleeping time of philosophers
	int					meal;	// (5th) argurment: max_meal (opional)
	int					save;
	int					life;
	int					reset;
	unsigned long	first_time;
}	t_table;

void	*ft_calloc(int count, int size);
int		ft_atoi(char *str);
#endif
