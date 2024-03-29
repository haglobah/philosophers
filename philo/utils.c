/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:29:03 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/11/30 20:45:19 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
