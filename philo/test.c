/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 23:44:56 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/11/30 20:44:09 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdarg.h>

char	**mk_stra(int argc, ...)
{
	va_list	argp;
	int		i;
	char	**res;

	res = calloc(sizeof(char *), argc);
	if (res == NULL)
		return (NULL);
	va_start(argp, argc);
	i = 0;
	while (i < argc)
	{
		char *str_to_add = va_arg(argp, char *);
		res[i] = ft_calloc(sizeof(char), ft_strlen(str_to_add) + 1);
		if (res[i] == NULL)
			return (NULL);
		res[i] = str_to_add;
		printf("\'%s\', ", str_to_add);
		i++;
	}
	printf("\n");
	va_end(argp);
	return (res);
}

int	assert(int argc, char *argv[], bool assertion, int *total_tests)
{
	*total_tests += 1;
	if (parse(argc, argv) == NULL)
		printf("NULL");
	return ((parse(argc, argv) == NULL) == assertion);
}

void	test_parser()
{
	int	total_tests;
	int	pass_count;
	int	i;

	total_tests = 0;
	pass_count = 0;
	i = 0;
	printf("\nTesting Parser...\n");
	pass_count += assert(5, mk_stra(5, "./philo", "1", "2", "3", "5"),
						 true, &total_tests);
	printf("\nPassed %i / Failed %i (of %i)\n",
			  pass_count,
			  total_tests - pass_count,
			  total_tests);
}

void	run_tests(void)
{
	test_parser();
}
