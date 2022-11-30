/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 20:13:06 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/11/30 20:34:56 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_sb_dead(t_phi *p)
{
	bool	result;

	result = false;
	pthread_mutex_lock(p->death);
	if (*p->has_died)
		result = true;
	pthread_mutex_unlock(p->death);
	return (result);
}

void	printp(t_phi *p, t_ps *ps, char *s)
{
	pthread_mutex_lock(p->write);
	if (!is_sb_dead(p))
	{
		printf("%lli %i %s\n", get_us(ps->start) / 1000, p->id, s);
	}
	pthread_mutex_unlock(p->write);
}

void	announce_death(t_phi *p, t_ps *ps)
{
	pthread_mutex_lock(p->write);
	if (!is_sb_dead(p))
	{
		printf("%lli %i has died\n", get_us(ps->start) / 1000, p->id);
	}
	*p->has_died = true;
	pthread_mutex_unlock(p->write);
}

bool	should_die(t_phi *p, t_ps *ps)
{
	return (is_sb_dead(p)
		|| (get_us(ps->start) - ps->ate_last_time >= p->n.time_to_die * 1000));
}

int	handle_death(t_phi *p, t_ps ps)
{
	announce_death(p, &ps);
	return (1);
}
