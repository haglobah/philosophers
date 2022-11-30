/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:39:19 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/11/30 16:51:39 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_time	utc(t_tv time)
{
	return (time.tv_sec * 1e6 + time.tv_usec);
}

t_time	µs_difference(t_tv start, t_tv now)
{
	return (( now.tv_sec - start.tv_sec) * 1e6
			+ now.tv_usec - start.tv_usec);
}

t_time get_ts()
{
	t_tv	now;

	gettimeofday(&now, NULL);
	return (utc(now));
}

t_time get_µs(t_time start)
{
	return (get_ts() - start);
}

bool	should_die(t_phi *p, t_ps *ps)
{
	if (get_µs(ps->start) - ps->ate_last_time >= p->n.time_to_die * 1000)
		return (true);
	return (false);
}

void	printp(t_phi *p, t_ps *ps, char *s)
{
	pthread_mutex_lock(p->write);
	if (should_die(p, ps))
	{
		printf("%lli %i died\n", get_µs(ps->start) / 1000, p->id);
		// kill_all_processes();
		// pthread_mutex_unlock(p->write);
		return ;
	}
	printf("%lli %i %s\n", get_µs(ps->start) / 1000, p->id, s);
	pthread_mutex_unlock(p->write);
}

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
	right = (p->id == 0) ? p->n.philos - 1 : p->id - 1;
	unlock(p, left);
	unlock(p, right);
}

void	acquire_forks(t_phi *p, t_ps *ps)
{
	int	left;
	int	right;

	left = p->id;
	right = (p->id == 0) ? p->n.philos - 1 : p->id - 1;
	lock(p, right);
	printp(p, ps, "has taken a fork");
	lock(p, left);
	printp(p, ps, "has taken a fork");
}

int	transition(t_phi *p, t_ps *ps)
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
		printp(p, ps, "is eating");
	}
	return (ps->curr_slot < 2 ? ps->curr_slot + 1 : 0);
}

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
	/* printf("mod_id of %i: %i\n", p->id, mod_id); */
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
	if (get_µs(ps->start) - ps->last_switch >= tasklen)
		return (true);
	else
		return (false);
}

void	sleep_until_next_switch(t_phi *p, int state, int curr_slot)
{
	if (p->n.philos % 2 == 0 && state == THINKING)
		return ;
	printf("%u: ", get_dur(p, p->id, curr_slot));
	usleep(get_dur(p, p->id, curr_slot) - 500);
}

bool	times_ate_reached(t_phi *p, t_ps *ps)
{
	if (!(ps->times_ate == p->n.times_must_eat))
		return (false);
	printp(p, ps, "ate times:");
	printf("   %i\n", ps->times_ate);
	return (true);
}

void	go(t_phi *p)
{
	t_ps	ps;

	ps = (t_ps){};
	ps.start = get_ts();
	ps.state = get_status(p, 2);
	ps.curr_slot = 2;
	ps.curr_slot = transition(p, &ps);
	ps.last_switch = 0;
	ps.ate_last_time = 0;
	ps.times_ate = 0;
	while (true)
	{
		if (switch_needed(p, &ps))
		{
			ps.curr_slot = transition(p, &ps);
			ps.last_switch = get_µs(ps.start);
			if (ps.state == SLEEPING)
			{
				ps.times_ate++;
				ps.ate_last_time = get_µs(ps.start);
			}
			//sleep_until_next_switch(p, state, curr_slot);
			/* printp(ate_last_time, p, "ate_last_time"); */
		}
		if (times_ate_reached(p, &ps))
		{
			return ;
		}
	}
	return ;
}

void	*run_philos(t_phi *p)
{
	pthread_t	*t;
	int	i;

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
		if (pthread_join(t[i], NULL) == 0)
			printf("thread %i joined.\n", i);
	}
	free(t);
	return (NULL);
}
