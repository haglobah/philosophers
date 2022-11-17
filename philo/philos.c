/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heil...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 23:54:44 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/11/16 23:54:44 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*free_n_destroy(t_phi *p, int died_while, int i)
{
	if (died_while == FORKS)
	{
		
	}
	else if (died_while == PHILOS)
	{
		
	}
	else if (died_while == TIMETABLE)
	{
		
	}
	else
	{
		
	}
	return (rerror("Allocation of philo failed"));
}

t_pdata	*mk_philo(t_phi *p, int id)
{
	t_pdata	*phi;

	phi = malloc(sizeof(t_pdata) * 1);
	if (phi == NULL)
		return (NULL);
	phi->id = id;
	phi->ts = p->timetable;
	phi->forks = p->forks;
	return (phi);
}

t_pdata	**mk_philos(t_phi *p, t_args n)
{
	t_pdata	**philos;
	int	i;

	i = -1;
	philos = malloc(sizeof(t_pdata *) * n.philos);
	if (philos == NULL)
		return (rerror("Allocation of philos failed."));
	while (++i < n.philos)
	{
		philos[i] = mk_philo(p, i);
		printf("i: %i, id: %i\n", i, philos[i]->id);
		if (philos[i] == NULL)
			return (free_n_destroy(p, PHILOS, i));
	}
	return (philos);
}

pthread_mutex_t	*mk_forks(t_phi *p, t_args n)
{
	pthread_mutex_t	*forks;
	int	i;

	i = -1;
	forks = malloc(sizeof(pthread_mutex_t) * n.philos);
	if (forks == NULL)
		return (rerror("Allocation of forks failed."));
	while (++i < n.philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (free_n_destroy(p, FORKS, i));
	}
	return (forks);
}

void	populate_even(t_phi *p, t_args n)
{
	p->timetable[0][0] = (t_ts){n.time_to_eat, EATING};
	p->timetable[0][1] = (t_ts){n.time_to_sleep, SLEEPING};
	p->timetable[0][2] = (t_ts){1, THINKING};
	p->timetable[1][0] = (t_ts){n.time_to_sleep, SLEEPING};
	p->timetable[1][1] = (t_ts){1, THINKING};
	p->timetable[1][2] = (t_ts){n.time_to_eat, EATING};
}

void	populate_odd(t_phi *p, t_args n)
{
	p->timetable[0][0] = (t_ts){n.time_to_eat, EATING};
	p->timetable[0][1] = (t_ts){n.time_to_sleep, SLEEPING};
	p->timetable[0][2] = (t_ts){1, THINKING};
	p->timetable[1][0] = (t_ts){n.time_to_sleep, SLEEPING};
	p->timetable[1][1] = (t_ts){1, THINKING};
	p->timetable[1][2] = (t_ts){n.time_to_eat, EATING};
	p->timetable[2][0] = (t_ts){1, THINKING};
	p->timetable[2][1] = (t_ts){n.time_to_eat, EATING};
	p->timetable[2][2] = (t_ts){n.time_to_sleep, SLEEPING};
}

int	get_dur(t_phi *p, int philo, int slot)
{
	return (p->timetable[philo][slot].dur);
}

int	get_st(t_phi *p, int philo, int slot)
{
	return (p->timetable[philo][slot].status);
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

void	populate_timetable(t_phi *p, t_args n)
{

	if ((n.philos % 2) == 0)
		populate_even(p, n);
	else
		populate_odd(p, n);
	print_tt(p);
}

t_phi	*mk_phi(t_args n)
{
	t_phi	*p;
	int	i;

	p->forks = mk_forks(p, n);
	populate_timetable(p, n);
	p->phi = mk_philos(p, n);
	p->n = n;
	return (p);
}

void	print_philos(t_phi *p)
{
	int	i;

	i = -1;
	while (++i < p->n.philos)
	{
		printf("Philo %i is there.\n", p->phi[i]->id);
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

	return (mk_phi(n));
}

