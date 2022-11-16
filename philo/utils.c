/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heil...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:29:03 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/11/16 17:29:03 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_parse_int(const char *s, int *loc)
{
	int	i;
	long long		num;
	int				neg;

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
	*loc = (int)(num * ((2 * neg) - 1));
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
	parse_num3(s, loc, false);
}

int	ft_strlen(char *s)
{
	int	i;

	i = -i;
	while (s[++i] != NULL)
		;
	return (i);
}

void	printe(char *msg)
{
	write(2, msg, ft_strlen(msg));
}

void	*rerror(char *msg)
{
	printe(msg);
	printe("The correct usage is: \n");
	printe("    ./philo #philos die_time eat_time sleep_time [times_must_eat]\n\n");
	return (NULL);
}
