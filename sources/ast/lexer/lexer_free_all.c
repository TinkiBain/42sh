/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_free_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 21:21:43 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/08/24 21:21:44 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	free_lex(t_lex *lex)
{
	if (!lex)
		return ;
	if (lex->lexeme)
		free(lex->lexeme);
	free(lex);
}

void		lexer_free_all(t_lex *lex)
{
	t_lex	*tmp;

	if (!lex)
		return ;
	while (lex->prev)
	{
		tmp = lex;
		lex = lex->prev;
		free_lex(tmp);
	}
	free_lex(lex);
}
