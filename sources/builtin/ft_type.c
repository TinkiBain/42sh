/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 14:22:58 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/08/03 19:40:08 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		ft_type(char **av)
{
	if (av)
		while (*av)
		{
			if (check_builtin(*av))
			{
				ft_putstr(*av);
				ft_putendl(" is a shell builtin");
			}
			else if (get_bin(*av, g_table))
			{
				ft_putstr(*av);
				ft_putendl(" is a shell builtin");
			}
			else
			{
				ft_putstr(PROJECT_NAME);
				ft_putstr(": type: ");
				ft_putstr(*av);
				ft_putendl(": not found");
			}
			++av;
		}
}
