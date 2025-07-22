/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:17:32 by ybahri            #+#    #+#             */
/*   Updated: 2025/07/22 10:28:07 by ybahri           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

int	main(int ac, char **av)
{
	(void)av;

	t_table	table;
	if(ac == 5 || ac == 6)
	{
		parse_input(&table, av);
		data_init(&table);
		dinner_start(&table);
		clean(&table);
	}
	else
		error_exit("Wrong input: \nCorrect example is: ./philo 5 800 200 200 [5]");
}
