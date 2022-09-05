/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_thread_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 16:07:42 by sharnvon          #+#    #+#             */
/*   Updated: 2022/09/06 05:43:12 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

/*
void	*ft_philo_routine(void *elbat)
{
	t_table		*table;
	int			i;

	table = (t_table *)elbat;
	i = ft_get_index(table);
	while (1 > 0)
	{
		pthread_mutex_lock(&table->philo[i].mutex_fork);
		ft_philo_printf(table, i + 1, FORK_TAKEN);
		pthread_mutex_lock(&table->philo[(i + 1) % table->amount].mutex_fork);
		ft_philo_printf(table, i + 1, FORK_TAKEN);
		ft_philo_printf(table, i + 1, EAT);
		ft_isleepnow(table->eat);
		pthread_mutex_lock(&table->philo[i].mutex_lifetime);
		table->philo[i].life = table->life_time;
		pthread_mutex_unlock(&table->philo[i].mutex_lifetime);
		table->philo[i].meal++;
		pthread_mutex_unlock(&table->philo[i].mutex_fork);
		pthread_mutex_unlock(&table->philo[(i + 1) % table->amount].mutex_fork);
		ft_philo_printf(table, i + 1, SLEEP);
		ft_isleepnow(table->sleep);
		ft_philo_printf(table, i + 1, THINK);
	}
}

int	ft_get_index(t_table *table)
{
	static int	count = 0;
	int			index;

	if (count + 1 > table->amount)
		count = 1;
	index = count;
	if (count + 2 != table->amount)
		count += 2;
	else
		count++;
	while (table->philo_status == SLEEP)
	{
	}
	return (index);
}
*/
void	*ft_philo_mealcount(void *elbat)
{
	int		count;
	int		index;
	t_table	*table;

	table = (t_table *)elbat;
	count = 0;
	while (count != table->amount)
	{
		index = 0;
		count = 0;
		while (index < table->amount)
		{
		//	printf("philo[%d].meal == %d\n", index, table->philo[index].meal);
			if (table->philo[index].meal >= table->meal)
				count++;
			index++;
		}
	}
	table->philo_status = FULL;
	return (0);
}

void	*ft_philo_lifetime(void *elbat)
{
//	int	i;
	t_table	*table;

	table = (t_table *)elbat;
	ft_timestamp_cal((t_table *)table, TIME_REGIS);
	while (0 < 1)
	{
		ft_isleepnow(1000);
//		i = -1;
//		while (++i < ((t_table *)table)->amount)
//		{
		//	pthread_mutex_lock(&((t_table *)table)->philo[i].mutex_lifetime);
			sem_wait(((t_table *)table)->philo[table->count].sem_lifetime);
			((t_table *)table)->philo[table->count].life -= 1000;
			sem_post(((t_table *)table)->philo[table->count].sem_lifetime);
		//	pthread_mutex_unlock(&((t_table *)table)->philo[i].mutex_lifetime);
			if (((t_table *)table)->philo[table->count].life <= 0)
			{
				((t_table *)table)->philo_status = DEAD;
				ft_philo_printf(((t_table *)table), table->count + 1, DEAD);
//				printf("(lifetime)kill) count = %d\n", table->count);
//				kill(table->pid[table->count - 1], SIGINT);
				exit(0);
			}
			if (((t_table *)table)->philo_status == FULL)
				return (0);
//		}
	}
	return (0);
}

void	ft_philo_printf(t_table *table, int index, int mode)
{
	if (mode == FORK_TAKEN && table->philo_status == ALIVE)
	{
		printf("=> \033[0;33m%lu\033[0m ms, \033[0;36m%d\033[0m has taken"
			" a fork.\n", ft_timestamp_cal(table, TIME_CAL), index);
	}
	else if (mode == EAT && table->philo_status == ALIVE)
	{
		printf("=> \033[0;33m%lu\033[0m ms, \033[0;36m%d\033[0m is eating.\n",
			ft_timestamp_cal(table, TIME_CAL), index);
	}
	else if (mode == SLEEP && table->philo_status == ALIVE)
	{
		printf("=> \033[0;33m%lu\033[0m ms, \033[0;36m%d\033[0m is sleeping.\n",
			ft_timestamp_cal(table, TIME_CAL), index);
	}
	else if (mode == THINK && table->philo_status == ALIVE)
	{
		printf("=> \033[0;33m%lu\033[0m ms, \033[0;36m%d\033[0m is thinking.\n",
			ft_timestamp_cal(table, TIME_CAL), index);
	}
	else if (mode == DEAD)
	{
		printf("=> \033[0;33m%lu\033[0m ms, \033[0;36m%d\033[0m \033[0;31mdied."
			"\033[0m\n", ft_timestamp_cal(table, TIME_CAL), index);
	}
}
