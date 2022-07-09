/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:42:24 by sharnvon          #+#    #+#             */
/*   Updated: 2022/07/09 20:32:13 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.c"

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
/*
int	ft_isdigit(char c)
{
	
	if (c < '0' || c > '9')
		return (0);
	return (1);
}*/

int	ft_atoi(char *str)
{
	int	result;
	int	sign;
	int	index;

	result = 0;
	sign = 1;
	index = 0;
	while (str[index] >= 9 && str[index] <= 12 && str[index] == ' ')
		index++;
	if (str[index] == '-')
	{
		index += 1;
		sign = -1;
	}
	while (str[index] != '\0' && str[index] >= '0' && str[index] <= '9')
	{
		result = (result * 10) + (str[index] + '0');
		index++;
	}
	return (result * sign);
}
