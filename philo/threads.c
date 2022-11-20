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

int	transition(t_phi *p, int *state, int time_passed, int curr_slot)
{
	if (*state == EATING)
	{
		//unlock_forks(p);
		*state = SLEEPING;
		printf("%i %i is sleeping\n", time_passed / 1000, p->id);
	}
	else if (*state == SLEEPING)
	{
		*state = THINKING;
		printf("%i %i is thinking\n", time_passed / 1000, p->id);
	}
	else if (*state == THINKING)
	{
		//acquire_forks(p);
		*state = EATING;
		printf("%i %i is eating\n", time_passed / 1000, p->id);
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

void	go(t_phi *p)
{
	t_time	start;
	int	state;
	int	curr_slot;
	t_time	time_passed;
	t_time	last_switch;

	start = get_ts();
	state = get_status(p, 2);
	curr_slot = transition(p, &state, 0, 2);
	last_switch = 0;
	while (true)
	{
		time_passed = get_ts() - start;
		if (switch_needed(p, last_switch, time_passed, curr_slot))
		{
			curr_slot = transition(p, &state, time_passed, curr_slot);
			last_switch = get_ts() - start;
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
