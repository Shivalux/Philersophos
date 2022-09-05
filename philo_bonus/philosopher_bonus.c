/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:38:08 by sharnvon          #+#    #+#             */
/*   Updated: 2022/09/06 05:58:03 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

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
	char	*sem_life;

	table = (t_table *)ft_calloc(sizeof(t_table), 1);
	if (table == NULL)
		return (0);
	table->philo = (t_philo *)ft_calloc(sizeof(t_philo), ft_atoi(argv[1]));
	if (table->philo == NULL)
	{
		free(table);
		return (0);
	}
	table->amount = ft_atoi(argv[1]);
	table->pid = (int *)ft_calloc(sizeof(int), table->amount);
	if (table->pid == NULL)
	{
		free(table->philo);
		free(table);
		return (0);
	}
	table->eat = ft_atoi(argv[3]) * 1000;
	table->sleep = ft_atoi(argv[4]) * 1000;
	table->life_time = ft_atoi(argv[2]) * 1000;
	table->philo_status = SLEEP;
	if (argv[5] != NULL)
		table->meal = ft_atoi(argv[5]);
	else
		table->meal = -1;
	sem_unlink(SEMFORK); //
	table->sem_fork = sem_open(SEMFORK, O_CREAT | O_EXCL, 0644, table->amount);
	while (index < table->amount)
	{
	//	pthread_mutex_init(&table->philo[index].mutex_fork, NULL);
	//	pthread_mutex_init(&table->philo[index].mutex_lifetime, NULL);
		sem_life = ft_strjoin(SEMLIFE, ft_positive_itoa(index)); //
		sem_unlink(sem_life); //
		table->philo[index].sem_lifetime = sem_open(sem_life , O_CREAT | O_EXCL, 0644, 1);
		table->philo[index++].life = ft_atoi(argv[2]) * 1000;
		free(sem_life);
	}
	return (table);
}
/*
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
*/
/* ./philo [number of philos] [time to die] [time to eat] [time to sleep] */
	/* optional "number of time to eat" */
int	main(int argc, char **argv)
{
	t_table		*table;
	pthread_t	thread;
	int			count;
//	int			*pid;

	count = 0;
	ft_check_arguments(argc, argv);
	table = ft_table_init(NULL, argv, 0);
	if (table == NULL)
		return (EXIT_FAILURE);

	// malloc pid use for kill the process //
	////////////////////////////////////////
	
	
	// chai mai dai // not working //
	if (argv[5] != NULL)
	{
		if (pthread_create(&table->thread, NULL, &ft_philo_mealcount, (void *)table) != 0)
			ft_free_resource(table, FAILURE);
	}
	/////////////////////////////////////////



	// philo_funtion //
	
	while (count < table->amount)
	{
		table->pid[count] = fork();
		if (table->pid[count] < 0)
		{
			// need to kill another child process //
			while (count >= 0)
				kill(table->pid[count--], SIGINT);
			ft_free_resource(table, FAILURE);
		}
		if (table->pid[count] == 0)
			break ;
		count++;
	}
	if (count < table->amount && table->pid[count] == 0)
	{
		//printf("(child)count = %d\n", count);
		table->count = count;
		pthread_create(&thread, NULL, &ft_philo_lifetime, (void *)table);
		while (table->philo_status == SLEEP);
	//	pthread_create(&table->philo[count].thread, NULL, &ft_philo_routine, (void *)table);
		if (count > table->amount / 2)
			ft_isleepnow(table->eat);
		while (1)//(table->philo_status != DEAD && table->philo_status != FULL)
		{
			sem_wait(table->sem_fork);
			ft_philo_printf(table, count + 1, FORK_TAKEN);
			sem_wait(table->sem_fork);
			ft_philo_printf(table, count + 1, FORK_TAKEN);
			ft_philo_printf(table, count + 1, EAT);
			ft_isleepnow(table->eat);
			sem_wait(table->philo[count].sem_lifetime);
			table->philo[count].life = table->life_time;
			sem_post(table->philo[count].sem_lifetime);
			table->philo[count].meal++;
			sem_post(table->sem_fork);
			sem_post(table->sem_fork);
			ft_philo_printf(table, count + 1, SLEEP);
			ft_isleepnow(table->sleep);
			ft_philo_printf(table, count + 1, THINK);
		}
		pthread_join(thread, NULL);
		printf("(child)count == %d, pid[%d] = %d\n", count, count, table->pid[count]);
	}
	else
	{
		while (waitpid(-1, NULL, 0) != -1 || errno != ECHILD)
		{
			while (--count >= 0)
				kill(table->pid[count], SIGINT);
		}
		printf("(parent):end\n");
		ft_free_resource(table, SUCCESS);
//		while(1);
	//	printf("HI-LOW O_OKAY\n");
	}
//	printf("end\n");
	return (EXIT_SUCCESS);
}
/*
void	*ft_philo_routine(void *elbat)
{
	t_table		*table;
//	static int	number = 0;
//	int			count;

	table = (t_table *)elbat;
	count = number++;
	printf("count = %d\n", count);
	if (count > table->amount / 2)
		ft_isleepnow(table->eat);
	while (table->philo_status != DEAD && table->philo_status != FULL)
	{
		sem_wait(table->sem_fork);
		ft_philo_printf(table, count + 1, FORK_TAKEN);
		sem_wait(table->sem_fork);
		ft_philo_printf(table, count + 1, FORK_TAKEN);
		ft_philo_printf(table, count + 1, EAT);
		ft_isleepnow(table->eat);
		printf("phio[%d].liffe == %lu\n", count, table->philo[count].life);
		sem_wait(table->philo[count].sem_lifetime);
		table->philo[count].life = table->life_time;
		sem_post(table->philo[count].sem_lifetime);
		table->philo[count].meal++;
		sem_post(table->sem_fork);
		sem_post(table->sem_fork);
		ft_philo_printf(table, count + 1, SLEEP);
		ft_isleepnow(table->sleep);
		ft_philo_printf(table, count + 1, THINK);
		printf("phio[%d].life == %lu\n", count, table->philo[count].life);
	}
	return (0);
}*/

// free pid in ft_free_resource //
// 

/*
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
}*/
