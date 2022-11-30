/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tt_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 20:40:27 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/11/30 20:41:05 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_dur(t_phi *p, int philo, int slot)
{
	return (p->tt[philo][slot].dur);
}

int	get_st(t_phi *p, int philo, int slot)
{
	return (p->tt[philo][slot].status);
}

int	get_thinktime(t_args n)
{
	int	think_time;
	int	longer;
	int	shorter;

	if (n.time_to_sleep > n.time_to_eat)
	{
		longer = n.time_to_sleep;
		shorter = n.time_to_eat;
	}
	else
	{
		longer = n.time_to_sleep;
		shorter = n.time_to_eat;
	}
	think_time = longer * 2 - shorter;
	return (think_time);
}
