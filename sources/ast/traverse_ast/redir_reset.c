/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_reset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwisoky <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 17:08:30 by dwisoky           #+#    #+#             */
/*   Updated: 2019/08/09 18:44:29 by dwisoky          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void		close_all_fd(void)
{
	int			i;

	i = 0;
	while (++i < *g_open_fd)
		close(g_open_fd[i]);
	free(g_open_fd);
	g_open_fd = NULL;
}

void			redir_reset(void)
{
	char		*file;
	int			fd;
	int			i;

	close_all_fd();
	i = 0;
	while (i < 4)
	{
		if (!(file = ttyname(i)))
		{
			fd = open(g_tty, O_RDWR);
			dup2(fd, i);
			close(fd);
		}
		++i;
	}
}
