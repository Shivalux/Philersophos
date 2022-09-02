/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:38:08 by sharnvon          #+#    #+#             */
/*   Updated: 2022/09/03 01:00:17 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void				*ft_philo_routine(void *table);
unsigned long int	ft_timestamp_cal(t_table *table, int mode);
void				ft_isleepnow(t_table *table, int behave);

/* ./philo [number of philos] [time to die] [time to eat] [time to sleep] */
	/* optional "number of time to eat" */
void	ft_check_arguments(int argc, char **argv)
{
	int	index;
	int	xedni;

	index = 1;
	if (argc < 5 || argc > 6)
	{
		printf("THE NUMBER OF THE AGUMENT IS WRONG :(\n");
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
				printf("THE VALUE OF AGURMENTS MUST BE A POSITIVE NUMBER..\n");
				exit(EXIT_FAILURE);
			}
			xedni++;
			// check_argument_over or less than int //
		}
		index++;
	}
}

int	ft_free_resource(t_table *table, int mode)
{
	int	count;

	count = 0;
	while (count < table->amount)
	{
		pthread_detach(table->philo[count].thread);
		pthread_mutex_destroy(&table->philo[count++].mutex);
	}
	pthread_mutex_destroy(&table->mutex_lifetime);
	pthread_detach(table->thread);
	free(table->philo);
	free(table);
	if (mode == FAILURE)
		exit(EXIT_FAILURE);
	return (0);
}
/* function initialise the t_table structure */
t_table *ft_table_init(t_table *table, char **argv, int index)
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
	table->philo_status = ALIVE;
	pthread_mutex_init(&table->mutex_lifetime, NULL);
	if (argv[5] != NULL)
		table->meal = ft_atoi(argv[5]);
	else
		table->meal = -1;
	while (index < table->amount)
	{
		pthread_mutex_init(&table->philo[index].mutex, NULL);
		table->philo[index].life = ft_atoi(argv[2]) * 1000;
		index++;
	}
	return (table);
}

void	*ft_philo_lifetime(void *elbat)
{
	t_table		*table;
	int			index;

	table = (t_table *)elbat;
	ft_timestamp_cal(table, TIME_REGIS);
	while (0 < 1)
	{
		ft_isleepnow(table, 1000);
		index = 0;
		while (index < table->amount)
		{
			pthread_mutex_lock(&table->mutex_lifetime);
			table->philo[index].life -= 1000;
			pthread_mutex_unlock(&table->mutex_lifetime);
			if (table->philo[index].life <= 0)
			{
				table->philo_status = DEAD;
				ft_philo_printf(table, index + 1, DEAD);
				return (0);
			}
			if (table->philo_status == FULL)
				return (0);
			index++;
		}
	}
	return (0);
}
/*
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
		if (ft_timestamp_cal(&time, 3) >= behave)
			break ;
	}
}*/
void	*ft_philo_mealcount(void *elbta)
{
	int		count;
	int		index;
	t_table	*table;

	table = (t_table *)elbta;
	count = 0;
	while (count != table->amount)
	{
		index = 0;
		count = 0;
		while (index < table->amount)
		{
			if (table->philo[index].meal == table->meal)
				count++;
			index++;
		}
	}
	table->philo_status = FULL;
	printf("=> \033[0;33m%lu\033[0m ms, \033[0;36mall philosopher is full\033[0m\n", ft_timestamp_cal(table, TIME_CAL));
	return (0);
}

void	ft_isleepnow(t_table *table, int behave)
{
	t_table			time;

	ft_timestamp_cal(&time, TIME_REGIS);
	while (1 > 0)
	{
		if (ft_timestamp_cal(&time, TIME_CAL) >= behave / 1000)
			break ;
	}
}

int		ft_get_index(t_table *table)
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
	while (table->timestamp_init == NO)
	{
	}
	return (index);
}

void	*ft_philo_routine(void *elbat)
{
	t_table		*table;
	int			index;

	table = (t_table *)elbat;
	index = ft_get_index(table);
	printf("\033[1;33mindex = %d\033[0m\n", index);
	while (1 > 0)
	{	
		pthread_mutex_lock(&table->philo[index].mutex);
		if (table->philo_status == ALIVE)
			ft_philo_printf(table, index + 1, FORK_TAKEN);
		pthread_mutex_lock(&table->philo[(index + 1) % table->amount].mutex);
		if (table->philo_status == ALIVE)
			ft_philo_printf(table, index + 1, FORK_TAKEN);
		if (table->philo_status == ALIVE)
			ft_philo_printf(table, index + 1, EAT);
		ft_isleepnow(table, table->eat);
		table->philo[index].meal++;
		pthread_mutex_lock(&table->mutex_lifetime);
		table->philo[index].life = table->life_time;
		pthread_mutex_unlock(&table->mutex_lifetime);
		pthread_mutex_unlock(&table->philo[index].mutex);
		pthread_mutex_unlock(&table->philo[(index + 1) % table->amount].mutex);
		if (table->philo_status == ALIVE)
			ft_philo_printf(table, index + 1, SLEEP);
		ft_isleepnow(table, table->sleep);
		if (table->philo_status == ALIVE)
			ft_philo_printf(table, index + 1, THINK);
	}
}

/* function print behavious of philosopher */
/* following the behaveious form mode */
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
	else
	{
		printf("=> \033[0;33m%lu\033[0m ms, \033[0;36m%d\033[0m \033[0;31mdied."
			"\033[0m\n", ft_timestamp_cal(table, TIME_CAL), index);
	}
}

/* function about init timestamp & calulate in millisec */
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
		table->timestamp_init = YES;
		return (0);
	}
	else if (mode == TIME_CAL)
	{
		gettimeofday(&time, NULL);
		result = ((time.tv_sec - table->sec) * 1000) + ((time.tv_usec / 1000) - (table->micro / 1000));
		return (result);
	}
	return (-1);
}

void	ft_create_philo(t_table *table, int amount, int count)
{
	while (count + 1 < amount)
	{
		printf("count = %d\n",count);
		if (pthread_create(&table->philo[count].thread, NULL, &ft_philo_routine, (void *)table) != 0)
			ft_free_resource(table, FAILURE);
		if (count + 2 != table->amount)
			count += 2;
		else
			count++;
	}
}

/* ./philo [number of philos] [time to die] [time to eat] [time to sleep] */
	/* optional "number of time to eat" */
int	main(int argc, char **argv)
{
	t_table		*table;
	pthread_t	thread;
// fix //
	ft_check_arguments(argc, argv);
	table = ft_table_init(table, argv, 0);
	if (table == NULL)
		return (0);
	if (argv[5] != NULL)
	{
		if (pthread_create(&table->thread, NULL, &ft_philo_mealcount, (void *)table) < 0)
			ft_free_resource(table, FAILURE);
	}
	//thread create//
	ft_create_philo(table, table->amount, 0);
	// time register and lifetime count//
	printf("first_end\n");
	if (pthread_create(&thread, NULL, &ft_philo_lifetime, (void *)table) != 0)
		ft_free_resource(table, FAILURE);
	// wait time register//
	while (table->timestamp_init == NO)
	{
	}

	//thread create//
	printf("go\n");
	ft_isleepnow(table, table->eat);
	ft_create_philo(table, table->amount + 1,  1);
	if (pthread_join(thread, NULL) != 0)
		ft_free_resource(table, FAILURE);
	ft_free_resource(table, SUCCESS);
	return (EXIT_SUCCESS);
}
