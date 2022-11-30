/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 20:06:48 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/11/30 20:42:53 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

bool	ft_parse_int(const char *s, int *loc)
{
	int			i;
	long long	num;
	int			neg;

	num = 0;
	i = 0;
	neg = (s[i] == '-');
	i += neg;
	while (s[i] != '\0' && ft_isdigit(s[i]))
	{
		num = (num * 10) + (s[i] - '0');
		if (num > (((long long)INT_MAX) + neg))
			return (false);
		i++;
	}
	*loc = (int)(num * -((2 * neg) - 1));
	return (i > neg && s[i] == '\0');
}

bool	parse_num3(const char *s, int *loc, bool is_num_philos)
{
	if (ft_parse_int(s, loc) == false)
		return (false);
	if (*loc < 0)
		return (false);
	if (is_num_philos && *loc < 1)
		return (false);
	return (true);
}

bool	parse_num2(const char *s, int *loc)
{
	return (parse_num3(s, loc, false));
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
