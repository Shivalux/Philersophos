/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_thread.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 16:07:42 by sharnvon          #+#    #+#             */
/*   Updated: 2022/09/08 10:09:05 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*ft_philo_routine(void *elbat)
{
	t_table		*table;
	int			i;

	table = (t_table *)elbat;
	i = ft_get_index(table);
	while (table->philo_status != FULL && table->philo_status != DEAD)
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
	return (0);
}

int	ft_get_index(t_table *table)
{
	static int	count = 0;
	int			index;

	pthread_mutex_lock(&table->mutex_index);
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
	pthread_mutex_unlock(&table->mutex_index);
	return (index);
}

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
			if (table->philo[index].meal >= table->meal)
				count++;
			index++;
		}
	}
	pthread_mutex_lock(&table->mutex_status);
	table->philo_status = FULL;
	pthread_mutex_unlock(&table->mutex_status);
	return (0);
}

void	*ft_philo_lifetime(void *table)
{
	int	i;

	ft_timestamp_cal((t_table *)table, TIME_REGIS);
	while (((t_table *)table)->philo_status == ALIVE)
	{
		ft_isleepnow(1000);
		i = -1;
		while (++i < ((t_table *)table)->amount)
		{
			pthread_mutex_lock(&((t_table *)table)->philo[i].mutex_lifetime);
			((t_table *)table)->philo[i].life -= 1000;
			pthread_mutex_unlock(&((t_table *)table)->philo[i].mutex_lifetime);
			pthread_mutex_lock(&((t_table *)table)->mutex_status);
			if (((t_table *)table)->philo[i].life <= 0)
			{
				ft_philo_is_dead(table, i);
				return (0);
			}
			pthread_mutex_unlock(&((t_table *)table)->mutex_status);
		}
	}
	return (0);
}

void	ft_philo_printf(t_table *table, int index, int mode)
{
	pthread_mutex_lock(&table->philo[index - 1].mutex_print);
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
	pthread_mutex_unlock(&table->philo[index - 1].mutex_print);
}
