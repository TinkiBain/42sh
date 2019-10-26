/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_for_clause.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:11:03 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/10/26 16:38:41 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** for_clause	: For name linebreak                            do_group
** 				| For name linebreak in          sequential_sep do_group
** 				| For name linebreak in wordlist sequential_sep do_group
** 				;
** do_group		: Do compound_list Done
*/

void			traverse_for_clause(t_for_clause *list, t_pjobs **local)
{
	extern char	**g_var;
	char		*var_name;
	char		*var;
	t_wordlist	*wordlist;

	g_is_interrupt = 0;
	if (check_name(list->name) || (check_readonly_var(list->name,
													ft_strlen(list->name))))
		return ;
	var_name = ft_xstrjoin(list->name, "=");
	wordlist = list->wordlist;
	while (wordlist && !g_is_interrupt)
	{
		wordlist->word = tdq(wordlist->word, local);
		var = ft_xstrjoin(var_name, wordlist->word);
		set_var(var, &g_var, 0);
		ft_strdel(&var);
		traverse_compound_list(list->do_group, local);
		wordlist = wordlist->next;
	}
	ft_strdel(&var_name);
}
