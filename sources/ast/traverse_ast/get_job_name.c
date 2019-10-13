/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_job_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 22:01:59 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/10/14 01:24:15 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*get_job_name(t_lex *lex, t_lex *lex_end)
{
	char	*str;
	char	*tmp;

	if (!lex)
		return (ft_xstrdup(""));
	str = ft_xstrdup((lex->lexem) ? lex->lexem : get_lexem_value(lex->type));
	while ((lex = lex->next) && lex != lex_end)
	{
		if (lex->type == NEWLINE)
			continue ;
		tmp = ft_xstrjoin(" ", (lex->lexem) ? lex->lexem
											: get_lexem_value(lex->type));
		str = ft_xstrrejoin(str, tmp, 3);
	}
	return (str);
}
