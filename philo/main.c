/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:26:38 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/11/30 16:45:15 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	main(int argc, char *argv[])
{
	t_phi	*p;

	p = parse(argc, argv);
	run_philos(p);
	del_phis(p);
	return (0);
}
