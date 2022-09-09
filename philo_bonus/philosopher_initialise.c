/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_initialise.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 13:44:07 by sharnvon          #+#    #+#             */
/*   Updated: 2022/09/09 23:43:06 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

t_table	*ft_table_init(t_table *table, char **argv, int i)
{
	table = ft_allocate_data(table, (int)ft_atoi(argv[1]));
	if (table == NULL)
		return (0);
	table->amount = ft_atoi(argv[1]);
	table->eat = ft_atoi(argv[3]) * 1000;
	table->sleep = ft_atoi(argv[4]) * 1000;
	table->life_time = ft_atoi(argv[2]) * 1000;
	table->philo_status = SLEEP;
	table->life = ft_atoi(argv[2]) * 1000;
	table->max_meal = -1;
	if (argv[5] != NULL)
		table->max_meal = ft_atoi(argv[5]);
	sem_unlink(SEMDEAD);
	table->sem_dead = sem_open(SEMDEAD, O_CREAT | O_EXCL, 0644, 1);
	sem_unlink(SEMFORK);
	table->sem_fork = sem_open(SEMFORK, O_CREAT | O_EXCL, 0644, table->amount);
	sem_unlink(SEPRINT);
	table->sem_print = sem_open(SEPRINT, O_CREAT | O_EXCL, 0644, table->amount);
	table = ft_semaphore_loopinnit(table, i);
	return (table);
}

t_table	*ft_semaphore_loopinnit(t_table *table, int i)
{
	char	*semaphore;

	while (i < table->amount)
	{
		semaphore = ft_strjoin(SEMLIFE, ft_positive_itoa(i));
		sem_unlink(semaphore);
		table->sem_lifetime[i] = sem_open(semaphore, O_CREAT | O_EXCL, 0644, 1);
		free(semaphore);
		semaphore = ft_strjoin(SESTATE, ft_positive_itoa(i));
		sem_unlink(semaphore);
		table->sem_status[i++] = sem_open(semaphore, O_CREAT | O_EXCL, 0644, 1);
		free(semaphore);
	}
	return (table);
}

t_table	*ft_allocate_data(t_table *table, int amount)
{
	table = (t_table *)ft_calloc(sizeof(t_table), 1);
	if (table == NULL)
		return (0);
	table->pid = (int *)ft_calloc(sizeof(int), amount);
	if (table->pid == NULL)
	{
		free(table);
		return (0);
	}
	table->sem_lifetime = (sem_t **)ft_calloc(sizeof(sem_t *), amount);
	if (table->sem_lifetime == NULL)
	{
		free(table->pid);
		free(table);
		return (0);
	}
	table->sem_status = (sem_t **)ft_calloc(sizeof(sem_t *), amount);
	if (table->sem_status == NULL)
	{
		free(table->pid);
		free(table->sem_lifetime);
		free(table);
		return (0);
	}
	return (table);
}

int	ft_free_resource(t_table *table, int mode)
{
	ft_semaphore_loopclose(table);
	sem_unlink(SEPRINT);
	sem_close(table->sem_print);
	sem_unlink(SEMDEAD);
	sem_close(table->sem_dead);
	sem_unlink(SEMFORK);
	sem_close(table->sem_fork);
	pthread_detach(table->thread);
	free(table->pid);
	free(table->sem_lifetime);
	free(table->sem_status);
	free(table);
	if (mode == FAILURE)
		exit(EXIT_FAILURE);
	return (0);
}

void	ft_semaphore_loopclose(t_table *table)
{
	int		count;
	char	*semaphore;

	count = 0;
	while (count < table->amount)
	{
		pthread_detach(table->thread);
		semaphore = ft_strjoin(SESTATE, ft_positive_itoa(count));
		sem_unlink(semaphore);
		sem_close(table->sem_status[count]);
		free(semaphore);
		semaphore = ft_strjoin(SEMLIFE, ft_positive_itoa(count));
		sem_unlink(semaphore);
		sem_close(table->sem_lifetime[count]);
		free(semaphore);
		count++;
	}
}
