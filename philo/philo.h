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
	int	ms;
	char	*status;
}	t_time_status;

typedef struct s_philorow
{
	t_time_status	*ts;
}	t_philorow;

typedef struct s_timetable
{
	t_philorow	*philorow;
}	t_tt;

typedef struct s_philosopher_init_data
{
	int	id;
	t_tt	*t;
} t_pdata;

typedef struct s_philo_struct
{
	t_pdata	*phi;
	pthread_mutex_t	*forks;
	t_tt	*timetable;
	t_args	n;
}	t_phi;

t_phi	*mk_phi(t_args n);
void	del_phi(t_phi *p);

t_phi	*parse(int argc, char *argv[]);
bool	parse_num3(const char *s, int *loc, bool is_num_philos);
bool	parse_num2(const char *s, int *loc);
bool	ft_parse_int(const char *s, int *loc);
void	*rerror(char *msg);

int	ft_strlen(char *s);
void	run_tests(void);

#endif
