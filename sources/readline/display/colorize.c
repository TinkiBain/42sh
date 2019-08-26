/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 18:37:50 by gmelisan          #+#    #+#             */
/*   Updated: 2019/08/26 18:59:25 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "colors.h"

static void	colorize_arg(t_string *str, int *i)
{
	char	c;

	str_xinsert(str, *i, COLOR_GREY, ft_strlen(COLOR_GREY));
	*i += ft_strlen(COLOR_GREY);
	while ((c = str_get(*str, *i)) && !ft_isspace(c))
		*i += 1;
	str_xinsert(str, *i, COLOR_EOC, ft_strlen(COLOR_EOC));
	*i += ft_strlen(COLOR_EOC);
}

static void	colorize_cmd_sep(t_string *str, int *i)
{
	str_xinsert(str, *i, COLOR_GREEN, ft_strlen(COLOR_GREEN));
	*i += ft_strlen(COLOR_GREEN);
	*i += 1;
	str_xinsert(str, *i, COLOR_EOC, ft_strlen(COLOR_EOC));
	*i += ft_strlen(COLOR_EOC);
}

void		colorize(t_string *str)
{
	int			i;
	char		c;

	i = -1;
	while ((c = str_get(*str, ++i)))
	{
		if (c == '-')
			colorize_arg(str, &i);
		else if (c == '&' || c == '|')
			colorize_cmd_sep(str, &i);
		else if (c == '\\')
			++i;
	}
}