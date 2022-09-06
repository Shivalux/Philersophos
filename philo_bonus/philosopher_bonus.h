/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:38:25 by sharnvon          #+#    #+#             */
/*   Updated: 2022/09/06 21:24:14 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_BONUS_H
# define PHILOSOPHER_BONUS_H

# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>

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

# define SEMLIFE "/semaphore_lifetime"
# define SEMFORK "/semaphore_fork"
# define SEMDEAD "/semaphore_dead"
# define SEPRINT "/semaphore_print"

typedef struct s_table
{
	pthread_t			thread;
	sem_t				*sem_fork;
	sem_t				*sem_dead;
	sem_t				*sem_print;
	sem_t				**sem_lifetime;
	unsigned long int	sec;
	unsigned long int	micro;
	unsigned long int	life_time;
	unsigned long int	eat;
	unsigned long int	sleep;
	unsigned long int	philo_status;
	int					amount;
	int					meal;
	int					count;
	int					max_meal;
	long int			life;
	pid_t				*pid;
}	t_table;

void				*ft_calloc(int count, int size);
unsigned long int	ft_atoi(char *str);
unsigned long int	ft_timestamp_cal(t_table *table, int mode);
void				ft_philo_printf(t_table *table, int index, int mode);
void				ft_isleepnow(unsigned long int behave);
void				ft_check_arguments(int argc, char **argv);
void				ft_philo_routine(t_table *table);
int					ft_create_philo(t_table *table);
void				*ft_philo_lifetime(void *elbat);
void				*ft_philo_mealcount(void *elbat);
t_table				*ft_table_init(t_table *table, char **argv, int i);
t_table				*ft_allocate_data(t_table *table, char **argv);
int					ft_free_resource(t_table *table, int mode);
int					ft_get_index(t_table *table);
int					ft_strslen(char *str1, char *str2);
char				*ft_strjoin(char *str1, char *str2);
char				*ft_positive_itoa(int number);

#endif
