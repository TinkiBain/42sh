/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_hash_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 17:49:40 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/08/08 18:17:52 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		fill_hash_table(void)
{
	extern t_hash	**g_table;
	extern char		**g_env;

	if (g_table)
		del_hash();
	g_table = (t_hash **)ft_xmalloc(sizeof(t_hash) * HASH_LEN);
	if (g_env)
	{
		create_bin(ft_getenv("PATH", g_env));
	}
}
