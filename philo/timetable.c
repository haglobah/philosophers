/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timetable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 19:20:15 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/11/30 20:41:01 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	populate_even(t_phi *p, t_args n)
{
	p->tt[0][0] = (t_ts){n.time_to_eat * 1e3, EATING};
	p->tt[0][1] = (t_ts){n.time_to_sleep * 1e3, SLEEPING};
	p->tt[0][2] = (t_ts){1, THINKING};
	p->tt[1][0] = (t_ts){n.time_to_sleep * 1e3, SLEEPING};
	p->tt[1][1] = (t_ts){1, THINKING};
	p->tt[1][2] = (t_ts){n.time_to_eat * 1e3, EATING};
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
