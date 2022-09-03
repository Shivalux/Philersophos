/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:38:25 by sharnvon          #+#    #+#             */
/*   Updated: 2022/09/03 18:31:51 by sharnvon         ###   ########.fr       */
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

/* mode in ft_free_resource */
# define FAILURE 0
# define SUCCESS 1

/* status of philosopher */
# define ALIVE 1
# define DEAD 0
# define FULL 2

/* mode in ft_printf_philo */
# define FORK_TAKEN 1
# define EAT 2
# define SLEEP 3
# define THINK 4

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	mutex_fork;
	pthread_mutex_t	mutex_lifetime;
	int				life;	// lifepoint => (2)argument, if == 0 philo is dead;
	int				meal;	// number of time to eat => (optional)(5)argurment; 
}	t_philo;

typedef struct s_table
{
	t_philo				*philo;
	pthread_t			thread;
	unsigned long int	sec;	// timestamp
	unsigned long int	micro;	// timestamp
	int					amount; // (1st) argument number of philosophers
	unsigned long int	life_time;	// (2nd) argument: liftpoint | revalue when finish eating;
	unsigned long int	eat;	// (3rd) argurment: eating time of philosophers
	unsigned long int	sleep;	// (4th) argurment: sleeping time of philosophers
	int	meal;	// (5th) argurment: max_meal (opional)
	unsigned long int	philo_status; // SLEEP: at the start wait untill timestamp is innited | ALIVE: on philo still alive | DEAD: some philo is dead | FULL: all philosopher's meal reach max meal;
}	t_table;

void				*ft_calloc(int count, int size);
unsigned long int	ft_atoi(char *str);
unsigned long int	ft_timestamp_cal(t_table *table, int mode);
void				ft_philo_printf(t_table *table, int index, int mode);
void				ft_isleepnow(unsigned long int behave);
void				ft_check_argurment(int argc, char **argv);
void				ft_create_philo(t_table *table, int amount, int count);
void				*ft_philo_lifetime(void *elbat);
void				*ft_philo_mealcount(void *elbat);
void				*ft_philo_routine(void *elbat);
t_table				*ft_table_init(t_table *table, char **argv, int index);
int					ft_free_resource(t_table *table, int mode);
int					ft_get_index(t_table *table);

#endif
