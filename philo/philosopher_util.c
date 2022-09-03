/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:42:24 by sharnvon          #+#    #+#             */
/*   Updated: 2022/09/03 23:40:49 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*ft_calloc(int count, int size)
{
	void	*result;
	int		index;

	result = (void *)malloc(count * size);
	if (result == NULL)
		return (0);
	index = 0;
	while (index < (count * size))
	{
		((char *)result)[index] = '\0';
		index++;
	}
	return (result);
}

unsigned long int	ft_atoi(char *str)
{
	long int	result;
	int			sign;
	int			index;

	result = 0;
	sign = 1;
	index = 0;
	while (str[index] >= '\t' && str[index] <= '\r' && str[index] == ' ')
		index++;
	if (str[index] == '-')
	{
		index += 1;
		sign = -1;
	}
	while (str[index] != '\0' && str[index] >= '0' && str[index] <= '9')
	{
		result = (result * 10) + (str[index] - '0');
		index++;
	}
	return (result * sign);
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
		table->philo_status = ALIVE;
		return (0);
	}
	else if (mode == TIME_CAL)
	{
		gettimeofday(&time, NULL);
		result = ((time.tv_sec - table->sec) * 1000)
			+ ((time.tv_usec / 1000) - (table->micro / 1000));
		return (result);
	}
	return (-1);
}

void	ft_isleepnow(unsigned long int behave)
{
	t_table			time;

	ft_timestamp_cal(&time, TIME_REGIS);
	while (1 > 0)
	{
		if (ft_timestamp_cal(&time, TIME_CAL) >= behave / 1000)
			break ;
	}
}

int	ft_free_resource(t_table *table, int mode)
{
	int	count;
	int	philo_status;

	count = 0;
	philo_status = table->philo_status;
	while (count < table->amount)
	{
		pthread_detach(table->philo[count].thread);
		pthread_mutex_destroy(&table->philo[count].mutex_fork);
		pthread_mutex_destroy(&table->philo[count].mutex_lifetime);
		count++;
	}
	pthread_mutex_destroy(&table->mutex_index);
	pthread_detach(table->thread);
	free(table->philo);
	free(table);
	if (philo_status == FULL)
		printf("=> \033[0;36mall philosophers are full :)\nnumber"
			" of times_to_eat is reached...\033[0m\n");
	if (mode == FAILURE)
		exit(EXIT_FAILURE);
	return (0);
}
