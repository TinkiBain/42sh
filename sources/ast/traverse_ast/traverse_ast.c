/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 19:23:21 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/09/09 21:03:22 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void		traverse_and_or(t_and_or *elem, int flag1, t_pjobs *local)
{
	extern char	**environ;
	static int	flag;

	flag = flag1;
	if (elem->next)
		traverse_and_or(elem->next, flag, local);
	if (!flag || (flag == AND_IF && !g_res_exec)
				|| (flag == OR_IF && g_res_exec))
	{
		traverse_pipe_sequence(elem->pipeline->pipe_sequence, environ, local);
		if (elem->pipeline->bang)
		{
			g_res_exec = (!g_res_exec) ? 1 : 0;
			set_result();
		}
	}
	else
		return ;
	flag = elem->and_or_if;
}

char			*get_pjob_name(t_and_or *and_or)
{
	char		*pjobs_name;

	pjobs_name = NULL;
	(void)and_or;
	// pjobs_name = and_or->pipeline;
	return (pjobs_name);
}

static void		traverse_list(t_pars_list *list, int sep)
{
	t_pjobs		*local;
	char		*pjobs_name;

	if (list->next)
		traverse_list(list->next, list->next->sep);
	g_res_exec = 0;
	pjobs_name = get_pjob_name(list->and_or);
	local = jobs_startet("name", sep);
	traverse_and_or(list->and_or, 0, local);
}

void			traverse_ast(t_complete_cmd *root)
{
	if (!root)
		return ;
	root->list->sep = root->sep;
	traverse_list(root->list, root->sep);
}
