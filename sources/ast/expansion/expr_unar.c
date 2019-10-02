/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr_unar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwisoky <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:22:19 by dwisoky           #+#    #+#             */
/*   Updated: 2019/10/01 21:06:39 by dwisoky          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arifmetic.h"

size_t		expr_unar(void)
{
	size_t	left_value;
	int		type;

	type = 0;
	if (g_lex_arif && (g_lex_arif->type == PLUS || g_lex_arif->type == MINUS
				|| g_lex_arif->type == LOGICAL_NOT))
	{
		type = g_lex_arif->type;
		g_lex_arif = g_lex_arif->next;
		left_value = expr_unar();
	}
	else
		left_value = expr_suffix();
	if (g_error_arifmetic)
		return (0);
	if (type == MINUS)
		return (left_value * -1);
	else if (type == LOGICAL_NOT)
		return ((left_value) ? 0 : 1);
	return (left_value);
}
