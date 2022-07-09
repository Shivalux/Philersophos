/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:38:08 by sharnvon          #+#    #+#             */
/*   Updated: 2022/07/09 20:32:55 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void *ft_philo_routine(t_table table);

int	ft_philo_init(t_table *table, char **argv)
{
	int	index;
	//int	amount;

	index = 0;
	//amount = ft_atoi(argv[1]);
	table->philo = (t_philo *)ft_calloc(sizeof(t_philo), ft_atoi(argv[1]));
	if (table->philo == NULL)
		return (0);
	//table->max_meal = ft_atoi(argv[]);
	table->amount = ft_atoi(argv[1]);
	while (index < table->amount)
	{
		if (pthread_create(&table->philo[index].thread, NULL, &ft_philo_routine, table) == 0)
		{
			free(table->philo);
			free(table);
			return(0);
		}
		// register mutex //
		// -->
			
		pthread_mutex_init(&table->philo[index].mutex, NULL);

		// <--
		table->philo[index].life = ft_atoi(argv[2]);
		table->philo[index].status = 1;
		table->philo[index].fork = 1;
		table->philo[index].meal = 0;
		index++;
	}
	return (1);
}

void *ft_philo_routine(t_table table)
{

	return (0);
}

	/* function checking status */
	/* return (1) no philosopher is dead | return (0) someone is dead */
int	ft_check_philo(t_table *table)
{
	int index;

	index = 0;
	while (index < table->amount)
	{
		if (table->philo[index].status == 0)
		{
			printf(" %d is died\n", index);
			return (0);
		}
		index++;
	}
	return (1);
}

/* ./philo [number of philos] [time to die] [time to eat] [time to sleep] */
	/* optional "number of time to eat" */
int	main(int argc, char **argv)
{
/*	t_table	*table;

	table->count = 0;
	if (argc < 5 || argc > 6)
	{
		// printf error and exit the program;
		return (0);
	}
	table = (t_table *)ft_calloc(sizeof(t_philo), 1)
	if (table == NULL)
		return (0);
	if (ft_philo_init(table, argv) == 0)
		return (0);
	while (ft_check_philo(table) != 0 || ft_check)
	{
		pthread_join(table[count % table->amount], NULL);
		table->count++;
	}

	//free section//
	free(table->philo);
	free(table);
*/	
	unsigned long int	time;
	unsigned long int	start;
	struct timeval tv;

	gettimeofday(&tv, NULL);
	printf("time = %d\n", tv.tv_usec);
	return (0);
}
