/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:39:19 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/11/30 20:36:32 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	transition(t_phi *p, t_ps *ps)
{
	if (ps->state == EATING)
	{
		place_forks(p);
		ps->state = SLEEPING;
		printp(p, ps, "is sleeping");
	}
	else if (ps->state == SLEEPING)
	{
		ps->state = THINKING;
		printp(p, ps, "is thinking");
	}
	else if (ps->state == THINKING)
	{
		acquire_forks(p, ps);
		ps->state = EATING;
		if (should_die(p, ps))
		{
			handle_death(p, *ps);
			return (true);
		}
		printp(p, ps, "is eating");
	}
	ps->curr_slot = (ps->curr_slot < 2) * (ps->curr_slot + 1);
	return (false);
}

int	go(t_phi *p)
{
	t_ps	ps;

	ps = (t_ps){.start = get_ts(), 0, 0,
		.state = get_status(p, 2), .curr_slot = 2, 0, false};
	ps.curr_slot = transition(p, &ps);
	while (true)
	{
		if (should_die(p, &ps))
			return (handle_death(p, ps));
		if (switch_needed(p, &ps))
		{
			ps.died = transition(p, &ps);
			if (ps.died)
				return (1);
			ps.last_switch = get_us(ps.start);
			if (ps.state == SLEEPING)
			{
				ps.times_ate++;
				ps.ate_last_time = get_us(ps.start);
			}
		}
		if (times_ate_reached(p, &ps))
			return (0);
	}
	return (0);
}

void	*run_philos(t_phi *p)
{
	pthread_t	*t;
	void		*has_died;
	int			i;

	has_died = NULL;
	t = ft_calloc(p->n.philos, sizeof(pthread_t));
	if (t == NULL)
		return (rerror("thread_arr creation failed.\n"));
	i = -1;
	while (++i < p->n.philos)
	{
		if (pthread_create(&t[i], NULL, (void *)go, &p[i]) != 0)
			return (rerror("thread creation failed.\n"));
	}
	while (--i >= 0)
	{
		if (pthread_join(t[i], &has_died) == 0)
		{
			printf("thread %i joined.\n", i);
			if (((int)(intptr_t)has_died) == true)
				break ;
		}
	}
	free(t);
	return (NULL);
}
