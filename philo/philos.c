/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 23:54:44 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/11/30 19:01:10 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*free_n_destroy(t_phi *p)
{
	del_phis(p);
	return (rerror("Allocation of a fork failed.\n"));
}

pthread_mutex_t	*mk_forks(t_phi *p, t_args n)
{
	pthread_mutex_t	*forks;
	int	i;

	i = -1;
	forks = ft_calloc(n.philos + 1, sizeof(pthread_mutex_t));
	if (forks == NULL)
		return (rerror("Allocation of forks failed."));
	while (++i < n.philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (free_n_destroy(p));
	}
	return (forks);
}

void	populate_even(t_phi *p, t_args n)
{
	p->tt[0][0] = (t_ts){n.time_to_eat * 1e3, EATING};
	p->tt[0][1] = (t_ts){n.time_to_sleep * 1e3, SLEEPING};
	p->tt[0][2] = (t_ts){1, THINKING};

	p->tt[1][0] = (t_ts){n.time_to_sleep * 1e3, SLEEPING};
	p->tt[1][1] = (t_ts){1, THINKING};
	p->tt[1][2] = (t_ts){n.time_to_eat * 1e3, EATING};
}

int	get_thinktime(t_args n)
{
	int	think_time;
	int	longer;
	int	shorter;

	if (n.time_to_sleep > n.time_to_eat)
	{
		longer = n.time_to_sleep;
		shorter = n.time_to_eat;
	}
	else
	{
		longer = n.time_to_sleep;
		shorter = n.time_to_eat;
	}
	think_time = longer * 2 - shorter;
	return (think_time);
}

void	populate_odd(t_phi *p, t_args n)
{
	p->tt[0][0] = (t_ts){n.time_to_eat * 1e3, EATING};
	p->tt[0][1] = (t_ts){n.time_to_sleep * 1e3, SLEEPING};
	p->tt[0][2] = (t_ts){get_thinktime(n) * 1e3, THINKING};

	p->tt[1][0] = (t_ts){n.time_to_sleep * 1e3, SLEEPING};
	p->tt[1][1] = (t_ts){get_thinktime(n) * 1e3, THINKING};
	p->tt[1][2] = (t_ts){n.time_to_eat * 1e3, EATING};

	p->tt[2][0] = (t_ts){get_thinktime(n) * 1e3, THINKING};
	p->tt[2][1] = (t_ts){n.time_to_eat * 1e3, EATING};
	p->tt[2][2] = (t_ts){n.time_to_sleep * 1e3, SLEEPING};
}

int	get_dur(t_phi *p, int philo, int slot)
{
	return (p->tt[philo][slot].dur);
}

int	get_st(t_phi *p, int philo, int slot)
{
	return (p->tt[philo][slot].status);
}

void	print_tt(t_phi *p)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 3)
	{
		printf("Philo %i:\n", i);
		j = -1;
		while (++j < 3)
		{
			printf("  %i for %i\n", get_st(p, i, j), get_dur(p, i, j));
		}
	}
}

void	populate_tt(t_phi *p, t_args n)
{

	if ((n.philos % 2) == 0)
		populate_even(p, n);
	else
		populate_odd(p, n);
}

t_phi	*mk_phis(t_args n)
{
	t_phi	*p;
	t_mutex	*forks;
	t_mutex	*write;
	t_mutex *death;
	bool	*has_died;
	int	i;

	p = ft_calloc(n.philos + 1, sizeof(t_phi));
	if (p == NULL)
		return (NULL);
	forks = mk_forks(p, n);
	if (forks == NULL)
		return (NULL);
	write = ft_calloc(1, sizeof(t_mutex));
	if (write == NULL)
		return (NULL);
	death = ft_calloc(1, sizeof(t_mutex));
	if (death == NULL)
		return (NULL);
	has_died = ft_calloc(1, sizeof(bool));
	if (has_died == NULL)
		return (NULL);
	*has_died = false;
	pthread_mutex_init(write, NULL);
	pthread_mutex_init(death, NULL);
	i = -1;
	while (++i < n.philos)
	{
		p[i].forks = forks;
		p[i].write = write;
		p[i].death = death;
		p[i].has_died = has_died;
		populate_tt(&p[i], n);
		p[i].id = i;
		p[i].n = n;
	}
	print_tt(p);
	return (p);
}

void	del_mutexes(t_phi *p)
{
	int		i;
	t_mutex	*fork;

	i = -1;
	while (++i < p->n.philos)
	{
		fork = &p->forks[i];
		pthread_mutex_destroy(fork);
	}
	free(p->forks);
	pthread_mutex_destroy(p->write);
	free(p->write);
	pthread_mutex_destroy(p->death);
	free(p->death);
	free(p->has_died);
	return ;
}

void	del_phis(t_phi *p)
{
	del_mutexes(p);
	free(p);
	return ;
}

void	print_philos(t_phi *p)
{
	int	i;

	i = 0;
	while (i < p[i].n.philos)
	{
		printf("Philo %i is there.\n", p[i].id);
		i++;
	}
}

t_phi	*parse(int argc, char *argv[])
{
	t_args	n;

	if (argc < 5 || argc > 6)
	{
		printf("Wrong number of args, namely %i ≠ 5 (or 6)\n", argc);
		return (NULL);
	}
	if (parse_num3(argv[1], &n.philos, true) == false)
		return (rerrorm("number_of_philosophers invalid\n"));
	if (parse_num2(argv[2], &n.time_to_die) == false)
		return (rerrorm("time_to_die invalid\n"));
	if (parse_num2(argv[3], &n.time_to_eat) == false)
		return (rerrorm("time_to_eat invalid\n"));
	if (parse_num2(argv[4], &n.time_to_sleep) == false)
		return (rerrorm("time_to_sleep invalid\n"));
	if (argc == 6 && (parse_num2(argv[5], &n.times_must_eat) == false))
		return (rerrorm("times_must_eat invalid\n"));

	return (mk_phis(n));
}

