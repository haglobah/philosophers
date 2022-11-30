/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:29:03 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/11/30 19:09:10 by bhagenlo         ###   ########.fr       */
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

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i++])
		;
	return (i);
}

void	*ft_memset(void *str, int c, size_t len)
{
	unsigned char	*res;

	res = (unsigned char *) str;
	while (len)
	{
		*res = (unsigned char)c;
		res++;
		len--;
	}
	return (str);
}

void	*ft_calloc(int count, int size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, count * size);
	return (ptr);
}

void	printe(char *msg)
{
	write(2, msg, ft_strlen(msg));
}

void	*rerror(char *msg)
{
	printe(msg);
	return (NULL);
}

void	*rerrorm(char *msg)
{
	printe(msg);
	printe("The correct usage is: \n");
	printe("    ./philo #philos die_time eat_time sleep_time [#must_eat]\n\n");
	return (NULL);
}
