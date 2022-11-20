/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heil...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 17:16:04 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/11/20 17:16:04 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heil...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:25:09 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/11/16 10:25:09 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <limits.h>
# include <stdarg.h>

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define FORKS -10
# define PHILOS -9
# define TIMETABLE -8

# define EATING 3
# define SLEEPING 4
# define THINKING 5

# define EST 6
# define STE 7
# define TES 8

typedef struct timeval	t_tv;
typedef long long t_time;

typedef struct s_arguments
{
	int	philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_must_eat;
}	t_args;

typedef struct s_time_status
{
	t_time	dur;
	int	status;
	/* char	stat[5]; */
}	t_ts;

/* typedef struct s_philorow */
/* { */
/* 	t_time_status	*ts; */
/* }	t_philorow; */

/* typedef struct s_timetable */
/* { */
/* 	t_ts	bla[3]; */
/* }	t_tt; */

typedef struct s_philosopher_init_data
{
	int	id;
	t_ts	**ts;
	pthread_mutex_t	*forks;
	t_args	*n;
} t_pdata;

typedef struct s_philo_struct
{
	int	id;
	pthread_mutex_t	*forks;
	t_ts	timetable[3][3];
	t_args	n;
}	t_phi;

t_phi	*mk_phi(t_args n);
void	del_phi(t_phi *p);
pthread_mutex_t	*mk_forks(t_phi *p, t_args n);
void	populate_even(t_phi *p, t_args n);
void	populate_odd(t_phi *p, t_args n);
int	get_dur(t_phi *p, int philo, int slot);
int	get_st(t_phi *p, int philo, int slot);
void	print_tt(t_phi *p);
void	populate_timetable(t_phi *p, t_args n);

t_phi	*parse(int argc, char *argv[]);
bool	parse_num3(const char *s, int *loc, bool is_num_philos);
bool	parse_num2(const char *s, int *loc);
bool	ft_parse_int(const char *s, int *loc);

void	*rerror(char *msg);
void	*rerrorm(char *msg);

void	*run_philos(t_phi *p);
void	print_philos(t_phi *p);

int	ft_strlen(char *s);
void	run_tests(void);

#endif
