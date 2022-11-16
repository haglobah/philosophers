/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heil...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:26:38 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/11/16 10:26:38 by bhagenlo         ###   ########.fr       */
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
	return (NULL)
}

t_pdata	*mk_philo(t_phi p, int id)
{
	t_pdata	*phi;

	phi = malloc(sizeof(t_pdata) * 1);
	phi->id = id;
	phi->t = p->timetable;
	return (phi);
}

t_pdata	*mk_philos(t_phi p, t_args n)
{
	t_pdata	*philos;
	int	i;

	i = -1;
	philos = malloc(sizeof(t_philo) * n.philos);
	if (philos == NULL)
		return (rerror("Allocation of philos failed."));
	while (++i < n.philo_count)
	{
		philos[i] = mk_philo(p, i);
		if (philos[i] == NULL)
			return (free_n_destroy(p, PHILOS, i));
	}
	return (philos);
}

pthread_mutex_t	*mk_forks(t_args n)
{
	pthread_mutex_t	*forks;
	int	i;

	i = -1;
	forks = malloc(sizeof(pthread_mutex_t) * n.philos);
	if (forks == NULL)
		return (rerror("Allocation of forks failed."));
	while (++i < n.philo_count)
	{
		if (pthread_mutex_init(&forks[i]) != 0)
			return (free_n_destroy(p, FORKS, i));
	}
	return (forks);
}

void	populate_even(t_tt *t, t_args n)
{
	
}

void	populate_odd(t_tt *t, t_args n)
{
	
}

t_tt	*mk_timetable(t_args n)
{
	t_philorows	*pr;

	pr = malloc(sizeof(t_philorow) * n.philos);
	if (pr == NULL)
		return (rerror("timetable failed"));
	if ((n.philos % 2) == 0)
		populate_even(t, n.philos);
	else
		populate_odd(t, n.philos);
}

t_phi	*mk_phi(t_args n)
{
	t_phi	*p;
	int	i;

	p->forks = mk_forks(n);
	p->timetable = mk_timetable(n);
	p->philos = mk_philos(p, n);
	p->n = n;
	return (p);
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
		return (rerror("number_of_philosophers invalid\n"));
	if (parse_num2(argv[2], &n.time_to_die) == false)
		return (rerror("time_to_die invalid"\n));
	if (parse_num2(argv[3], &n.time_to_eat) == false)
		return (rerror("time_to_eat invalid"\n));
	if (parse_num2(argv[4], &n.time_to_sleep) == false)
		return (rerror("time_to_sleep invalid\n"));
	if (argc == 6 && (parse_num2(argv[5], &n.times_must_eat) == false))
		return (rerror("times_must_eat invalid\n"));

	return (mk_phi(n));
}

int	main(int argc, char *argv[])
{
	t_phi	*p;

	p = parse(argc, argv);
	//run_threads(p);
}
