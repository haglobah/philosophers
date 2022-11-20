/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heil...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:39:19 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/11/17 11:39:19 by bhagenlo         ###   ########.fr       */
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

void	printp(t_time now, t_phi *p, char *s)
{
	printf("%lli %i %s\n", now / 1000, p->id, s);
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

void	acquire_forks(t_phi *p)
{
	int	left;
	int	right;

	left = p->id;
	right = (p->id == 0) ? p->n.philos - 1 : p->id - 1;
	lock(p, right);
	lock(p, left);
}

int	transition(t_phi *p, int *state, t_time time_passed, int curr_slot)
{
	if (*state == EATING)
	{
		place_forks(p);
		*state = SLEEPING;
		printp(time_passed, p, "is sleeping");
	}
	else if (*state == SLEEPING)
	{
		*state = THINKING;
		printp(time_passed, p, "is thinking");
	}
	else if (*state == THINKING)
	{
		acquire_forks(p);
		*state = EATING;
		printp(time_passed, p, "is eating");
	}
	return (curr_slot < 2 ? curr_slot + 1 : 0);
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

bool	switch_needed(t_phi *p, t_time last_switch, t_time time_passed, int curr_slot)
{
	t_time	tasklen;

	tasklen = get_tasklen(p, curr_slot);
	if (time_passed - last_switch >= tasklen)
		return (true);
	else
		return (false);
}

bool	times_ate_reached();

bool	check_death(t_phi *p, t_time time_passed, t_time ate_last_time)
{
	if (time_passed - ate_last_time >= p->n.time_to_die * 1000)
		return (true);
	return (false);
}

void	go(t_phi *p)
{
	t_time	start;
	int	state;
	int	curr_slot;
	t_time	time_passed;
	t_time	last_switch;
	t_time	ate_last_time;

	start = get_ts();
	state = get_status(p, 2);
	curr_slot = transition(p, &state, 0, 2);
	last_switch = 0;
	ate_last_time = 0;
	while (true)
	{
		time_passed = get_ts() - start;
		if (check_death(p, time_passed, ate_last_time))
			return (printp(time_passed, p, "has died"));
		if (switch_needed(p, last_switch, time_passed, curr_slot))
		{
			curr_slot = transition(p, &state, time_passed, curr_slot);
			last_switch = get_ts() - start;
			if (state == SLEEPING)
				ate_last_time = get_ts() - start;
			/* printp(ate_last_time, p, "ate_last_time"); */
		}
		//busy_sleep?
		/* if (times_ate_reached()) */
		/* { */
			
		/* 	return ; */
		/* } */
	}
	return ;
}

void	*run_philos(t_phi *p)
{
	pthread_t	*t;
	int	i;

	t = malloc(sizeof(pthread_t) * p->n.philos);
	if (t == NULL)
		return (rerror("thread_arr creation failed.\n"));
	i = -1;
	while (++i < p->n.philos)
	{
		if (pthread_create(&t[i], NULL, (void *)go, &p[i]) != 0)
			return (rerror("thread creation failed.\n"));
	}
	while (--i > 0)
	{
		if (pthread_join(t[i], NULL) != 0)
			return (rerror("thread join failed"));
	}
	free(t);
	return (NULL);
}
