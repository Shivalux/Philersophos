/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_thread_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 16:07:42 by sharnvon          #+#    #+#             */
/*   Updated: 2022/09/09 02:32:11 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	*ft_philo_lifetime(void *elbat)
{
	t_table	*table;
	int		index;

	table = (t_table *)elbat;
	ft_timestamp_cal((t_table *)table, TIME_REGIS);
	while (table->philo_status == ALIVE)
	{
		ft_isleepnow(1000);
		sem_wait(((t_table *)table)->sem_lifetime[table->count]);
		((t_table *)table)->life -= 1000;
		sem_post(((t_table *)table)->sem_lifetime[table->count]);
		sem_wait(table->sem_status[table->count]);
		if (((t_table *)table)->life <= 0)
		{
			sem_wait(table->sem_dead);
			index = 0;
			while (index++ < table->amount)
				sem_wait(table->sem_print);
			printf("=> \033[0;33m%lu\033[0m ms, \033[0;36m%d\033[0m \033[0;31m"
				"died.\033[0m\n", ft_timestamp_cal(table, 2), table->count + 1);
			exit(1);
		}
		sem_post(table->sem_status[table->count]);
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
}

// t_table	*ft_allocate_data(t_table *table, char **argv, int amount)
// {
// 	table = (t_table *)ft_calloc(sizeof(t_table), 1);
// 	if (table == NULL)
// 		return (0);
// 	table->pid = (int *)ft_calloc(sizeof(int), amount);
// 	if (table->pid == NULL)
// 	{
// 		free(table);
// 		return (0);
// 	}
// 	table->sem_lifetime = (sem_t **)ft_calloc(sizeof(sem_t *), amount);
// 	if (table->sem_lifetime == NULL)
// 	{
// 		free(table->pid);
// 		free(table);
// 		return (0);
// 	}
// 	table->sem_status = (sem_t **)ft_calloc(sizeof(sem_t *), amount);
// 	if (table->sem_status == NULL)
// 	{
// 		free(table->pid);
// 		free(table->sem_lifetime);
// 		free(table);
// 		return (0);
// 	}
// 	return (table);
// }

/* helper functoin form ft_argurment_check */
void	ft_error_printf(int mode)
{
	if (mode == ARG_ERROR)
	{
		printf("ERROR: THE NUMBER OF THE AGUMENT IS WRONG :(\n");
		printf(" (hint) ./philo [number of philos] [time to die] [time to eat]"
			" [time to sleep] [(optional): number of time to eat]\n");
	}
	if (mode == VALUE_ERROR)
		printf("ERROR: VALUE OF AGURMENTS MUST BE POSITIVE NUMBER..\n");
	if (mode == PHILO_ERROR)
		printf("ERROR: THE NUMBER OF PHILOSOPHER MUST BE ONE OR MORE..\n");
	exit(EXIT_FAILURE);
}
