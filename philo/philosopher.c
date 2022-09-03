/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:38:08 by sharnvon          #+#    #+#             */
/*   Updated: 2022/09/03 22:50:15 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/* ./philo [number of philos] [time to die] [time to eat] [time to sleep] */
	/* optional "number of time to eat" */
void	ft_check_arguments(int argc, char **argv)
{
	int	index;
	int	xedni;

	index = 1;
	if (argc < 5 || argc > 6)
	{
		printf("ERROR: THE NUMBER OF THE AGUMENT IS WRONG :(\n");
		printf(" (hint) ./philo [number of philos] [time to die] [time to eat]"
			" [time to sleep] [(optional): number of time to eat]\n");
		exit(EXIT_FAILURE);
	}
	while (argv[index] != NULL)
	{
		xedni = 0;
		while (argv[index][xedni] != '\0')
		{
			if (argv[index][xedni] < '0' || argv[index][xedni] > '9')
			{
				printf("ERROR: VALUE OF AGURMENTS MUST BE POSITIVE NUMBER..\n");
				exit(EXIT_FAILURE);
			}
			xedni++;
		}
		index++;
	}
}

/* function initialise the t_table structure */
t_table	*ft_table_init(t_table *table, char **argv, int index)
{
	table = ft_calloc(sizeof(t_table), 1);
	if (table == NULL)
		return (0);
	table->philo = (t_philo *)ft_calloc(sizeof(t_philo), ft_atoi(argv[1]));
	if (table->philo == NULL)
	{
		free(table);
		return (0);
	}
	table->amount = ft_atoi(argv[1]);
	table->eat = ft_atoi(argv[3]) * 1000;
	table->sleep = ft_atoi(argv[4]) * 1000;
	table->life_time = ft_atoi(argv[2]) * 1000;
	table->philo_status = SLEEP;
	table->meal = -1;
	pthread_mutex_init(&table->mutex_index, NULL);
	if (argv[5] != NULL)
		table->meal = ft_atoi(argv[5]);
	while (index < table->amount)
	{
		pthread_mutex_init(&table->philo[index].mutex_fork, NULL);
		pthread_mutex_init(&table->philo[index].mutex_lifetime, NULL);
		table->philo[index++].life = ft_atoi(argv[2]) * 1000;
	}
	return (table);
}

void	ft_create_philo(t_table *table, int amount, int count)
{
	while (count + 1 < amount)
	{
		if (pthread_create(&table->philo[count].thread, NULL, \
			&ft_philo_routine, (void *)table) != 0)
			ft_free_resource(table, FAILURE);
		if (count + 2 != table->amount)
			count += 2;
		else
			count++;
	}
	if (amount == 1 && count == 0)
	{
		if (pthread_create(&table->philo[count].thread, NULL, \
			&ft_philo_routine, (void *)table) != 0)
			ft_free_resource(table, FAILURE);
	}
}

/* ./philo [number of philos] [time to die] [time to eat] [time to sleep] */
	/* optional "number of time to eat" */
int	main(int argc, char **argv)
{
	t_table		*table;
	pthread_t	thread;

	ft_check_arguments(argc, argv);
	table = ft_table_init(NULL, argv, 0);
	if (table == NULL)
		return (EXIT_FAILURE);
	if (argv[5] != NULL)
	{
		if (pthread_create(&table->thread, NULL, \
			&ft_philo_mealcount, (void *)table) != 0)
			ft_free_resource(table, FAILURE);
	}
	ft_create_philo(table, table->amount, 0);
	if (pthread_create(&thread, NULL, &ft_philo_lifetime, (void *)table) != 0)
		ft_free_resource(table, FAILURE);
	while (table->philo_status == SLEEP)
	{
	}
	ft_isleepnow(table->eat);
	ft_create_philo(table, table->amount + 1, 1);
	if (pthread_join(thread, NULL) != 0)
		ft_free_resource(table, FAILURE);
	ft_free_resource(table, SUCCESS);
	return (EXIT_SUCCESS);
}
