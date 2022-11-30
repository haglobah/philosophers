/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:39:19 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/11/30 12:41:50 by bhagenlo         ###   ########.fr       */
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

void	printp(t_time start, t_phi *p, char *s)
{
	pthread_mutex_lock(p->write);
	printf("%lli %i %s\n", get_µs(start) / 1000, p->id, s);
	fflush(stdout);
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

void	acquire_forks(t_phi *p, t_time start)
{
	int	left;
	int	right;

	left = p->id;
	right = (p->id == 0) ? p->n.philos - 1 : p->id - 1;
	lock(p, right);
	printp(start, p, "has taken a fork");
	lock(p, left);
	printp(start, p, "has taken a fork");
}

int	transition(t_phi *p, int *state, t_time start, int curr_slot)
{
	if (*state == EATING)
	{
		place_forks(p);
		*state = SLEEPING;
		printp(start, p, "is sleeping");
	}
	else if (*state == SLEEPING)
	{
		*state = THINKING;
		printp(start, p, "is thinking");
	}
	else if (*state == THINKING)
	{
		acquire_forks(p, start);
		*state = EATING;
		printp(start, p, "is eating");
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

bool	switch_needed(t_phi *p, t_time last_switch, t_time start, int curr_slot)
{
	t_time	tasklen;

	tasklen = get_tasklen(p, curr_slot);
	if (get_µs(start) - last_switch >= tasklen)
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

bool	times_ate_reached(t_phi *p, t_time start, int times_ate)
{
	if (!(times_ate == p->n.times_must_eat))
		return (false);
	printp(start, p, "ate times:");
	printf("   %i\n", times_ate);
	return (true);
}

bool	check_death(t_phi *p, t_time start, t_time ate_last_time)
{
	if (get_µs(start) - ate_last_time >= p->n.time_to_die * 1000)
		return (true);
	return (false);
}

void	go(t_phi *p)
{
	t_time	start;
	int	state;
	int	curr_slot;
	int	times_ate;
	t_time	last_switch;
	t_time	ate_last_time;

	start = get_ts();
	state = get_status(p, 2);
	curr_slot = transition(p, &state, start, 2);
	last_switch = 0;
	ate_last_time = 0;
	times_ate = 0;
	while (true)
	{
		if (check_death(p, start, ate_last_time))
			return (printp(start, p, "died"));
		if (switch_needed(p, last_switch, start, curr_slot))
		{
			curr_slot = transition(p, &state, start, curr_slot);
			last_switch = get_µs(start);
			if (state == SLEEPING)
			{
				times_ate++;
				ate_last_time = get_µs(start);
			}
			//sleep_until_next_switch(p, state, curr_slot);
			/* printp(ate_last_time, p, "ate_last_time"); */
		}
		//usleep(1);
		//busy_sleep?
		if (times_ate_reached(p, start, times_ate))
			return ;
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
