/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_forward_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 10:53:56 by gmelisan          #+#    #+#             */
/*   Updated: 2019/11/02 01:10:20 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"

void				for_space_go(char *str, int *i)
{
	while (*(str + *i) && ft_isspace(*(str + *i)))
		++(*i);
	if (ft_isprint(*(str + *i)) && !ft_isalnum(*(str + *i)))
		while (*(str + *i) && (ft_isprint(*(str + *i)) &&
					!ft_isalnum(*(str + *i))) && *(str + *i + 1) &&
				(ft_isprint(*(str + *i)) && !ft_isalnum(*(str + *i))))
			++(*i);
	else if (ft_isalnum(*(str + *i)))
		while (*(str + *i) && ft_isalnum(*(str + *i)) && *(str + *i + 1)
				&& ft_isalnum(*(str + *i + 1)))
			++(*i);
}

static	void		signs_go(char *str, int *i)
{
	if (*(str + *i + 1) && ft_isspace(*(str + *i + 1)))
	{
		++(*i);
		for_space_go(str, i);
	}
	while (*(str + *i) && (ft_isprint(*(str + *i)) && !ft_isalnum(*(str + *i))
				&& !ft_isspace(*(str + *i))) && *(str + *i + 1) &&
				(ft_isprint(*(str + *i + 1)) && !ft_isalnum(*(str + *i + 1))
				&& !ft_isspace(*(str + *i + 1))))
		++(*i);
}

static	void		alnum_go(char *str, int *i)
{
	if (*(str + *i + 1) && ft_isspace(*(str + *i + 1)) &&
			(ft_isprint(*(str + *i + 1)) && !ft_isalnum(*(str + *i + 1))
			&& !ft_isspace(*(str + *i + 1))))
	{
		++(*i);
		if (ft_isspace(*(str + *i)))
			for_space_go(str, i);
		else
			signs_go(str, i);
	}
	else
		while (*(str + *i) && ft_isalnum(*(str + *i)) && *(str + *i + 1) &&
				ft_isalnum(*(str + *i + 1)))
			++(*i);
}

static	void		forward_go(char *str, int *cpos)
{
	int		i;

	i = *cpos;
	if (ft_isspace(*(str + i)))
		for_space_go(str, &i);
	else if (ft_isalnum(*(str + i)))
		alnum_go(str, &i);
	else if (ft_isprint(*(str + i)) && !ft_isalnum(*(str + i)))
		signs_go(str, &i);
	*cpos = i;
}

void				vi_forward_word(t_line *line)
{
	int i;
	int j;

	j = -1;
	while (++j < line->arg)
	{
		i = line->cpos;
		forward_go(line->str->s, &line->cpos);
	}
}
