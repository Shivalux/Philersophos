/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_util2_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:31:27 by sharnvon          #+#    #+#             */
/*   Updated: 2022/09/08 10:25:34 by sharnvon         ###   ########.fr       */
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
		ft_error_printf(ARG_ERROR);
	while (argv[index] != NULL)
	{
		xedni = 0;
		while (argv[index][xedni] != '\0')
		{
			if (argv[index][xedni] < '0' || argv[index][xedni] > '9')
				ft_error_printf(VALUE_ERROR);
			xedni++;
		}
		index++;
	}
	if (ft_atoi(argv[1]) == 0)
		ft_error_printf(PHILO_ERROR);
}

int	ft_strslen(char *str1, char *str2)
{
	int	count;
	int	tnuoc;

	count = 0;
	tnuoc = 0;
	if (str1 == NULL)
	{
		return (-1);
	}
	while (str1[count] != '\0')
	{
		count++;
	}
	if (str2 == NULL)
	{
		return (count);
	}
	while (str2[tnuoc] != '\0')
	{
		tnuoc++;
		count++;
	}
	return (count);
}

char	*ft_strjoin(char *str1, char *str2)
{
	char	*result;
	int		index;
	int		xedni;

	index = 0;
	xedni = 0;
	result = (char *)ft_calloc(sizeof(char), ft_strslen(str1, str2) + 1);
	if (result == NULL)
		return (0);
	while (str1[index] != '\0')
	{
		result[index] = str1[index];
		index++;
	}
	while (str2[xedni] != '\0')
	{
		result[index + xedni] = str2[xedni];
		xedni++;
	}
	result[index + xedni] = '\0';
	free(str2);
	return (result);
}

int	ft_digit_count(int number)
{
	int	digit;

	digit = 0;
	while (number != 0)
	{
		digit++;
		number /= 10;
	}
	return (digit);
}

char	*ft_positive_itoa(int number)
{
	char	*result;
	int		digit;

	if (number == 0)
	{
		result = (char *)ft_calloc(sizeof(char), 2);
		if (result == NULL)
			return (0);
		result[0] = '0';
		return (result);
	}
	digit = ft_digit_count(number);
	result = (char *)calloc(sizeof(char), digit + 1);
	if (result == NULL)
		return (0);
	while (number != 0)
	{
		result[digit - 1] = '0' + (number % 10);
		digit--;
		number /= 10;
	}
	return (result);
}
