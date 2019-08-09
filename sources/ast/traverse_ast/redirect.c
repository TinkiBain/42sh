/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwisoky <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 17:15:05 by dwisoky           #+#    #+#             */
/*   Updated: 2019/08/09 21:36:40 by dwisoky          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int		redirect(t_io_redirect *redir)
{
	if (redir->io_number == -2)
		return (-1); //return error_fd
	if (redir->type & LESS)
		return (redir_less(redir));
	else if (redir->type & DLESS)
		return (redir_dless(redir));
	else if (redir->type & DLESSDASH)
		return (redir_dless(redir));
	else if (redir->type & TLESS)
		return (redir_tless(redir));
/*	else if (redir->type & LESSAND)
		return (redir_less_and(redir));
*/	else if (redir->type & LESSGREAT)
		return (redir_less_great(redir));
	else if (redir->type & GREAT || redir->type & DGREAT)
		return (redir_great(redir));
	else if (redir->type & GREATAND)
		return (redir_great_and(redir));
	else if (redir->type & ANDGREAT)
		return (redir_and_great(redir));
	else if (redir->type & ANDDGREAT)
		return (redir_and_dgreat(redir));
	else
//		return (redir_clobber(redir));
	return (-1);
}
