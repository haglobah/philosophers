/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 19:11:08 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/11/30 19:14:15 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_time	utc(t_tv time)
{
	return (time.tv_sec * 1e6 + time.tv_usec);
}

t_time	get_ts(void)
{
	t_tv	now;

	gettimeofday(&now, NULL);
	return (utc(now));
}

t_time	get_us(t_time start)
{
	return (get_ts() - start);
}
