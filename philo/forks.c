/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 20:15:04 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/11/30 21:05:11 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock(t_phi *p, int fork_id)
{
	pthread_mutex_unlock(&p->forks[fork_id]);
}

void	lock(t_phi *p, int fork_id)
{
	pthread_mutex_lock(&p->forks[fork_id]);
}

void	place_forks(t_phi *p)
{
	int	left;
	int	right;

	left = p->id;
	right = (p->id == 0) * (p->n.philos - 1) + (!(p->id == 0)) * (p->id - 1);
	unlock(p, left);
	unlock(p, right);
}

bool	acquire_forks(t_phi *p, t_ps *ps)
{
	int	left;
	int	right;

	left = p->id;
	right = (p->id == 0) * (p->n.philos - 1) + (!(p->id == 0)) * (p->id - 1);
	lock(p, right);
	printp(p, ps, "has taken a fork");
	if (p->n.philos == 1)
	{
		while (true)
		{
			if (should_die(p, ps))
				return ((bool)handle_death(p, *ps));
		}
	}
	lock(p, left);
	printp(p, ps, "has taken a fork");
	return (false);
}
