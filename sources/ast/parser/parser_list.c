#include "parser.h"

/*
 ** Grammar rule
 ** list    : list separator_op and_or
 **         |                   and_or
 **         ;
*/

t_pars_list			*parser_free_list(t_pars_list *list)
{
	if (!list)
		return (NULL);
	parser_free_and_or(list->and_or);
	parser_free_list(list->list);
	free(list);
	return (NULL);
}

static t_pars_list	*parser_init_list(t_pars_list *list_down)
{
	t_pars_list		*list;

	list = (t_pars_list*)ft_xmalloc(sizeof(t_pars_list));
	list->list = list_down;
	list->sep = 0;
	list->and_or = NULL;
	return (list);
}

t_pars_list			*parser_list(t_pars_list *list_down)
{
	t_pars_list	*list;

	if (!g_lex)
		return (NULL);
	list = parser_init_list(list_down);
	list->and_or = parser_and_or(NULL);
	if (g_error_lex)
		return (parser_free_list(list));
	if (!g_lex)
		return (list);
	if ((g_lex->type == JOB || g_lex->type == SEMI)
			&& g_lex->next && g_lex->next->type != NEWLINE)
	{
		list->sep = g_lex->type;
		g_lex = g_lex->next;
		return (parser_list(list));
	}
	return (parser_free_list(list));
}
