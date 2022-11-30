/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 20:32:04 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/11/30 20:54:27 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_idm(t_phi *p)
{
	int	mod;

	if (p->n.philos % 2 == 0)
		mod = 2;
	else
		mod = 3;
	return (p->id % mod);
}

int	get_status(t_phi *p, int slot)
{
	int	mod_id;
	int	status;

	mod_id = get_idm(p);
	status = p->tt[mod_id][slot].status;
	return (status);
}

t_time	get_tasklen(t_phi *p, int slot)
{
	return (p->tt[get_idm(p)][slot].dur);
}

bool	switch_needed(t_phi *p, t_ps *ps)
{
	t_time	tasklen;

	tasklen = get_tasklen(p, ps->curr_slot);
	if (get_us(ps->start) - ps->last_switch >= tasklen)
		return (true);
	else
		return (false);
}

bool	times_ate_reached(t_phi *p, t_ps *ps)
{
	if (!(ps->times_ate == p->n.times_must_eat))
		return (false);
	return (true);
}
