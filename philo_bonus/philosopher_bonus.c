/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:38:08 by sharnvon          #+#    #+#             */
/*   Updated: 2022/09/06 22:33:45 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

// /* ./philo [number of philos] [time to die] [time to eat] [time to sleep] */
// 	/* optional "number of time to eat" */
// void	ft_check_arguments(int argc, char **argv)
// {
// 	int	index;
// 	int	xedni;

// 	index = 1;
// 	if (argc < 5 || argc > 6)
// 	{
// 		printf("ERROR: THE NUMBER OF THE AGUMENT IS WRONG :(\n");
// 		printf(" (hint) ./philo [number of philos] [time to die] [time to eat]"
// 			" [time to sleep] [(optional): number of time to eat]\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	while (argv[index] != NULL)
// 	{
// 		xedni = 0;
// 		while (argv[index][xedni] != '\0')
// 		{
// 			if (argv[index][xedni] < '0' || argv[index][xedni] > '9')
// 			{
// 				printf("ERROR: VALUE OF AGURMENTS MUST BE POSITIVE NUMBER..\n");
// 				exit(EXIT_FAILURE);
// 			}
// 			xedni++;
// 		}
// 		index++;
// 	}
// }

// t_table	*ft_allocate_data(t_table *table, char **argv)
// {
// 	table = (t_table *)ft_calloc(sizeof(t_table), 1);
// 	if (table == NULL)
// 		return (0);
// 	table->amount = ft_atoi(argv[1]);
// 	table->pid = (int *)ft_calloc(sizeof(int), table->amount);
// 	if (table->pid == NULL)
// 	{
// 		free(table);
// 		return (0);
// 	}
// 	table->sem_lifetime = (sem_t **)ft_calloc(sizeof(sem_t *), table->amount);
// 	if (table->sem_lifetime == NULL)
// 	{
// 		free(table->pid);
// 		free(table);
// 		return (0);
// 	}
// 	table->eat = ft_atoi(argv[3]) * 1000;
// 	table->sleep = ft_atoi(argv[4]) * 1000;
// 	table->life_time = ft_atoi(argv[2]) * 1000;
// 	table->philo_status = SLEEP;
// 	table->life = ft_atoi(argv[2]) * 1000;
// 	table->max_meal = -1;
// 	return (table);
// }

/* function initialise the t_table structure */
t_table	*ft_table_init(t_table *table, char **argv, int i)
{
	char	*sem_life;

	table = ft_allocate_data(table, argv);
	if (table == NULL)
		return (0);
	if (argv[5] != NULL)
		table->max_meal = ft_atoi(argv[5]);
	sem_unlink(SEMDEAD);
	table->sem_dead = sem_open(SEMDEAD, O_CREAT | O_EXCL, 0644, 1);
	sem_unlink(SEMFORK);
	table->sem_fork = sem_open(SEMFORK, O_CREAT | O_EXCL, 0644, table->amount);
	sem_unlink(SEPRINT);
	table->sem_print = sem_open(SEPRINT, O_CREAT | O_EXCL, 0644, table->amount);
	while (i < table->amount)
	{
		sem_life = ft_strjoin(SEMLIFE, ft_positive_itoa(i));
		sem_unlink(sem_life);
		table->sem_lifetime[i] = sem_open(sem_life, O_CREAT | O_EXCL, 0644, 1);
		free(sem_life);
		i++;
	}
	return (table);
}

void	ft_philo_routine(t_table *table)
{
	while (table->philo_status == SLEEP)
	{
	}
	if (table->count > table->amount / 2)
		ft_isleepnow(table->eat);
	while (table->philo_status != DEAD)
	{
		sem_wait(table->sem_fork);
		ft_philo_printf(table, table->count + 1, FORK_TAKEN);
		sem_wait(table->sem_fork);
		ft_philo_printf(table, table->count + 1, FORK_TAKEN);
		ft_philo_printf(table, table->count + 1, EAT);
		ft_isleepnow(table->eat);
		sem_wait(table->sem_lifetime[table->count]);
		table->life = table->life_time;
		sem_post(table->sem_lifetime[table->count]);
		table->meal++;
		sem_post(table->sem_fork);
		sem_post(table->sem_fork);
		if (table->max_meal != -1 && table->meal >= table->max_meal)
			break ;
		ft_philo_printf(table, table->count + 1, SLEEP);
		ft_isleepnow(table->sleep);
		ft_philo_printf(table, table->count + 1, THINK);
	}
}

int	ft_create_philosopher(t_table *table)
{
	int	count;

	count = 0;
	while (count < table->amount)
	{
		table->pid[count] = fork();
		if (table->pid[count] < 0)
		{
			while (count >= 0)
				kill(table->pid[count--], SIGINT);
			ft_free_resource(table, FAILURE);
		}
		if (table->pid[count] == 0)
			break ;
		count++;
	}
	return (count);
}

void	ft_waiting_child(t_table *table, int count)
{
	int	status;
	int	meal;

	meal = 0;
	while (waitpid(-1, &status, 0) != -1 || errno != ECHILD)
	{
		if (WEXITSTATUS(status) == 1)
		{
			while (--count >= 0)
				kill(table->pid[count], SIGINT);
		}
		else if (WEXITSTATUS(status) == 0)
			meal++;
	}
	if (meal == table->amount)
		printf("=> \033[0;36mall philosophers are full :)\nnumber"
			" of times_to_eat is reached...\033[0m\n");
	ft_free_resource(table, SUCCESS);
}

/* ./philo [number of philos] [time to die] [time to eat] [time to sleep] */
	/* optional "number of time to eat" */
int	main(int argc, char **argv)
{
	t_table		*table;
	int			count;

	ft_check_arguments(argc, argv);
	table = ft_table_init(NULL, argv, 0);
	if (table == NULL)
		return (EXIT_FAILURE);
	count = ft_create_philosopher(table);
	if (count < table->amount && table->pid[count] == 0)
	{
		pthread_create(&table->thread, NULL, &ft_philo_lifetime, (void *)table);
		pthread_detach(table->thread);
		table->count = count;
		ft_philo_routine(table);
	}
	else
	{
		ft_waiting_child(table, count);
	}
	return (EXIT_SUCCESS);
}
