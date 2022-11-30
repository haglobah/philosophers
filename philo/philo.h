/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 17:16:04 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/11/30 20:46:12 by bhagenlo         ###   ########.fr       */
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

# define TIMES_ATE_REACHED 10

typedef struct timeval	t_tv;
typedef long long		t_time;
typedef pthread_mutex_t	t_mutex;

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
	int		status;
}	t_ts;

typedef struct s_philo_state
{
	t_time	start;
	t_time	last_switch;
	t_time	ate_last_time;
	int		state;
	int		curr_slot;
	int		times_ate;
	bool	died;
}	t_ps;

typedef struct s_global_stuff
{
	t_mutex	*forks;
	t_mutex	*write;
	t_mutex	*death;
	bool	*has_died;
}	t_glob;

typedef struct s_philo_struct
{
	int		id;
	t_glob	*g;
	t_mutex	*forks;
	t_mutex	*write;
	t_mutex	*death;
	bool	*has_died;
	t_ts	tt[3][3];
	t_args	n;
}	t_phi;

t_phi	*mk_phis(t_args n);
void	del_phis(t_phi *p);
t_mutex	*mk_forks(t_phi *p, t_args n);
int		get_dur(t_phi *p, int philo, int slot);
int		get_st(t_phi *p, int philo, int slot);

//parse.c
t_phi	*parse(int argc, char *argv[]);
bool	parse_num3(const char *s, int *loc, bool is_num_philos);
bool	parse_num2(const char *s, int *loc);
bool	ft_parse_int(const char *s, int *loc);

//error.c
void	*rerror(char *msg);
void	*rerrorm(char *msg);

void	*run_philos(t_phi *p);
void	print_philos(t_phi *p);

//go_helpers.c
int		get_idm(t_phi *p);
int		get_status(t_phi *p, int slot);
t_time	get_tasklen(t_phi *p, int slot);
bool	switch_needed(t_phi *p, t_ps *ps);
bool	times_ate_reached(t_phi *p, t_ps *ps);

//death.c
bool	is_sb_dead(t_phi *p);
void	printp(t_phi *p, t_ps *ps, char *s);
void	announce_death(t_phi *p, t_ps *ps);
bool	should_die(t_phi *p, t_ps *ps);
int		handle_death(t_phi *p, t_ps ps);

//forks.c
void	place_forks(t_phi *p);
void	acquire_forks(t_phi *p, t_ps *ps);

//time.c
t_time	utc(t_tv time);
t_time	get_ts(void);
t_time	get_us(t_time start);

//timetable.c
void	populate_even(t_phi *p, t_args n);
void	populate_odd(t_phi *p, t_args n);
void	print_tt(t_phi *p);
void	populate_tt(t_phi *p, t_args n);

//tt_helpers.c
int		get_dur(t_phi *p, int philo, int slot);
int		get_st(t_phi *p, int philo, int slot);
int		get_thinktime(t_args n);

//utils.c
int		ft_strlen(char *s);
void	run_tests(void);
void	*ft_calloc(int count, int size);

#endif
