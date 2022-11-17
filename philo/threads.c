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

long long	µs_difference(t_tv start, t_tv now)
{
	return (( now.tv_sec - start.tv_sec) * 1e6
			+ now.tv_usec - start.tv_usec);
}

void	transition(t_pdata *d, int *state, int time_passed)
{
	if (*state == EATING)
	{
		//unlock_forks(p);
		*state = SLEEPING;
		printf("%i %i is sleeping", time_passed, d->id);
	}
	else if (*state == SLEEPING)
	{
		*state = THINKING;
		printf("%i %i is thinking", time_passed, d->id);
	}
	else if (*state == THINKING)
	{
		//acquire_forks(p);
		*state = EATING;
		printf("%i %i is eating", time_passed, d->id);
	}
}

void	go(t_pdata *d)
{
	printf("Hi! I am Philo %i\n", d->id);

	t_tv	start;
	t_tv	now;
	int	state;

	gettimeofday(&start, NULL);
	state = get_st(d->ts);
	while (true)
	{
		gettimeofday(&now, NULL);
		time_passed = µs_difference(start, now);
		if (is_time(time_passed, timetable))
			transition(d, &state, time_passed);
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
		if (pthread_create(&t[i], NULL, go, p->phi[i]) != 0)
			return (rerror("thread creation failed.\n"));
	}
	while (--i > 0)
	{
		if (pthread_join(t[i], NULL) != 0)
			return (rerror("thread join failed"));
	}
	free(t);
	return ;
}
