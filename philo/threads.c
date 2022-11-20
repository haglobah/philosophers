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
	printf("Unix seconds: %li\n", now.tv_sec);
	return (utc(now));
}

int	transition(t_pdata *d, int *state, int time_passed, int curr_slot)
{
	if (*state == EATING)
	{
		//unlock_forks(p);
		*state = SLEEPING;
		printf("%i %i is sleeping\n", time_passed, d->id);
	}
	else if (*state == SLEEPING)
	{
		*state = THINKING;
		printf("%i %i is thinking\n", time_passed, d->id);
	}
	else if (*state == THINKING)
	{
		//acquire_forks(p);
		*state = EATING;
		printf("%i %i is eating\n", time_passed, d->id);
	}
	return (curr_slot < 2 ? curr_slot + 1 : 0);
}

int	get_idm(t_pdata *d)
{
	int	mod;

	if (d->n->philos % 2 == 0)
		mod = 2;
	else
		mod = 3;
	return (d->id % mod);
}

int	get_status(t_pdata *d, int slot)
{
	int	mod_id;
	int	status;

	mod_id = get_idm(d);
	printf("mod_id of %i: %i\n", d->id, mod_id);
	status = d->ts[mod_id][slot].status;
	return (status);
}

t_time	get_tasklen(t_pdata *d, int slot)
{
	return (d->ts[get_idm(d)][slot].dur);
}

bool	switch_needed(t_pdata *d, t_time last_switch, t_time time_passed, int curr_slot)
{
	t_time	tasklen;

	tasklen = get_tasklen(d, curr_slot);
	if (time_passed - last_switch >= tasklen)
		return (true);
	else
		return (false);
}

bool	times_ate_reached();

void	go(t_pdata *d)
{
	printf("Hi! I am Philo %i\n", d->id);

	t_time	start;
	t_time	curr;
	int	state;
	int	curr_slot;
	t_time	time_passed;
	t_time	last_switch;

	printf("%i e.\n", d->id);
	start = get_ts();
	printf("%i ex.\n", d->id);
	usleep(500);
	state = get_status(d, 0);
	printf("%i exi.\n", d->id);
	curr_slot = 0;
	last_switch = 0;
	while (true)
	{
		curr = get_ts();
		time_passed = curr - start;
		if (switch_needed(d, last_switch, time_passed, curr_slot))
		{
			curr_slot = transition(d, &state, time_passed, curr_slot);
			last_switch = get_ts();
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
		if (pthread_create(&t[i], NULL, (void *)go, p->phi[i]) != 0)
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
