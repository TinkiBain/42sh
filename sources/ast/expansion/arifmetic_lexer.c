/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arifmetic_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwisoky <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:21:28 by dwisoky           #+#    #+#             */
/*   Updated: 2019/10/03 16:37:29 by dwisoky          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arifmetic.h"

char		*arifmetic_lexer_bracket(char *str, t_lex **lex)
{
	if (*str == '(')
		init_lex(LBRACKET_ARIF, ft_strdup("("), lex);
	else
		init_lex(RBRACKET_ARIF, ft_strdup(")"), lex);
	++str;
	return (str);
}

char		*arifmetic_lexer_not(char *str, t_lex **lex)
{
	++str;
	if (*str == '=')
	{
		++str;
		init_lex(NOT_EQUAL_IF, ft_strdup("!="), lex);
	}
	else
		init_lex(LOGICAL_NOT, ft_strdup("!"), lex);
	return (str);
}

t_lex		*arifmetic_lexer(char *str)
{
	t_lex	*lex;
	char	*begin;

	lex = NULL;
	while (str && *str)
	{
		begin = str;
		while (ft_isspace(*str))
			++str;
		if (ft_isalpha(*str))
			str = arifmetic_lexer_var(str, &lex);
		else if (ft_isdigit(*str))
			str = arifmetic_lexer_digit(str, &lex);
		else if (*str == '(' || *str == ')')
			str = arifmetic_lexer_bracket(str, &lex);
		else if (*str == '!')
			str = arifmetic_lexer_not(str, &lex);
		else
			str = arifmetic_lexer_check_token(str, &lex);
	}
	if (!str)
		init_lex(DIGIT, begin, &g_error_arifmetic);
	while (lex && lex->back)
		lex = lex->back;
	return (lex);
}