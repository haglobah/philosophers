/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 23:54:44 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/11/30 20:07:07 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_mutex	*mk_forks(t_phi *p, t_args n)
{
	t_mutex	*forks;
	int		i;

	i = -1;
	forks = ft_calloc(n.philos + 1, sizeof(pthread_mutex_t));
	if (forks == NULL)
		return (rerror("Allocation of forks failed."));
	while (++i < n.philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			del_phis(p);
			return (NULL);
		}
	}
	return (forks);
}

t_glob	*alloc_globals(t_phi *p, t_args n)
{
	t_glob	*g;

	g = ft_calloc(1, sizeof(t_glob));
	if (g == NULL)
		return (NULL);
	g->forks = mk_forks(p, n);
	if (g->forks == NULL)
		return (NULL);
	g->write = ft_calloc(1, sizeof(t_mutex));
	if (g->write == NULL)
		return (NULL);
	g->death = ft_calloc(1, sizeof(t_mutex));
	if (g->death == NULL)
		return (NULL);
	g->has_died = ft_calloc(1, sizeof(bool));
	if (g->has_died == NULL)
		return (NULL);
	return (g);
}

void	cons_philo(t_phi *p, t_glob *g, t_args n, int i)
{
	p[i].forks = g->forks;
	p[i].write = g->write;
	p[i].death = g->death;
	p[i].has_died = g->has_died;
	populate_tt(&p[i], n);
	p[i].id = i;
	p[i].n = n;
}

t_phi	*mk_phis(t_args n)
{
	t_phi	*p;
	t_glob	*g;
	int		i;

	p = ft_calloc(n.philos + 1, sizeof(t_phi));
	if (p == NULL)
		return (NULL);
	g = alloc_globals(p, n);
	if (g == NULL)
		return (NULL);
	*g->has_died = false;
	pthread_mutex_init(g->write, NULL);
	pthread_mutex_init(g->death, NULL);
	i = -1;
	while (++i < n.philos)
	{
		cons_philo(p, g, n, i);
	}
	free(g);
	print_tt(p);
	return (p);
}

void	del_phis(t_phi *p)
{
	int		i;

	i = -1;
	while (++i < p->n.philos)
		pthread_mutex_destroy(&p->forks[i]);
	free(p->forks);
	pthread_mutex_destroy(p->write);
	free(p->write);
	pthread_mutex_destroy(p->death);
	free(p->death);
	free(p->has_died);
	free(p);
	return ;
}
