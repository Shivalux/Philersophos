/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:38:25 by sharnvon          #+#    #+#             */
/*   Updated: 2022/09/08 10:09:08 by sharnvon         ###   ########.fr       */
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

/* mode in ft_error_printf */
# define ARG_ERROR 1
# define VALUE_ERROR 2
# define PHILO_ERROR 3

typedef struct s_philo
{
	pthread_t			thread;
	pthread_mutex_t		mutex_fork;
	pthread_mutex_t		mutex_lifetime;
	pthread_mutex_t		mutex_print;
	long int			life;
	int					meal;
}	t_philo;

typedef struct s_table
{
	t_philo				*philo;
	pthread_t			thread;
	pthread_mutex_t		mutex_index;
	pthread_mutex_t		mutex_status;
	unsigned long int	sec;
	unsigned long int	micro;
	unsigned long int	life_time;
	unsigned long int	eat;
	unsigned long int	sleep;
	unsigned long int	philo_status;
	int					amount;
	int					meal;
}	t_table;

void				*ft_calloc(int count, int size);
unsigned long int	ft_atoi(char *str);
unsigned long int	ft_timestamp_cal(t_table *table, int mode);
void				ft_philo_printf(t_table *table, int index, int mode);
void				ft_isleepnow(unsigned long int behave);
void				ft_check_arguments(int argc, char **argv);
void				ft_create_philo(t_table *table, int amount, int count);
void				ft_error_printf(int mode);
void				ft_philo_is_dead(t_table *table, int index);
void				*ft_philo_lifetime(void *elbat);
void				*ft_philo_mealcount(void *elbat);
void				*ft_philo_routine(void *elbat);
t_table				*ft_table_init(t_table *table, char **argv, int index);
t_table				*ft_allocate_table(t_table *table, char **argv);
int					ft_free_resource(t_table *table, int mode);
int					ft_get_index(t_table *table);

#endif
