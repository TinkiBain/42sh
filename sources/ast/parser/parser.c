/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:56:29 by dwisoky           #+#    #+#             */
/*   Updated: 2019/09/06 18:46:30 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
/*
 **complete_command : list separator
 **                 | list
 **				 ;
*/

t_complete_cmd		*parser_free(t_complete_cmd *list)
{
	if (!list)
		return (NULL);
	parser_free_list(list->list);
	free(list);
	return (NULL);
}

t_complete_cmd		*parser(void)
{
	t_complete_cmd	*complete_cmd;

	complete_cmd = (t_complete_cmd*)ft_xmalloc(sizeof(t_complete_cmd));
	complete_cmd->sep = 0;
	complete_cmd->list = parser_list(NULL);
	if (g_error_lex)
		return (parser_free(complete_cmd));
	if (!g_lex)
		return (complete_cmd);
	if (g_lex->type == SEMI || g_lex->type == JOB)
	{
		complete_cmd->sep = g_lex->type;
		g_lex = g_lex->next;
		parser_linebreak();
	}
	else
		parser_new_line_list();
	if (g_lex)
		g_error_lex = g_lex;
	return (complete_cmd);
}
