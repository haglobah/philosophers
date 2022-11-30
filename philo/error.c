/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 20:44:57 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/11/30 20:45:24 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printe(char *msg)
{
	write(2, msg, ft_strlen(msg));
}

void	*rerror(char *msg)
{
	printe(msg);
	return (NULL);
}

void	*rerrorm(char *msg)
{
	printe(msg);
	printe("The correct usage is: \n");
	printe("    ./philo #philos die_time eat_time sleep_time [#must_eat]\n\n");
	return (NULL);
}
