/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:38:25 by sharnvon          #+#    #+#             */
/*   Updated: 2022/09/02 03:41:11 by sharnvon         ###   ########.fr       */
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

# define ALIVE 1
# define DEAD 0
# define FULL 2

# define YES 1
# define NO 0

# define FORK_TAKEN 1
# define EAT 2
# define SLEEP 3
# define THINK 4

# define FAILURE 0
# define SUCCESS 1
typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t mutex;
//	int				index;
	int				life;	// lifepoint => (2)argument, if == 0 philo is dead;
//	int				fork;	// status of fork;
//	unsigned long	used_time;
	int				meal;	// number of time to eat => (optional)(5)argurment; 

}	t_philo;

typedef struct s_table
{
	t_philo				*philo;
	int					amount; // (1st) argument number of philosophers
	unsigned long int	sec;	// timestamp
	unsigned long int	micro;	// timestamp
	pthread_t			thread;
//	int					count;
	int					eat;	// (3rd) argurment: eating time of philosophers
	int					sleep;	// (4th) argurment: sleeping time of philosophers
	int					meal;	// (5th) argurment: max_meal (opional)
	int					timestamp_init;
	int					life_time;	// (2nd) argument: liftpoint | revalue when finish eating;
//	int					reset;
	int					philo_status; // ALIVE: on philo still alive | DEAD: some philo is dead | FULL: all philosopher's meal reach max meal;
//	unsigned long		first_time;
}	t_table;

void	*ft_calloc(int count, int size);
long	ft_atoi(char *str);
void	ft_philo_printf(t_table *table, int index, int mode);
void	ft_isleepnow(t_table *table, int behave);
int		ft_free_resource(t_table *table, int mode);
#endif
