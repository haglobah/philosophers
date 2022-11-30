/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 20:06:48 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/11/30 20:07:11 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
