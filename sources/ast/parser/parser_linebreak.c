/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_linebreak.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 20:30:04 by dwisoky           #+#    #+#             */
/*   Updated: 2019/09/23 14:12:34 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Grammar rule
** linebreak        : newline_list
**                  | / empty /
**                  ;
*/

void		parser_linebreak(void)
{
	if (!g_lex || g_lex->type != NEWLINE)
		return ;
	parser_new_line_list();
}
