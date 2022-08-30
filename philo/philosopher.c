/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:38:08 by sharnvon          #+#    #+#             */
/*   Updated: 2022/08/31 01:43:23 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void				*ft_philo_routine(void *table);
unsigned long int	ft_timestamp_cal(t_table *table, int mode);
void				ft_milisleep(t_table *table, int behave);

/* ./philo [number of philos] [time to die] [time to eat] [time to sleep] */
	/* optional "number of time to eat" */
int	ft_check_arguments(char **argv)
{
	int	index;
	int	xedni;

	index = 1;
	while (argv[index] != NULL)
	{
		xedni = 0;
		while (argv[index][xedni] != '\0')
		{
			if (argv[index][xedni] < '0' || argv[index][xedni] > '9')
				return (0);
			xedni++;
		}
		// check_argument_over or less than int //
		index++;
	}
	return (42);
}
/* function initialise the t_table structure */
int	ft_table_init(t_table *table, char **argv)
{
	int	index;

	index = 0;
	table->count = 0;
	table->philo = (t_philo *)ft_calloc(sizeof(t_philo), ft_atoi(argv[1]));
	if (table->philo == NULL)
		return (0);
	table->amount = ft_atoi(argv[1]);
	table->eat = ft_atoi(argv[3]) * 1000;
	table->sleep = ft_atoi(argv[4]) * 1000;
	table->life = ft_atoi(argv[2]) * 1000;
	if (argv[5] != NULL)
		table->meal = ft_atoi(argv[5]);
	while (index < table->amount)
	{
		pthread_mutex_init(&table->philo[index].mutex, NULL);
		table->philo[index].index = index;
		table->philo[index].life = ft_atoi(argv[2]) * 1000;
		table->philo[index].fork = 1;	//
//		table->philo[index].meal = 0;	//
//		table->philo[index].status = 1; //
		index++;
	}
	return (42);
}

void	*ft_philo_lifetime(void *elbat)
{
	t_table		*table;
	int			index;

	table = (t_table *)elbat;
	ft_timestamp_cal(table, TIME_REGIS);
//	return (0);
	while (0 < 1)
	{
		ft_milisleep(table, 1000);
		index = 0;
		while (index < table->amount)
		{
			table->philo[index].life -= 1000;
	//		printf("index = %d, life = %d\n", index, table->philo[index].life);
			if (table->philo[index].life <= 0)
			{
				printf("%lu ms, %d died\n", ft_timestamp_cal(table, TIME_CAL), index + 1);
				return (0);
			}
			index++;
		}
	}
}

void	ft_milisleep(t_table *table, int behave)
{
	unsigned long	time_sec;
	unsigned long	time_usec;
	t_table			time;

//	time_usec = table->micro + behave;
//	if (time_usec >= 1000000)
//	{
//		time_sec = table->sec + (time_usec / 1000000);
//		time_usec = time_usec % 1000000;
//	}
//	else
//		time_sec = table->sec;
	ft_timestamp_cal(&time, TIME_REGIS);
//	printf("sec == %lu, %lu | usec == %lu, %lu\n", time_sec, time.sec, time_usec / 1000, time.micro / 1000);
//	printf("usleep => %ld\n", ((time_sec - table->sec) * 1000) + ((time_usec / 1000) - (table->micro / 1000)));
//	unsigned long test =  ((time_sec - time.sec) * 1000000) + ((time_usec) - (time.micro));
//	printf("test = %ld\n", test);
	while (1)
	{
		if (ft_timestamp_cal(&time, TIME_CAL) >= behave / 1000)
			break ;
	}
}

void	*ft_philo_routine(void *elbat)
{
	t_table		*table;
	int			index;
	static int	count = 0;

	table = (t_table *)elbat;
	if (table->reset == 1)
	{
		count = 1;
		table->reset = 0;
	}
	index = count;
	count = count + 2;
	printf("\033[1;33mindex = %d\033[0m\n", index);
	while (table->save == 0)
	{
	}
	while (1 > 0)
	{	
		// eat //
		pthread_mutex_lock(&table->philo[index].mutex);
			printf("%lu ms, %d has taken a fork\n", ft_timestamp_cal(table, TIME_CAL), table->philo[index].index + 1);
		pthread_mutex_lock(&table->philo[(index + 1) % table->amount].mutex);
			printf("%lu ms, %d has taken a fork\n", ft_timestamp_cal(table, TIME_CAL), table->philo[index].index + 1);
//		printf("index: %d => ready\n", index + 1);	
		printf("%lu ms, %d is eating\n", ft_timestamp_cal(table, TIME_CAL), table->philo[index].index + 1);
		ft_milisleep(table, table->eat);
		table->philo[index].life = table->life;
//		usleep(table->eat);
		// checklife point // 
		pthread_mutex_unlock(&table->philo[index].mutex);
		pthread_mutex_unlock(&table->philo[(index + 1) % table->amount].mutex);

		// sleep //
		printf("%lu ms, %d is sleeping\n", ft_timestamp_cal(table, TIME_CAL), table->philo[index].index + 1);
//		usleep(table->sleep);
		ft_milisleep(table, table->sleep);
		// checklife point //

		// think //
		printf("%lu ms, %d is thinking\n", ft_timestamp_cal(table, TIME_CAL), table->philo[index].index + 1);
	}
}

/* function checking status */
/* return (1) no philosopher is dead | return (0) someone is dead */
int	ft_check_philo(t_table *table)
{
	int index;

	index = 0;
	while (index < table->amount)
	{
		if (table->philo[index].life == 0)
		{
			printf(" %d is died\n", index);
			return (0);
		}
		index++;
	}
	return (1);
}

/* function about innit timestamp & calulate in millisec */
/* mode(1)TIME_REGIS init timestamp | mode(2)TIME_CAL return time in millisec*/
unsigned long int	ft_timestamp_cal(t_table *table, int mode)
{
	struct timeval		time;
	unsigned long int	result;

	if (mode == TIME_REGIS)
	{
		gettimeofday(&time, NULL);
		table->sec = time.tv_sec;
		table->micro = time.tv_usec;
		if (table->first_time == 0)
			table->first_time = ft_timestamp_cal(table, TIME_CAL);
		table->save = 1;
		return (0);
	}
	else if (mode == TIME_CAL)
	{
		gettimeofday(&time, NULL);
		result = ((time.tv_sec - table->sec) * 1000) + ((time.tv_usec / 1000) - (table->micro / 1000));
		return (result);
	}
	else if (mode == 3)
	{
		gettimeofday(&time, NULL);
		result = ((time.tv_sec - table->sec) * 1000) + (time.tv_usec - table->micro);
		return (result);

	}
	return (-1);
}

/* ./philo [number of philos] [time to die] [time to eat] [time to sleep] */
	/* optional "number of time to eat" */

//
int	main(int argc, char **argv)
{
	t_table		*table;
	int			count;
	pthread_t	thread;

	count = 0;
	if (argc < 5 || argc > 6 || ft_check_arguments(argv) == 0)
	{
		// printf error and exit the program;
		printf("WRONG AGUMENT :(\n");
		return (EXIT_FAILURE);
	}

	table = (t_table *)ft_calloc(sizeof(t_table), 1);
	if (table == NULL)
		return (EXIT_FAILURE);
	if (ft_table_init(table, argv) == 0)
	{
		free(table);
		return (EXIT_FAILURE);
	}
	while (table->count < table->amount)
	{
		printf("count = %d\n",table->count);
		if (pthread_create(&table->philo[table->count].thread, NULL, &ft_philo_routine, (void *)table) != 0)
		{
			free(table->philo);
			free(table);
			return (EXIT_FAILURE);
		}
		table->count = table->count + 2;
	}
	printf("first_end\n");
	if (pthread_create(&thread, NULL, &ft_philo_lifetime, (void *)table) != 0)
	{
		free(table->philo);
		free(table);
		return (EXIT_FAILURE);
	}
	while (table->save == 0)
	{
	}
	printf("go\n");
	table->reset = 1;
	table->count = 1;
	while (table->count < table->amount)
	{
		if (pthread_create(&table->philo[table->count].thread, NULL, &ft_philo_routine, (void *)table) != 0)
		{
			free(table->philo);
			free(table);
			return (EXIT_FAILURE);
		}
		if (table->count + 1 == table->amount)
			table->count++;
		else
			table->count = table->count + 2;

	}
/*
	// pthread join //
	int index = 0;
	while (index < table->amount)
	{	
		if (pthread_join(table->philo[index++].thread, NULL) != 0)
		{
			free(table->philo);
			free(table);
			return (0);
		}
	}*/
//	while (table->status != DEAD)
//	{
//	}
	if (pthread_join(thread, NULL) != 0)
	{
		free(table->philo);
		free(table);
		return (EXIT_FAILURE);
	}
//	sleep(2);
	//free section//
	count = 0;
	while (count < table->amount)
	{
		pthread_detach(table->philo[count].thread);
		pthread_mutex_destroy(&table->philo[count++].mutex);
	}
	free(table->philo);
	free(table);
	return (EXIT_SUCCESS);
}