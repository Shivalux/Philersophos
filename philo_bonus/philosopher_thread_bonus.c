/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_thread_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 16:07:42 by sharnvon          #+#    #+#             */
/*   Updated: 2022/09/06 21:40:53 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	*ft_philo_lifetime(void *elbat)
{
	t_table	*table;
	int		index;

	index = 0;
	table = (t_table *)elbat;
	ft_timestamp_cal((t_table *)table, TIME_REGIS);
	while (0 < 1)
	{
		ft_isleepnow(1000);
		sem_wait(((t_table *)table)->sem_lifetime[table->count]);
		((t_table *)table)->life -= 1000;
		sem_post(((t_table *)table)->sem_lifetime[table->count]);
		if (((t_table *)table)->life <= 0)
		{
			sem_wait(table->sem_dead);
			while (index++ < table->amount)
				sem_wait(table->sem_print);
			printf("=> \033[0;33m%lu\033[0m ms, \033[0;36m%d\033[0m \033[0;31m"
				"died.\033[0m\n", ft_timestamp_cal(table, TIME_CAL), index);
	//		((t_table *)table)->philo_status = DEAD;
	//		ft_philo_printf(((t_table *)table), table->count + 1, DEAD);
			exit(1);
		}
	}
	return (0);
}

void	ft_philo_printf(t_table *table, int index, int mode)
{
	sem_wait(table->sem_print);
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
	sem_post(table->sem_print);
/*	else if (mode == DEAD)
	{
		printf("=> \033[0;33m%lu\033[0m ms, \033[0;36m%d\033[0m \033[0;31mdied."
			"\033[0m\n", ft_timestamp_cal(table, TIME_CAL), index);
	}*/
}
