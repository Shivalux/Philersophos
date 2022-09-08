/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 09:03:03 by sharnvon          #+#    #+#             */
/*   Updated: 2022/09/08 10:10:14 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/* helper function from ft_table_innit */
t_table	*ft_allocate_table(t_table *table, char **argv)
{
	table = (t_table *)ft_calloc(sizeof(t_table), 1);
	if (table == NULL)
		return (0);
	table->amount = atoi(argv[1]);
	table->philo = (t_philo *)ft_calloc(sizeof(t_philo), table->amount);
	if (table->philo == NULL)
	{
		free(table);
		return (0);
	}
	return (table);
}

/* helper function form ft_philo_lifetime */
void	ft_philo_is_dead(t_table *table, int index)
{
	int	xedni;

	xedni = 0;
	table->philo_status = DEAD;
	while (xedni < table->amount)
	{
		pthread_mutex_lock(&table->philo[xedni].mutex_print);
		xedni++;
	}
	printf("=> \033[0;33m%lu\033[0m ms, \033[0;36m%d\033[0m \033[0;31mdied."
		"\033[0m\n", ft_timestamp_cal(table, TIME_CAL), index + 1);
}

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
